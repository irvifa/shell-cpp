#include "shell.h"
#include "commands.h"
#include <iostream>
#include <sstream>

namespace ShellNamespace {
    Shell::Shell() {
        commands["exit"] = std::make_unique<ExitCommand>();
        commands["echo"] = std::make_unique<EchoCommand>();
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
                std::cout << command.name << ": command not found" << std::endl;
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
}
