#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
using namespace std;
using pt = pair<int, int>;
using vvc = vector<set<int>>;
set<pt> visited;

int manifold_size;
int manifold_width;

int beam_split(pt pos, vvc* splitters) {
    int num_split = 0;
    bool hit_splitter = false;
    pt left_split;
    pt right_split;

    if (pos.first >= manifold_size || pos.second < 0 || pos.second >= manifold_width) return 0;

    for (pt new_pos = pos; new_pos.first < manifold_size; ++new_pos.first) {
        if(visited.contains(new_pos)) return num_split;
        visited.insert(new_pos);

        set<int> cur_splitters = splitters->at(new_pos.first);
        if (cur_splitters.contains(new_pos.second)) {
            hit_splitter = true;
            num_split++;
            left_split  = {new_pos.first, new_pos.second-1};
            right_split = {new_pos.first, new_pos.second+1};
            break;
        }
    }
    if (hit_splitter) {
        num_split += beam_split(left_split, splitters);
        num_split += beam_split(right_split, splitters);
    }
    return num_split;
}

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

    pt starting_pos = {0,0}; // {line number, index}
    for (int pos = 0; pos < lines[0].length(); ++pos) {
        if (lines[0][pos] == 'S') {
            starting_pos = {0, pos};
            break;
        }
    }
    vvc splitters(lines.size());
    for (int l = 1; l < lines.size(); ++l) {
        line = lines[l];
        for (int pos = 0; pos < line.length(); ++pos) {
            if (line[pos] == '^') {
                splitters[l].insert(pos);
            }
        }
    }
    manifold_size = lines.size();
    manifold_width = lines[0].size();
    int num_split = beam_split(starting_pos, &splitters);
    cout << num_split << endl;
    return 0;
}
