#include <iostream>
#include <fstream>
#include <string>

int main() {
    int dial = 50;
    int password = 0;
    std::ifstream i_file("input");
    if (!i_file.is_open()) {
        std::cerr << "Failed to open file: input"  << '\n';
        return 1;
    }

    std::string line;
    while (std::getline(i_file, line)) {
        std::string dir = line.substr(0, 1);
        int num = stoi(line.substr(1));
        std::cout << "Direction:" << dir << " Number:" << num << '\n';
        num = num % 100;
        if (dir == "R") {
            dial = (dial + num) % 100;
        } else if (dir == "L") {
            dial = (dial + 100 - num) % 100;
        }
        if (dial == 0) {
            password +=1;
        }
    }
    std::cout << "Password: " << password << '\n';
    i_file.close();
    return 0;
}