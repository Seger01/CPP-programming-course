#include <iostream>

#include <cstring>
#include <string>

#include "ArmorObject.h"
#include "Database.h"
#include "ExperiencePotionObject.h"
#include "GameObjectFactory.h"
#include "GoldPiecesObject.h"
#include "HealthPotionObject.h"
#include "String.h"
#include "TUI.h"
#include "TeleportationPotionObject.h"
#include "Vector.h"
#include "WeaponObject.h"

// main function with input args and return type int the one input argument is a
// file path
int main(int argc, char* argv[]) {
    // check if the input argument is not provided
    std::string filename;
    if (argc < 2) {
        // print the error message
        filename = "";
    } else {
        filename = argv[1];
        // print the file path
        std::cout << "File path: " << filename << std::endl;
    }

    {
        ArmorObject armorObject;
        WeaponObject weaponObject;
        GoldPiecesObject goldObject;
        HealthPotionObject healthPotionObject;
        TeleportationPotionObject teleportationPotionObject;
        ExperiencePotionObject experiencePotionObject;
    }

    bool restart = false;

    while (true) {
        TUI tui(filename);

        if (!tui.run()) {
            break;
        }
    }

    return 0;
}
