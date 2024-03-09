#ifndef NETWORKTHREAD_H
#define NETWORKTHREAD_H

#include <string>
#include <map>
#include <vector>

#include "Poco/Runnable.h"

typedef std::map<std::string, int> IntfCountMap;

class NetworkThread : public Poco::Runnable
{
public:
	NetworkThread();

	~NetworkThread();

	void stop()
	{
		m_bStopFlag = true;
	}

protected:

	void run();

private:

	IntfCountMap getIntfIpv6Counter();

	void compareIntfAndRestart(const IntfCountMap& old, const IntfCountMap& now);

	void restartIntf(const std::string intfName);

private:

	int getIpv6AddrList();

	IntfCountMap m_lastIpv6Status;

private:
	bool m_bStopFlag;
};

#endif // !NETWORKTHREAD_H
