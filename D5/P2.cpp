#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>


using namespace std;
using ull = unsigned long long;
using p_t = pair<ull,ull>;
using v_t = vector<p_t>;

v_t::iterator merge(v_t::iterator b, v_t::iterator e, v_t::iterator i) {
    *i = *b;
    for (auto it = b+1; it != e; ++it) {
        if (it->first <= i->second)
            i->second = max(it->second, i->second);
        else {
            *(++i) = *it;
        }
    }
    return ++i;
}

int main() {
    ifstream ifile("input");
    string line;
    ull numFresh = 0;
    v_t intervals;
    while(getline(ifile, line)) {
        if (line != "") {
            size_t pos = line.find('-');
            if (pos != string::npos) {
                //range
                string f = line.substr(0, pos);
                string s = line.substr(pos+1);
                pair<ull,ull> p = {stoull(f), stoull(s)};
                intervals.push_back(p);
            } else {
            }
        }
    }

    sort(intervals.begin(), intervals.end(), [](const p_t& a, const p_t& b) {
        return a.first < b.first;
    });
    v_t result(intervals.size());
    auto end_it = merge(intervals.begin(), intervals.end(), result.begin());
    result.resize(end_it - result.begin());
    result.shrink_to_fit();
    for (auto r : result) {
        numFresh += (r.second - r.first + 1);
    }
    cout << "Total Fresh produce : " << numFresh << endl;

    ifile.close();
    return 0;
}