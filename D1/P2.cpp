#include <iostream>
#include <fstream>
#include <string>

int main() {
    int dial = 50;
    int password = 0;
    std::string filename = "input";
    std::ifstream i_file(filename);
    if (!i_file.is_open()) {
        std::cerr << "Failed to open file: "<< filename << '\n';
        return 1;
    }

    std::string line;
    while (std::getline(i_file, line)) {
        std::string dir = line.substr(0, 1);
        int num = stoi(line.substr(1));
        std::cout << "Direction:" << dir << " Number:" << num << '\n';
        password += (num/100);
        num = num % 100;
        if (dir == "R") {
            password += ((dial + num) > 100) ? 1 : 0;
            dial = (dial + num) % 100;
        } else if (dir == "L") {
            password += ((dial > 0 && (dial - num) < 0) ? 1 : 0);
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