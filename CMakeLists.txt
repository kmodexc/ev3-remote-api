cmake_minimum_required(VERSION 3.16)

project(LegoRaspiApi)

add_executable(LegoRaspiApi 
	main.cpp 
	"Command.cpp"
	HIDCon.cpp
	Brick.cpp
)

target_compile_features(LegoRaspiApi PRIVATE cxx_std_17)