#ifndef COMMANDS_H
#define COMMANDS_H

#include "command_interface.h"
#include "command_template.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <memory>

namespace ShellNamespace {
    class ExitCommand : public CommandTemplate<std::function<bool(const std::vector<std::string>&)>> {
    public:
        ExitCommand();
    };

    class EchoCommand : public CommandTemplate<std::function<bool(const std::vector<std::string>&)>> {
    public:
        EchoCommand();
    };

    class CdCommand : public CommandTemplate<std::function<bool(const std::vector<std::string>&)>> {
    public:
        CdCommand();
    };

    class TypeCommand : public CommandTemplate<std::function<bool(const std::vector<std::string>&)>> {
    public:
        TypeCommand(const std::unordered_set<std::string>& builtins);
    };

    void initializeBuiltins(std::unordered_map<std::string, std::unique_ptr<CommandInterface>>& commands,
                            std::unordered_set<std::string>& builtins);
}

#endif // COMMANDS_H
