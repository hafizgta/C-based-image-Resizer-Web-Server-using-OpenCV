cmake_minimum_required(VERSION 3.7)
project(OPENCV_RESIZER)


set(CMAKE_CXX_STANDARD 11)
ADD_COMPILE_OPTIONS(-fPIC)

set(SOURCE_FILES main.cpp base64.cpp base64.h crow_all.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES PREFIX "")


# OpenCV libs
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

# boost lib
find_package(Boost REQUIRED COMPONENTS system thread)
include_directories( ${Boost_INCLUDE_DIRS} )
target_link_libraries(${PROJECT_NAME} ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY})

