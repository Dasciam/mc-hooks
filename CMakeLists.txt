cmake_minimum_required(VERSION 3.15)

project(mchooks)

include(cmake/CPM.cmake)

CPMAddPackage("gh:BasedInc/libhat@0.4.0")
CPMAddPackage("gh:cursey/safetyhook@0.6.9")

add_library(mchooks SHARED main.cpp)

target_link_libraries(mchooks PRIVATE
        safetyhook
        libhat::libhat
)