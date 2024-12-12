#pragma once

#include <string>
#include <vector>
#include <cstdint>

// This is a class for our player character
// This class has:
// - Name;
// - HP;
// - Inventory;
// - Current location;

class Player {
    public:
        Player();
        std::string name;
        uint32_t hp;
        std::vector<std::string> inventory;
        std::string current_location;
};