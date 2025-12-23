#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <sstream>
#include <algorithm>

using namespace std;
using ull = unsigned long long;
struct point_t {
    int coord[3];
    int circuit_idx;
};

struct dist_pair {
    point_t* p;
    point_t* q;
    ull distance;
};

ull get_distance(point_t p, point_t q) {
    return pow((p.coord[0] - q.coord[0]), 2) + pow((p.coord[1] - q.coord[1]), 2) + pow((p.coord[2] - q.coord[2]), 2);
}

int main() {
    vector<point_t> points;
    ifstream ifile("input");
    if (!ifile) {
        cerr << "Unable to open the file";
        return 1;
    }

    string line;
    while (getline(ifile, line)) {
        stringstream ss(line);
        string token;
        point_t p;
        int i = 0;
        while (getline(ss, token, ',')) {
            p.coord[i] = stoi(token);
            p.circuit_idx = -1;
            ++i;
        }
        points.push_back(p);
    }

    vector<dist_pair> distances;
    for (int p = 0; p < points.size()-1; ++p) {
        for (int q = p+1; q < points.size(); ++q) {
            dist_pair dp;
            dp.p = &points[p];
            dp.q = &points[q];
            dp.distance = get_distance(*dp.p, *dp.q);
            distances.push_back(dp);
        }
    }

    sort(distances.begin(), distances.end(), [](dist_pair a, dist_pair b){
        return a.distance < b.distance;
    });

    vector<vector<point_t*>> circuits;
    for (int i = 0; i < 1000; ++i) {
        dist_pair dp = distances[i];
        if (dp.p->circuit_idx == -1 && dp.q->circuit_idx == -1) {
            dp.p->circuit_idx = circuits.size();
            dp.q->circuit_idx = circuits.size();

            vector<point_t*> vp;
            vp.push_back(dp.p);
            vp.push_back(dp.q);
            circuits.push_back(vp);
        } else if (dp.p->circuit_idx == -1) {
            dp.p->circuit_idx = dp.q->circuit_idx;
            circuits[dp.p->circuit_idx].push_back(dp.p);
        } else if (dp.q->circuit_idx == -1) {
            dp.q->circuit_idx = dp.p->circuit_idx;
            circuits[dp.q->circuit_idx].push_back(dp.q);
        } else if (dp.p->circuit_idx == dp.q->circuit_idx) {
            continue;
        } else if (dp.p->circuit_idx != dp.q->circuit_idx) {
            vector<point_t*> vp1;
            vector<point_t*> vp2;

            vp1 = circuits[dp.p->circuit_idx];
            vp2 = circuits[dp.q->circuit_idx];

            if (vp1.size() <= vp2.size()) {
                circuits[dp.p->circuit_idx].clear();
                for (auto p : vp1) {
                    circuits[dp.q->circuit_idx].push_back(p);
                    p->circuit_idx = dp.q->circuit_idx;
                }
            } else {
                circuits[dp.q->circuit_idx].clear();   
                for (auto q : vp2) {
                    circuits[dp.p->circuit_idx].push_back(q);                 
                    q->circuit_idx = dp.p->circuit_idx;
                }
            }
        }
    }

    sort(circuits.begin(), circuits.end(), [](vector<point_t*> a, vector<point_t*> b) {
        return a.size() > b.size();
    });
    cout << circuits[0].size() * circuits[1].size() * circuits[2].size() << endl;
    return 0;
}