// RestartNet.cpp: 定义应用程序的入口点。
//

#include "RestartNet.h"
#include "NetWorkThread.h"

using namespace std;

POCO_SERVER_MAIN(RestartNetApp)

RestartNetApp::RestartNetApp()
{
}

RestartNetApp::~RestartNetApp()
{
}

int RestartNetApp::main(const std::vector<std::string>& args)
{

	NetworkThread * p = new NetworkThread();

	_t.start(p);

	waitForTerminationRequest();


	return 0;
}

void RestartNetApp::initialize(Application& self)
{
}

void RestartNetApp::uninitialize()
{
}
