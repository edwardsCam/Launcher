#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "Level.h"

class Parser {
public:
	static std::vector<Level> parseLevels();
	static const std::vector<sf::Color> parseColors();
};

#endif