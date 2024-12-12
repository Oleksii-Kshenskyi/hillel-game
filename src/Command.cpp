#include "Command.h"
#include "fmt/core.h"

#include <cstdlib>

CommandExecutor::CommandExecutor(): command_mapping({
    {"show", new ShowCommand()},
    {"exit", new ExitCommand()},
    {"rename", new RenameCommand()},
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