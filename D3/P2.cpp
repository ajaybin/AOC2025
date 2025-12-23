#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<utility>
#include<algorithm>
#include <cmath>

using namespace std;
using ull = unsigned long long;

int sz = 12; // Change to 2 for P1 behavior

int main() {
    string filename = "input";
    ifstream ifile (filename);
    if (!ifile) {
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }

    string line;
    
    ull sum_joltage = 0;
    while (getline(ifile, line)) {
        vector<pair<int, int>> values;
        for (int i = 0; i < line.length(); ++i) {
            int val = line[i] - '0';
            values.push_back({val, i});
        }
        std::sort(values.begin(), values.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.first == b.first) return a.second < b.second;
            else return a.first > b.first;
        });
        int lb = 0;
        int ub = values.size() - sz;
        for (int i = 0; i < sz; ++i) {
            ull max_val;
            ull multiplier = pow (10, sz - 1 - i);

            for (int j = 0; j < values.size(); ++j) {
                pair<int, int> p = values[j];
                //cout << "j: " << j << " ( " << p.first << ", " << p.second << " ) lb: " << lb << " ub: " << ub << endl;
                if (p.second >= lb && p.second <= ub) {
                    max_val = p.first * multiplier;
                    lb = p.second + 1;
                    ub = values.size() - sz + i + 1;
                    break;
                }
            }
            //cout << "max_val: " << max_val << endl;
            sum_joltage += max_val;
        }
    }
    
    std::cout << "Sum joltage: " << sum_joltage << endl;

    ifile.close();
    return 0;
}