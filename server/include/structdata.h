// #ifndef structdata
// #define structdata
#pragma once
#include <string>

// struct position {
// 	float x = 0;
// 	float y = 0;
// };

struct player {
	//position pos;
	std::string name;

	player(std::string name) : name(name) {}
};

// #endif // !data