# CMakeList.txt: RestartNet 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

# 将源代码添加到此项目的可执行文件。
add_executable (RestartNet 
"RestartNet.cpp" 
"RestartNet.h" 
"NetWorkThread.h"
"NetWorkThread.cpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RestartNet PROPERTY CXX_STANDARD 20)
endif()

add_definitions(-DPOCO_STATIC)

find_package(Poco
	COMPONENTS Foundation Net Util XML
	PATHS ${PROJECT_SOURCE_DIR}/../PocoStatic
	REQUIRED
	NO_DEFAULT_PATH
)


target_include_directories(RestartNet PRIVATE
  ${PROJECT_SOURCE_DIR}/../Poco/include
)

target_link_libraries(RestartNet
	PRIVATE
	Poco::Foundation
	Poco::Util
	Poco::Net
)

# TODO: 如有需要，请添加测试并安装目标。
