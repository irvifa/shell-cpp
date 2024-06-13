#include "shell.h"
#include "commands.h"
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

namespace ShellNamespace {
    Shell::Shell() {
        builtins = {"exit", "echo", "type", "cd"};
        commands["exit"] = std::make_unique<ExitCommand>();
        commands["echo"] = std::make_unique<EchoCommand>();
        commands["cd"] = std::make_unique<CdCommand>();
        commands["type"] = std::make_unique<TypeCommand>(builtins); // Pass builtins to TypeCommand
    }

    void Shell::run() {
        std::string input;

        while (true) {
            // Print the prompt
            std::cout << "$ ";

            // Read user input
            std::getline(std::cin, input);

            // If input is empty, continue to next iteration
            if (input.empty()) {
                continue;
            }

            // Tokenize the input into a Command
            Command command = tokenize(input);

            // Validate and execute the command
            if (!execute(command)) {
                runExternalCommand(command);
            }
        }
    }

    Shell::Command Shell::tokenize(const std::string& input) {
        std::stringstream ss(input);
        std::string token;
        std::vector<std::string> tokens;

        while (ss >> token) {
            tokens.push_back(token);
        }

        if (tokens.empty()) {
            return Command{"", {}};
        }

        std::string name = tokens[0];
        tokens.erase(tokens.begin());
        return Command{name, tokens};
    }

    bool Shell::execute(const Command& command) {
        auto it = commands.find(command.name);
        if (it != commands.end()) {
            it->second->execute(command.args);
            return true;
        }
        return false;
    }

    void Shell::runExternalCommand(const Command& command) {
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            std::vector<char*> args;
            args.push_back(const_cast<char*>(command.name.c_str()));
            for (const std::string& arg : command.args) {
                args.push_back(const_cast<char*>(arg.c_str()));
            }
            args.push_back(nullptr);

            execvp(args[0], args.data());
            // If execvp returns, there was an error
            std::cerr << command.name << ": command not found" << std::endl;
            exit(1);
        } else if (pid > 0) {
            // Parent process
            int status;
            waitpid(pid, &status, 0);
        } else {
            std::cerr << "Failed to fork" << std::endl;
        }
    }
}
