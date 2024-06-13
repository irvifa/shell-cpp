#include "commands.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <vector>

namespace ShellNamespace {

    bool ExitCommand::execute(const std::vector<std::string>& args) {
        if (args.size() == 1) {
            try {
                int exit_code = std::stoi(args[0]);
                exit(exit_code);
            } catch (const std::invalid_argument&) {
                std::cerr << "exit: invalid status code" << std::endl;
                return true;
            } catch (const std::out_of_range&) {
                std::cerr << "exit: status code out of range" << std::endl;
                return true;
            }
        } else {
            std::cerr << "exit: invalid number of arguments" << std::endl;
            return true;
        }
        return false;
    }

    bool EchoCommand::execute(const std::vector<std::string>& args) {
        bool omit_newline = false;
        std::vector<std::string> echo_args = args;

        if (!echo_args.empty() && echo_args[0] == "-n") {
            omit_newline = true;
            echo_args.erase(echo_args.begin());
        }

        std::string output;
        for (size_t i = 0; i < echo_args.size(); ++i) {
            output += echo_args[i];
            if (i != echo_args.size() - 1) {
                output += " ";
            }
        }

        // Use write system call to output the result
        write(STDOUT_FILENO, output.c_str(), output.size());
        if (!omit_newline) {
            write(STDOUT_FILENO, "\n", 1);
        }
        return true;
    }

}
