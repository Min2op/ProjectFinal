cmake_minimum_required(VERSION 3.0.0)
project(personalProject VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(personalProject main.cpp Controller.cpp Dataset.cpp MatchingAlgorithm.cpp model.cpp view.cpp CalibrateData.cpp)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
include_directories(CalibratedRooms, currentReading)
