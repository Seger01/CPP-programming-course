#include "LocationParser.h"
#include "Directions.h"
#include "Enemy.h"
#include "GameObject.h"
#include <iostream>
#include <sstream>

using namespace tinyxml2;

LocationParser::LocationParser(const std::string& filename) : filename(filename) {}

LocationParser::~LocationParser() {}

std::vector<Location*> LocationParser::parse() {
    std::vector<Location*> locations;
    XMLDocument doc;
    if (doc.LoadFile(filename.c_str()) != XML_SUCCESS) {
        std::cerr << "Error loading file: " << filename << "\n";
        return locations;
    }

    XMLElement* root = doc.FirstChildElement("locaties");
    if (!root) {
        std::cerr << "No 'locaties' root element found.\n";
        return locations;
    }

    for (XMLElement* locElement = root->FirstChildElement("locatie"); locElement;
         locElement = locElement->NextSiblingElement("locatie")) {
        int id = locElement->IntAttribute("id");
        const char* name = locElement->GetText();
        const char* descriptionText = locElement->FirstChildElement("beschrijving")->GetText();

        Location* location = new Location(id, name, descriptionText);

        parseExits(locElement, location);
        parseObjects(locElement, location);
        parseEnemies(locElement, location);

        locations.push_back(location);
    }
    return locations;
}

void LocationParser::parseExits(XMLElement* locElement, Location* location) {
    if (locElement->Attribute("noord")) {
        location->addExit(locElement->IntAttribute("noord"), NORTH);
    }
    if (locElement->Attribute("oost")) {
        location->addExit(locElement->IntAttribute("oost"), EAST);
    }
    if (locElement->Attribute("zuid")) {
        location->addExit(locElement->IntAttribute("zuid"), SOUTH);
    }
    if (locElement->Attribute("west")) {
        location->addExit(locElement->IntAttribute("west"), WEST);
    }
}

void LocationParser::parseObjects(XMLElement* locElement, Location* location) {
    if (const char* hiddenObjectsText = locElement->Attribute("objectenverborgen")) {
        std::string objects(hiddenObjectsText);
        std::istringstream ss(objects);
        std::string objectName;

        while (std::getline(ss, objectName, ';')) {
            GameObject* hiddenObject = GameObject::create();
            hiddenObject->setData(objectName.c_str(), "Hidden object in location");
            location->addHiddenObject(hiddenObject);
        }
    }

    if (const char* visibleObjectsText = locElement->Attribute("objectenzichtbaar")) {
        std::string objects(visibleObjectsText);
        std::istringstream ss(objects);
        std::string objectName;

        while (std::getline(ss, objectName, ';')) {
            GameObject* visibleObject = GameObject::create();
            visibleObject->setData(objectName.c_str(), "Visible object in location");
            location->addVisibleObject(visibleObject);
        }
    }
}

void LocationParser::parseEnemies(XMLElement* locElement, Location* location) {
    if (const char* enemiesText = locElement->Attribute("vijand")) {
        std::string enemies(enemiesText);
        std::istringstream ss(enemies);
        std::string enemyName;

        while (std::getline(ss, enemyName, ';')) {
            Enemy* enemy = new Enemy(enemyName.c_str(), "Enemy in location", 0, 0, 0, 0);
            location->addEnemy(enemy);
        }
    }
}
