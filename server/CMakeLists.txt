cmake_minimum_required(VERSION 3.24)
project(serverside)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Drogon CONFIG REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)
include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba) # The commit hash for 1.10.x. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)
#add_subdirectory(cpp-dotenv)

add_executable(serverside main.cc services/weatherService/weather.cpp services/weatherService/weather.h requestHandler.cc)

target_link_libraries(serverside PRIVATE cpr::cpr)
target_link_libraries(serverside PRIVATE Drogon::Drogon)
target_link_libraries(serverside PRIVATE nlohmann_json::nlohmann_json)
#target_link_libraries(serverside PUBLIC cpp_dotenv)

