#include<iostream>
#include<string>
#include<fstream>
#include<vector>

using namespace std;
using ull = unsigned long long;

bool is_double_num(const string& s) {
    if (s.size() % 2 != 0) {
        return false;
    } else {
        //cout << s.substr(0, s.size() / 2) << " " << s.substr(s.size() / 2) << endl;
        return s.substr(0, s.size() / 2) == s.substr(s.size() / 2);
    }
}

int main() {
    string filename = "input";
    ifstream ifile(filename);
    if (!ifile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }

    std::string line;
    ifile >> line;
    //cout << line << endl;

    std::string delim = ",";
    size_t pos = 0;
    vector<string> tokens;
    while ((pos = line.find(delim)) != std::string::npos) {
        std::string token = line.substr(0, pos);
        //cout << token << endl;
        tokens.push_back(token);
        line.erase(0, pos + delim.length());
    }
    //cout << line << endl;
    tokens.push_back(line);

    ull lb = 0, ub = 0;
    ull sum = 0;
    for (const auto& token : tokens) {
        size_t pos = token.find("-");
        if (pos != std::string::npos) {
            lb = stoull(token.substr(0, pos));
            ub = stoull(token.substr(pos + 1));
            //cout << "Lower bound: " << lb << ", Upper bound: " << ub << endl;
        }
        for (ull i = lb; i <= ub; ++i) {
            if (is_double_num(to_string(i))) {
                sum += i;
            }
        }
    }
    cout << sum << endl;

    ifile.close();
    return 0;
}