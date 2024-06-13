#ifndef COMMANDS_H
#define COMMANDS_H

#include "command_interface.h"
#include <vector>
#include <string>

namespace ShellNamespace {
    class ExitCommand : public CommandInterface {
    public:
        bool execute(const std::vector<std::string>& args) override;
    };

    class EchoCommand : public CommandInterface {
    public:
        bool execute(const std::vector<std::string>& args) override;
    };
}

#endif // COMMANDS_H
