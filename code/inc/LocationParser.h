#ifndef LOCATIONPARSER_H
#define LOCATIONPARSER_H

#include "Location.h"
#include "tinyxml2.h"
#include <string>
#include <vector>

class LocationParser {
public:
    LocationParser(const std::string& filename);
    ~LocationParser();

    std::vector<Location*> parse();

private:
    void parseExits(tinyxml2::XMLElement* locElement, Location* location);
    void parseObjects(tinyxml2::XMLElement* locElement, Location* location);
    void parseEnemies(tinyxml2::XMLElement* locElement, Location* location);

    std::string filename;
};

#endif // LOCATIONPARSER_H
