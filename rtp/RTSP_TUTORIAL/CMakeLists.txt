cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME rtsp_server)
project(${PROJECT_NAME})

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)

# OpenCV 경로 설정
set(OpenCV_DIR /usr/local/include/opencv4)  # OpenCV 설치 경로 지정

# OpenCV 라이브러리 찾기
find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)

# OpenCV 상태 출력
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

# 현재 디렉토리 포함 설정
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# OpenCV 포함 경로 추가
include_directories(${OpenCV_INCLUDE_DIRS})

# 컴파일러 플래그 설정
add_definitions(-Wall -D_REENTRANT -D_GNU_SOURCE -D_UNICODE -g -Os -DTIXML_USE_STL)

# 32비트 컴파일러 플래그 설정
if(KERNELTYPE EQUAL 32)
    add_definitions(-m32)
    message(STATUS "Set `-m32` flags.")
endif()

# 소스 파일 목록 설정
set(SRCS_SDV_ERM
    rtsp/header.hpp
    rtsp/server.cpp
    rtsp/server.hpp
)

# 서버 실행 파일 생성 및 링크
add_executable(rtsp_server ${SRCS_SDV_ERM} example/example_server.cpp)
target_link_libraries(rtsp_server
    ${OpenCV_LIBS}
    avcodec
    avformat
    avutil
    swscale
    Threads::Threads
)

# 클라이언트 실행 파일 생성 및 링크
add_executable(rtsp_client example/example_client.cpp)
target_link_libraries(rtsp_client
    ${OpenCV_LIBS}
    avcodec
    avformat
    avutil
    swscale
    Threads::Threads
)
