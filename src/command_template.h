#ifndef COMMAND_TEMPLATE_H
#define COMMAND_TEMPLATE_H

#include "command_interface.h"
#include <functional>

namespace ShellNamespace {
    template<typename Func>
    class CommandTemplate : public CommandInterface {
    public:
        CommandTemplate(Func func) : commandFunc(func) {}
        bool execute(const std::vector<std::string>& args) override {
            return commandFunc(args);
        }
    private:
        Func commandFunc;
    };
}

#endif // COMMAND_TEMPLATE_H
