#include <iostream>
#include <string>
#include <vector>
#include <fstream>


using namespace std;
using vvc = vector<vector<char>>;
int SIZE_ROW = 0;
int SIZE_COL = 0;
int total_removed = 0;
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

    int neighbours;
    void calc_neighbours() {
        neighbours = 0;
        if (ispaper()) {
            if (e != NULL) {
                neighbours += e->ispaper();
            }
            if (w != NULL) {
                neighbours += w->ispaper();
            }
            if (n != NULL) {
                neighbours += n->ispaper();
            }
            if (s != NULL) {
                neighbours += s->ispaper();
            }
            if (nw != NULL) {
                neighbours += nw->ispaper();
            }
            if (ne != NULL) {
                neighbours += ne->ispaper();
            }
            if (se != NULL) {
                neighbours += se->ispaper();
            }
            if (sw != NULL) {
                neighbours += sw->ispaper();
            }
        }  
        return; 
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
    
    temp->calc_neighbours();
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

int remove_paper(node* head) {
    int removed = 0;
    node* rPtr;
    node* dPtr = head;

    while (dPtr) {
        rPtr = dPtr;
        while (rPtr) {
            if (rPtr->ispaper() && rPtr->neighbours < 4) {
                removed += 1;
                rPtr->c = 'x';
            }
            rPtr = rPtr->e;
        }
        dPtr = dPtr->s;
    }
    return removed;
}

void recalculate_neighbours(node* head) {
    node* rPtr;
    node* dPtr = head;

    while (dPtr) {
        rPtr = dPtr;
        while (rPtr) {
            rPtr->calc_neighbours();
            rPtr = rPtr->e;
        }
        dPtr = dPtr->s;
    }
    return;    
}

int main () {
    vvc warehouse;
    create_warehouse(&warehouse);

    vector<vector<node*>> visited(SIZE_ROW, vector<node*>(SIZE_COL, NULL));
    node* head = create_dll(&warehouse, 0, 0, &visited);

    int removed = 0;
    do {
        removed = remove_paper(head);
        recalculate_neighbours(head);
        total_removed += removed;
    } while (removed != 0);

    cout << "total_removed:" << total_removed << endl;
    return 0;
}
