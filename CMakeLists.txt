cmake_minimum_required(VERSION 3.20)
project(project_conc)

set(CMAKE_CXX_STANDARD 14)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

set(BUILD_DIR "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_DIR}/../bin/")
set(BINARY_DIR "${CMAKE_BINARY_DIR}")


set(HEADER_FILES
        actors/bee.h
        actors/winnie_the_pooh.h
        objects/beehive.h
        utils/settings.h
        utils/utils.h
        )

set(SOURCE_FILES
        actors/bee.cpp
        actors/winnie_the_pooh.cpp
        objects/beehive.cpp
        )

add_executable(program
        main.cpp
        ${HEADER_FILES}
        ${SOURCE_FILES}
        )


target_link_libraries(program PRIVATE Threads::Threads)
