#include <iostream>
#include <string>

int main() {
    std::string command;

    while (true) {
        // Print the prompt
        std::cout << "$ ";

        // Read user input
        std::getline(std::cin, command);

        // If command is empty, continue to next iteration
        if (command.empty()) {
            continue;
        }

        // Print the command not found message
        std::cout << command << ": command not found" << std::endl;
    }

    return 0;
}
