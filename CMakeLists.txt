cmake_minimum_required(VERSION 3.20)

project(LightLog CXX)
add_library(LightLog LightLog/src/Log.cpp)

add_executable(example example.cpp)
target_include_directories(example
	PUBLIC 
	LightLog/include
)
target_link_libraries(example PUBLIC LightLog)

target_include_directories(LightLog
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/LightLog/include>
	$<INSTALL_INTERFACE:LightLog/include>
)

install(TARGETS LightLog
	EXPORT LightLog
	DESTINATION lib
)
		
install(FILES LightLog/LightLogConfig.cmake
	DESTINATION lib/cmake/LightLog
)

install(FILES 
	LightLog/include/Log.h
	DESTINATION	include
)
