// RestartNet.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <iostream>

#include <Poco/Util/ServerApplication.h>
#include <Poco/Thread.h>

class RestartNetApp : public Poco::Util::ServerApplication
{

public:
	RestartNetApp();

		~RestartNetApp();
		int main(const std::vector<std::string>& args);
protected:
	void initialize(Application& self);

	void uninitialize();


private:
	Poco::Thread	_t;
};


// TODO: 在此处引用程序需要的其他标头。
