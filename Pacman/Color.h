#pragma once
#include <sstream>

struct Color
{
	int r, g, b, a;
	static Color FromHex(const std::string&hex);
};

inline Color Color::FromHex(const std::string& hex)
{
	std::string alpha = hex.substr(1, 2);
	std::string red = hex.substr(3, 2);
	std::string green = hex.substr(5, 2);
	std::string blue = hex.substr(7, 2);
	std::string str = red + " " + green + " " + blue + " " + alpha;
	std::istringstream ostrStream(str);
	Color color;
	ostrStream >> std::hex >> color.r >> color.g >> color.b >> color.a;
	return color;
}


