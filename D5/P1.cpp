#include <iostream>
#include <fstream>

using ull = unsigned long long;
using namespace std;
struct Node {
    ull low;
    ull high;
    ull min;
    ull max;
    Node* left;
    Node* right;
};

Node* createNode(pair<ull,ull> i) {
    Node* n = new Node;
    n->low = i.first;
    n->high = i.second;
    n->min = i.first;
    n->max = i.second;
    n->left = nullptr;
    n->right = nullptr;
    return n;
}

Node* insertNode(Node* root, pair<ull,ull> i) {
    if (root == nullptr) {
        return createNode(i);
    }

    int root_low = root->low;

    if (i.first < root_low) {
        root->left = insertNode(root->left, i);
    } else {
        root->right = insertNode(root->right, i);
    }

    if (root->max < i.second) {
        root->max = i.second;
    }
    if (root->min > i.first) {
        root->min = i.first;
    }

    return root;

}

bool isPresentInInterval(Node* root, ull num) {
    if (root == nullptr) return false;

    if (num > root->max || num < root->min) return false;

    if (num >= root->low && num <= root->high) return true;

    if (root->left != nullptr && root->left->max >= num && root->left->min <= num) {
        return isPresentInInterval(root->left, num);
    }

    if (root->right != nullptr && root->right->max >= num && root->right->min <= num) {
        return isPresentInInterval(root->right, num);
    }

    return false;
}

int main() {
    ifstream ifile("input");
    string line;
    Node* root = nullptr;
    int numFresh = 0;
    while(getline(ifile, line)) {
        if (line != "") {
            size_t pos = line.find('-');
            if (pos != string::npos) {
                //range
                string f = line.substr(0, pos);
                string s = line.substr(pos+1);
                pair<ull,ull> p = {stoull(f), stoull(s)};
                root = insertNode(root, p);
            } else {
                //Number
                if (isPresentInInterval(root, stoull(line))) {
                    //cout << line << " is fresh" << endl;
                    ++numFresh;
                } else {
                    //cout << line << " has spoiled" << endl;
                }
            }
        }
    }
    cout << "Total Fresh produce : " << numFresh << endl;

    ifile.close();
    return 0;
}