#include "Player.h"

Player::Player() {
    this->name = "Nameless";
    this->hp = 100;
    this->inventory = std::vector<std::string>({"Potion", "Knife", "Scroll"});
    this->current_location = "Forest";
}