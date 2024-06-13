#include "commands.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstring>

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

    TypeCommand::TypeCommand(const std::unordered_set<std::string>& builtins)
        : builtins(builtins) {}

    bool TypeCommand::execute(const std::vector<std::string>& args) {
        if (args.size() != 1) {
            std::cerr << "type: invalid number of arguments" << std::endl;
            return true;
        }

        std::string command_name = args[0];

        // Check if it's a built-in command
        if (builtins.find(command_name) != builtins.end()) {
            std::cout << command_name << " is a shell builtin" << std::endl;
            return true;
        }

        // Check if it's an external command in PATH
        char *path_env = getenv("PATH");
        if (path_env == nullptr) {
            std::cerr << "type: PATH environment variable not set" << std::endl;
            return true;
        }

        // Copy path_env to a local buffer because strtok modifies the string
        char path_env_copy[strlen(path_env) + 1];
        strcpy(path_env_copy, path_env);

        std::vector<std::string> paths;
        char *path_token = std::strtok(path_env_copy, ":");
        while (path_token != nullptr) {
            paths.push_back(path_token);
            path_token = std::strtok(nullptr, ":");
        }

        for (const std::string &path : paths) {
            std::string full_path = path + "/" + command_name;
            if (access(full_path.c_str(), X_OK) == 0) {
                std::cout << command_name << " is " << full_path << std::endl;
                return true;
            }
        }

        std::cout << command_name << ": not found" << std::endl;
        return true;
    }

}
