cmake_minimum_required(VERSION 3.10)
project(TextureCompressionAlgorithmAnalytics)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directory
include_directories(include)

# Add source files
add_executable(ShaderCompiler main.cpp compression/dxt/dxt1.cpp compression/dxt/dxt2.cpp)