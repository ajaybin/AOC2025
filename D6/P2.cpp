#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include <numeric>
#include <algorithm>
#include <iterator>

using namespace std;
using ull = unsigned long long;
int main() {
    vector<int> starting_positions;
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
    string operator_string = lines.back();
    istringstream iss(operator_string);
    lines.pop_back();
    while (iss >> opr) {
        oprs.push_back(opr);
    }
    for(int i = 0; i < operator_string.length(); ++i) {
        if (operator_string[i] != ' ') {
            starting_positions.push_back(i);
        }
    }
    starting_positions.push_back(operator_string.length()+1);


    //Extract operands
    vector<vector<string>> operands(oprs.size());
    for (auto l : lines) {
        for (int i = 0; i < oprs.size(); ++i) {
            int start_pos = starting_positions[i];
            int end_pos   = starting_positions[i+1] - 1;
            vector<string>* iter_operands = &operands[i];
            int j = 0;
            for (int pos = start_pos; pos < end_pos; ++pos, ++j) {
                if (j >= iter_operands->size()) {
                    iter_operands->push_back("");
                }
                if (l[pos] == ' ') {
                    iter_operands->at(j) = iter_operands->at(j) + "";
                } else {
                    iter_operands->at(j) = iter_operands->at(j) + l[pos];
                }
            }
        }
    }

    //operate
    
    ull sum = 0;
    for (int op = 0; op < oprs.size(); ++op) {
        ull s = 0;
        vector<ull> ull_operands;
        std::transform(operands[op].cbegin(), operands[op].cend(), back_inserter(ull_operands), [](string s) {
            return stoull(s);
        });
        if (oprs[op] == '+') {
            s = std::accumulate(ull_operands.begin(), ull_operands.end(), 0ULL);
            cout << "+ s : " << s << endl;
            sum += s;
        } else if (oprs[op] == '*') {
            s = std::accumulate(ull_operands.begin(), ull_operands.end(), 1ULL, std::multiplies{});
            cout << "* s : " << s << endl;
            sum += s;
        }
    }
    
    cout << sum << endl;
    ifile.close();
    return 0;
}