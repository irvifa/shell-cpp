#ifndef COMMANDS_H
#define COMMANDS_H

#include "command_interface.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace ShellNamespace {
    class ExitCommand : public CommandInterface {
    public:
        bool execute(const std::vector<std::string>& args) override;
    };

    class EchoCommand : public CommandInterface {
    public:
        bool execute(const std::vector<std::string>& args) override;
    };

    class CdCommand : public CommandInterface {
    public:
        bool execute(const std::vector<std::string>& args) override;
    };

    class TypeCommand : public CommandInterface {
    public:
        TypeCommand(const std::unordered_set<std::string>& builtins);
        bool execute(const std::vector<std::string>& args) override;
    private:
        const std::unordered_set<std::string>& builtins;
    };
}

#endif // COMMANDS_H
