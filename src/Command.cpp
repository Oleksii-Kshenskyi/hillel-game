#include "Command.h"
#include "fmt/core.h"

#include <cstdlib>
#include <sstream>

CommandExecutor::CommandExecutor(): command_mapping({
    {"show", new ShowCommand()},
    {"exit", new ExitCommand()},
    {"rename", new RenameCommand()},
    {"where", new WhereCommand()},
    {"describe", new DescribeCommand()},
    {"go", new GoCommand()},
    {"", new UnknownCommand()},
}) {

}

CommandExecutor::~CommandExecutor() {
    for(auto& pair : this->command_mapping) {
        delete pair.second;
    }
}

void CommandExecutor::execute(std::vector<std::string>& args, World& world) {
    if(args.size() == 0) {
        return;
    }

    this->command_mapping[(this->command_mapping.contains(args[0]) ? args[0] : "")]->execute(args, world);
}


// show hp
// show inventory
// show name
void ShowCommand::execute(std::vector<std::string>& args, World& world) {
    if(args.size() == 1) {
        fmt::print("Show what exactly?..");
    } else if(args.size() == 2) {
        if(args[1] == "hp") {
            fmt::print("Player's HP: {}", world.p.hp);
        } else if(args[1] == "name") {
            fmt::print("Player's name: {}", world.p.name);
        } else if(args[1] == "inventory") {
            fmt::print("You have {} in your inventory.", join(world.p.inventory, ", "));
        } else if(args[1] == "exits") {
            std::stringstream ss;
            auto& exits = world.get_current_location().exits;
            std::vector<std::string> exit_names = {"North", "East", "South", "West"};
            bool all_empty = true;
            for(int i = 0; i < 4; i++) {
                if(!exits[i].empty()) {
                    ss << exit_names[i] << ": " << exits[i] << ";\n";
                    all_empty = false;
                }
            }

            fmt::print("{}", ss.str());
            if(all_empty) {
                throw "ERROR: ShowCommand::execute(): exits: NO EXITS EXIST FOR LOCATION?!";
            }
        } else {
            fmt::print("Don't know how to show '{}'!", args[1]);
        }
    } else {
        fmt::print("Can only show one thing at a time!");
    }
}

void ExitCommand::execute(std::vector<std::string>& args, World& world) {
    fmt::print("Thanks for playing, see you later!\n\n");

    std::exit(0);
}

void WhereCommand::execute(std::vector<std::string>& args, World& world) {
    if(args.size() == 3 && args[1] == "am" && args[2] == "i") {
        fmt::print("You are in the {} now.", world.p.current_location);
    } else {
        fmt::print("Where what? (you may have meant `where am i`)");
    }
}

void DescribeCommand::execute(std::vector<std::string>& args, World& world) {
    if(args.size() == 2 && args[1] == "area") {
        auto& loc = world.get_current_location();
        fmt::print("You are in {}. {}", loc.name, loc.description);
    } else {
        fmt::print("Describe what? (you may have meant `describe area`)");
    }
}


// TODO: solve the corner case where you could get a non-existant location in the exits array.
void GoCommand::execute(std::vector<std::string>& args, World& world) {
    if(args.size() != 2) {
        fmt::print("Can only go to one place at a time!");
        return;
    }

    auto& exits = world.get_current_location().exits;
    if(args[1] == "north") {
        if(!exits[0].empty()) {
            world.p.current_location = exits[0];
            fmt::print("You went North, to {}.", world.p.current_location);
        } else {
            fmt::print("There's no exit to the North!");
        }
    } else if(args[1] == "east") {
        if(!exits[1].empty()) {
            world.p.current_location = exits[1];
            fmt::print("You went East, to {}.", world.p.current_location);
        } else {
            fmt::print("There's no exit to the East!");
        }
    } else if (args[1] == "south") {
        if(!exits[2].empty()) {
            world.p.current_location = exits[2];
            fmt::print("You went South, to {}.", world.p.current_location);
        } else {
            fmt::print("There's no exit to the South!");
        }
    } else if (args[1] == "west") {
        if(!exits[3].empty()) {
            world.p.current_location = exits[3];
            fmt::print("You went West, to {}.", world.p.current_location);
        } else {
            fmt::print("There's no exit to the West!");
        }
    } else {
        fmt::print("Can only go north, south, east or west!");
        return;
    }
}

void UnknownCommand::execute(std::vector<std::string>& args, World& world) {
    fmt::print("ERROR: Don't know how to '{}'!", args[0]);
}

void RenameCommand::execute(std::vector<std::string>& args, World& world) {
    if(args.size() == 1) {
        fmt::print("Rename player to what?");
    } else if(args.size() > 2) {
        fmt::print("You can only name yourself one thing, not multiple!");
    }

    world.p.name = args[1];
    fmt::print("Your name is now {}!", world.p.name);
}