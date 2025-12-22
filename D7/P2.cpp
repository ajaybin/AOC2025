#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>

using namespace std;
using ull = unsigned long long;

int main() {
    ifstream ifile("input");
    if (!ifile) {
        cerr << "failed to open file";
        return 1;
    }

    vector<string> lines;
    string line;
    while(getline(ifile, line)) {
        lines.push_back(line);
    }

    size_t starting_pos = 0;
    starting_pos = lines[0].find('S');

    int manifold_width = lines[0].size();
    vector<ull> prev_num_beams(manifold_width, 0);

    prev_num_beams[starting_pos] = 1;
    for (int l = 1; l < lines.size(); ++l) {
        vector<ull> curr_num_beams(manifold_width, 0);
        line = lines[l];
        for (int pos = 0; pos < line.length(); ++pos) {
            if (line[pos] == '^') {
                if (pos > 0) curr_num_beams[pos-1] += prev_num_beams[pos];
                if (pos < manifold_width-1) curr_num_beams[pos+1] += prev_num_beams[pos];
            } else {
                curr_num_beams[pos] += prev_num_beams[pos];
            }
        }
        prev_num_beams = curr_num_beams;
    }

    ull total = accumulate(prev_num_beams.begin(), prev_num_beams.end(), 0ULL);

    return 0;
}
