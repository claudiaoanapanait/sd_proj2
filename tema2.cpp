#include <iostream>
#include <cstdlib>

using namespace std;

struct TreapNod { //node declaration
    int data;
    int priority;
    TreapNod *l, *r;

    TreapNod(int d) { //constructor
        data = d;
        priority = rand() % 100;
        l = r = nullptr;
    }
};

void rotLeft(TreapNod *&root) { //left rotation
    TreapNod *R = root->r;
    TreapNod *X = root->r->l;
    R->l = root;
    root->r = X;
    root = R;
}

void rotRight(TreapNod *&root) { //right rotation
    TreapNod *L = root->l;
    TreapNod *Y = root->l->r;
    L->r = root;
    root->l = Y;
    root = L;
}

void insertNod(TreapNod *&root, int d) { //insertion
    if (root == nullptr) {
        root = new TreapNod(d);
        return;
    }
    if (d < root->data) {
        insertNod(root->l, d);
        if (root->l != nullptr && root->l->priority > root->priority)
            rotRight(root);
    } else {
        insertNod(root->r, d);
        if (root->r != nullptr && root->r->priority > root->priority)
            rotLeft(root);
    }
}

bool searchNod(TreapNod *root, int key) {
    if (root == nullptr)
        return false;
    if (root->data == key)
        return true;
    if (key < root->data)
        return searchNod(root->l, key);
    return searchNod(root->r, key);
}

void deleteNod(TreapNod *&root, int key) {
    //node to be deleted which is a leaf node
    if (root == nullptr)
        return;
    if (key < root->data)
        deleteNod(root->l, key);
    else if (key > root->data)
        deleteNod(root->r, key);
        //node to be deleted which has two children
    else {
        if (root->l == nullptr && root->r == nullptr) {
            delete root;
            root = nullptr;
        } else if (root->l && root->r) {
            if (root->l->priority < root->r->priority) {
                rotLeft(root);
                deleteNod(root->l, key);
            } else {
                rotRight(root);
                deleteNod(root->r, key);
            }
        }
            //node to be deleted has only one child
        else {
            TreapNod *child = (root->l) ? root->l : root->r;
            TreapNod *curr = root;
            root = child;
            delete curr;
        }
    }
}

void displayTreap(TreapNod *root, int space = 0, int height = 10) { //display treap
    if (root == nullptr)
        return;
    space += height;
    displayTreap(root->l, space);
    cout << endl;
    for (int i = height; i < space; i++)
        cout << ' ';
    cout << root->data << "(" << root->priority << ")\n";
    cout << endl;
    displayTreap(root->r, space);
}

void findPreSuc(TreapNod *root, TreapNod *&pre, TreapNod *&suc, int key) {
    // Base case
    if (root == nullptr) return;

    // If key is present at root
    if (root->data == key) {
        // the maximum value in left subtree is predecessor
        if (root->l != nullptr) {
            TreapNod *tmp = root->l;
            while (tmp->r)
                tmp = tmp->r;
            pre = tmp;
        }

        // the minimum value in right subtree is successor
        if (root->r != nullptr) {
            TreapNod *tmp = root->r;
            while (tmp->l)
                tmp = tmp->l;
            suc = tmp;
        }
        return;
    }

    // If key is smaller than root's key, go to left subtree
    if (root->data > key) {
        suc = root;
        findPreSuc(root->l, pre, suc, key);
    } else // go to right subtree
    {
        pre = root;
        findPreSuc(root->r, pre, suc, key);
    }
}

int main() {
    int n, v[100];
    cin >> n;
    for (int i = 0; i < n; ++i)
        v[i] = i;
    TreapNod *root = nullptr;
    for (int i = 0; i < n; i++)
        insertNod(root, v[i]);
    cout << "Constructed Treap:\n\n";
    displayTreap(root);
    cout << "\nDeleting node 8:\n\n";
    deleteNod(root, 8);
    displayTreap(root);
    cout << "\nDeleting node 3:\n\n";
    deleteNod(root, 3);
    displayTreap(root);

    int key = (rand() % 100) + 1;

    TreapNod *pre = nullptr, *suc = nullptr;

    findPreSuc(root, pre, suc, key);
    if (pre != nullptr)
        cout << "Predecessor is " << pre->data << endl;
    else
        cout << "No Predecessor";

    if (suc != nullptr)
        cout << "Successor is " << suc->data;
    else
        cout << "No Successor";
    return 0;
}

