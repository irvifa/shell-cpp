#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>

class Command {
public:
    std::string name;
    int exit_code;

    Command(const std::string& name, int exit_code = -1)
        : name(name), exit_code(exit_code) {}
};

class Shell {
public:
    void run() {
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

private:
    Command tokenize(const std::string& input) {
        std::stringstream ss(input);
        std::string token;
        std::vector<std::string> tokens;

        while (ss >> token) {
            tokens.push_back(token);
        }

        if (tokens.empty()) {
            return Command("");
        }

        if (tokens[0] == "exit" && tokens.size() == 2) {
            try {
                int exit_code = std::stoi(tokens[1]);
                return Command(tokens[0], exit_code);
            } catch (const std::invalid_argument&) {
                return Command(tokens[0], -1);
            } catch (const std::out_of_range&) {
                return Command(tokens[0], -1);
            }
        }

        return Command(tokens[0]);
    }

    bool execute(const Command& command) {
        if (command.name == "exit") {
            if (command.exit_code != -1) {
                exit(command.exit_code);
            } else {
                std::cerr << "exit: invalid status code" << std::endl;
                return true;
            }
        }

        return false;
    }
};

int main() {
    Shell shell;
    shell.run();
    return 0;
}
