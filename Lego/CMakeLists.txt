cmake_minimum_required(VERSION 3.16)

add_library(Lego SHARED
    "Command.cpp"
    Brick.cpp
)
target_link_libraries(Lego PUBLIC HidIO)
target_include_directories(Lego PUBLIC ../IO)