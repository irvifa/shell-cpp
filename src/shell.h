#ifndef SHELL_H
#define SHELL_H

#include "command_interface.h"
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <string>

namespace ShellNamespace {
    class Shell {
    public:
        Shell();
        void run();
    private:
        struct Command {
            std::string name;
            std::vector<std::string> args;
        };

        std::unordered_map<std::string, std::unique_ptr<CommandInterface>> commands;
        std::unordered_set<std::string> builtins;

        Command tokenize(const std::string& input);
        bool execute(const Command& command);
        void runExternalCommand(const Command& command);
    };
}

#endif // SHELL_H
