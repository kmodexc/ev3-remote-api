#pragma once

enum class Output{
	A = 1,
	B = 2,
	C = 4,
	D = 8
};

// Previously input
enum class Port{
	S1 = 0,
	S2 = 1,
	S3 = 2,
	S4 = 3,
	A = 16,
	B = 17,
	C = 18,
	D = 19,
	E,
	F
};

enum class Then{
	Coast,
	Brake,
	Hold
};