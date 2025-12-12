#include <iostream>
#include <string>
#include <vector>
#include <fstream>


using namespace std;
using vvc = vector<vector<char>>;
int SIZE_ROW = 0;
int SIZE_COL = 0;
int can_access = 0;
struct node
{
    node* n;
    node* s;
    node* e;
    node* w;
    node* ne;
    node* nw;
    node* se;
    node* sw;

    char c = '.';
    int ispaper() {
        return (c == '@');
    }
};

node* create_node(char data) {
    node* nd = new node();
    
    nd->c = data;
    nd->n = NULL;
    nd->e = NULL;
    nd->s = NULL;
    nd->w = NULL;
    nd->ne = NULL;
    nd->nw = NULL;
    nd->sw = NULL;
    nd->se = NULL;
    return nd;
}

node* create_dll(vvc* warehouse, int row, int col, vector<vector<node*>>* visited) {
    if (row >= SIZE_ROW || col >= SIZE_COL || row < 0 || col < 0) {
        return NULL;
    }

    if (visited->at(row)[col] != NULL) {
        return visited->at(row)[col];
    }
    node* temp = create_node(warehouse->at(row)[col]);
    visited->at(row)[col] = temp;

    temp->e = create_dll(warehouse, row, col+1, visited);
    temp->s = create_dll(warehouse, row+1, col, visited);
    temp->se = create_dll(warehouse, row+1, col+1, visited);
    temp->sw = create_dll(warehouse, row+1, col-1, visited);

    temp->w =  create_dll(warehouse, row, col-1, visited);
    temp->n =  create_dll(warehouse, row-1, col, visited);
    temp->ne = create_dll(warehouse, row-1, col+1, visited);
    temp->nw = create_dll(warehouse, row-1, col-1, visited);

    int neighbours = 0;
    if (temp->ispaper()) {
        if (temp->e != NULL) {
            neighbours += temp->e->ispaper();
        }
        if (temp->w != NULL) {
            neighbours += temp->w->ispaper();
        }
        if (temp->n != NULL) {
            neighbours += temp->n->ispaper();
        }
        if (temp->s != NULL) {
            neighbours += temp->s->ispaper();
        }
        if (temp->nw != NULL) {
            neighbours += temp->nw->ispaper();
        }
        if (temp->ne != NULL) {
            neighbours += temp->ne->ispaper();
        }
        if (temp->se != NULL) {
            neighbours += temp->se->ispaper();
        }
        if (temp->sw != NULL) {
            neighbours += temp->sw->ispaper();
        }
        if (neighbours < 4) {
            cout << "row:" << row << " col:" << col << endl;
            can_access += 1;
        }
    }
    return temp;
}

void create_warehouse(vvc* warehouse) {
    string filename = "input";
    ifstream ifile(filename);
    if (!ifile) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(ifile, line)) {
        vector<char> vc;
        vc.insert(vc.cend(), line.begin(), line.end());
        warehouse->push_back(vc);
    }
    SIZE_ROW = warehouse->size();
    SIZE_COL = warehouse->at(0).size();
    ifile.close();
}

int main () {
    vvc warehouse;
    create_warehouse(&warehouse);

    vector<vector<node*>> visited(SIZE_ROW, vector<node*>(SIZE_COL, NULL));
    node* head = create_dll(&warehouse, 0, 0, &visited);
    cout << can_access << endl;
    return 0;
}
