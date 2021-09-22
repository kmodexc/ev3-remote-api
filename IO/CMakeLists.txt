cmake_minimum_required(VERSION 3.16)

find_package(Threads REQUIRED)
add_library(HidIO SHARED
	HIDCon.cpp
)
target_link_libraries(HidIO PUBLIC stdc++fs Threads::Threads)
target_compile_features(HidIO PUBLIC cxx_std_17)