#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include <numeric>
using namespace std;
using ull = unsigned long long;
int main() {
    //Read file
    ifstream ifile("input");
    if (!ifile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }    
    vector<string> lines; 
    string line;
    while(getline(ifile, line)) {
        lines.push_back(line);
    }

    //Extract operators
    char opr;
    vector<char> oprs;
    istringstream iss(lines.back());
    lines.pop_back();
    while (iss >> opr) {
        oprs.push_back(opr);
    }

    //Extract operands
    vector<vector<ull>> operands(oprs.size());
    string operand;
    int i;
    for (auto l : lines) {
        i = 0;
        istringstream opss(l);
        while(opss >> operand) {
            operands[i++].push_back(stoi(operand));
        }
    }

    //operate
    ull sum = 0;
    for (int op = 0; op < oprs.size(); ++op) {
        if (oprs[op] == '+') {
            sum += std::accumulate(operands[op].begin(), operands[op].end(), 0ULL);
        } else if (oprs[op] == '*') {
            sum += std::accumulate(operands[op].begin(), operands[op].end(), 1ULL, std::multiplies{});
        }
    }
    cout << sum << endl;
    ifile.close();
    return 0;
}