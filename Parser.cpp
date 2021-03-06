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
							iss >> thePlanet.xpos >> thePlanet.ypos >> thePlanet.radius;
							theLevel.addPlanet(thePlanet);
						} else if (line[0] == 's') {
							line = line.substr(3, line.length() - 2);
							std::istringstream iss(line);
							unsigned int xp, yp;
							iss >> xp >> yp;
							theLevel.setPlayerPos(xp, yp);
							theLevel.x_i = xp;
							theLevel.y_i = yp;
						}
						else if (line[0] == 'g') {
							line = line.substr(3, line.length() - 2);
							std::istringstream iss(line);
							iss >> theLevel.goal.pos.x >> theLevel.goal.pos.y;
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