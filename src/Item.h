#pragma once

#include <string>
#include <cstdint>

struct World;

struct Item {
    std::string name;
    std::string description;

    Item(std::string new_name, std::string new_description);
    virtual ~Item() {};
    virtual void use(World& world) = 0;
    virtual std::string to_string() = 0;
};

struct HealingPotion: public Item {
    HealingPotion(uint32_t new_power);

    void use(World& world) override;
    std::string to_string() override;

    uint32_t healing_power;
};