#ifndef COMMAND_INTERFACE_H
#define COMMAND_INTERFACE_H

#include <vector>
#include <string>

namespace ShellNamespace {
    class CommandInterface {
    public:
        virtual ~CommandInterface() = default;
        virtual bool execute(const std::vector<std::string>& args) = 0;
    };
}

#endif // COMMAND_INTERFACE_H
