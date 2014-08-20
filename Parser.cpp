#include "Parser.h"
#include <fstream>
#include <sstream>

std::vector<Level> Parser::parseLevels() {

	std::vector<Level> ret;

	std::ifstream s ("levels.txt");
	std::string line;
	int levelId = 1;
	bool parsing_level = false;
	if (s.is_open()) {
		while (std::getline(s,line)) {
			if (!line.empty() && line[0] != '#') {
				if (parsing_level) {
					Level theLevel;
					theLevel.id = levelId++;
					while (parsing_level) {
						if (line[0] == 'p') {
							Planet thePlanet;
							line = line.substr(3, line.length() - 2);
							std::istringstream iss(line);
							iss >> thePlanet.radius >> thePlanet.xpos >> thePlanet.ypos;
							theLevel.addPlanet(thePlanet);
						} else if (line[0] == 's') {
							sf::Vector2u pos;
							line = line.substr(3, line.length() - 2);
							std::istringstream iss(line);
							iss >> pos.x >> pos.y;
							theLevel.setPlayerPos(pos);
						}
						if (line[0] == '-') {
							parsing_level = false;
							continue;
						}
						std::getline(s,line);
					} // while parsing_level
					ret.push_back(theLevel);
				} // if parsing_level
				if (line[0] == '+')
					parsing_level = true;
			} // if not comment
		} // getline
	} // if open

	return ret;
}

const std::vector<sf::Color> Parser::parseColors() {
	std::vector<sf::Color> ret;

	std::ifstream s ("colors.txt");
	std::string line;

	if (s.is_open()) {
		while (std::getline(s,line)) {
			if (!line.empty() && line[0] != '#') {
				if (line[0] == 'c') {
					line = line.substr(3, line.length() - 2);
					std::istringstream iss(line);
					int r, g, b;
					iss >> r >> g >> b;
					sf::Color c(r, g, b);
					ret.push_back(c);
				}
			} // if not comment
		} // getline
	} // if open

	return ret;
}