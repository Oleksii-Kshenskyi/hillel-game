#include "Item.h"
#include "World.h"

#include <sstream>

Item::Item(std::string new_name, std::string new_description): name(new_name), description(new_description) {}


HealingPotion::HealingPotion(uint32_t new_power): healing_power(new_power), Item("Healing Potion", "A potent potion that heals its user.") {}

void HealingPotion::use(World& world) {
    uint32_t result = std::min(world.p.hp + this->healing_power, world.p.max_hp);
    world.p.hp = result;
}

std::string HealingPotion::to_string() {
    std::stringstream ss;
    ss << this->name << "(" << this->healing_power << ")";

    return ss.str();
}