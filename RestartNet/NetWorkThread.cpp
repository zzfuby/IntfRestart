#include "NetWorkThread.h"

#include <iostream>

#include "Poco/Thread.h"
#include "Poco/Net/NetworkInterface.h"

using Poco::Net::NetworkInterface;


NetworkThread::NetworkThread()
	:m_bStopFlag(true)
{
}

NetworkThread::~NetworkThread()
{
}

void NetworkThread::run()
{
	m_bStopFlag = false;
	m_lastIpv6Status = getIntfIpv6Counter();

	while (!m_bStopFlag)
	{
		auto curIntfStat = getIntfIpv6Counter();
		compareIntfAndRestart(m_lastIpv6Status, curIntfStat);
		m_lastIpv6Status.clear();
		m_lastIpv6Status = curIntfStat;

		// 10min
		Poco::Thread::sleep(1000 * 60 * 10);
	}
}

std::map<std::string, int> NetworkThread::getIntfIpv6Counter()
{
	std::map<std::string, int> ret;

	NetworkInterface::List m = NetworkInterface::list(true, false);
	for (auto it = m.begin(); it != m.end(); ++it)
	{
		NetworkInterface& curInterface = *it;
		if (curInterface.supportsIPv6() && curInterface.isUp() && !curInterface.isLoopback())
		{
			std::cout << curInterface.name() << std::endl;
			NetworkInterface::AddressList::const_iterator ipIt = curInterface.addressList().begin();
			NetworkInterface::AddressList::const_iterator ipEnd = curInterface.addressList().end();
			for (; ipIt != ipEnd; ++ipIt)
			{
				std::string addrStr = ipIt->get<NetworkInterface::IP_ADDRESS>().toString();
				if (addrStr.substr(0, 3) == "240")
				{
					auto itrCounter = ret.find(curInterface.name());
					if (itrCounter != ret.end())
					{
						++itrCounter->second;
					}
					else
					{
						ret[curInterface.name()] = 0;
					}
				}
			}
		}
	}
	return ret;
}

void NetworkThread::compareIntfAndRestart(const IntfCountMap& old, const IntfCountMap& now)
{
	
	for (auto itr = now.cbegin(); itr != now.cend(); ++itr)
	{
		std::string curIntf = itr->first;
		auto itrFindOld = old.find(curIntf);
		if (itrFindOld != old.end())
		{
			if (itr->second > itrFindOld->second)
			{
				//do restart
				std::cout << "Restarting Intf counter gt old" << curIntf << std::endl;
				restartIntf(itr->first);
			}
		}
		else
		{
			//new interface >1 do restart
			if (itr->second > 1)
			{
				std::cout << "Restarting new Intf counter gt 1" << curIntf << std::endl;
				restartIntf(itr->first);
			}
		}
	}
}

void NetworkThread::restartIntf(const std::string intfName)
{

	std::string commandDisabled = "netsh interface set interface \"" + intfName + "\" disabled";
	std::string commandEnabled = "netsh interface set interface \"" + intfName + "\" enabled";

	system(commandDisabled.data());
	system(commandEnabled.data());
}
