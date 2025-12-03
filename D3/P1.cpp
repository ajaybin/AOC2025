#include<iostream>
#include<string>
#include<fstream>

using namespace std;

int main() {
    string filename = "input";
    ifstream ifile (filename);
    if (!ifile) {
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }

    string line;
    int max_joltage_t = 0;
    int max_joltage_u = 0;
    int sum_joltage = 0;
    while (getline(ifile, line)) {
        max_joltage_t = line[0] - '0';
        max_joltage_u = line[1] - '0';
        for (auto i = 0; i < line.length()-1; ++i) {
            int num = line[i] - '0';
            int num_plus1 = line[i+1] - '0';
            if (num > max_joltage_t) {
                max_joltage_t = num;
                max_joltage_u = num_plus1;
            }
            if (num_plus1 > max_joltage_u) {
                max_joltage_u = num_plus1;
            }
        }
        //cout << "Max joltage: " << max_joltage_t << max_joltage_u << endl;
        sum_joltage += max_joltage_t * 10 + max_joltage_u;
    }
    std::cout << "Sum joltage: " << sum_joltage << endl;

    ifile.close();
    return 0;
}