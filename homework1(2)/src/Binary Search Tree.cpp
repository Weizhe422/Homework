#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <unordered_set>
using namespace std;

struct Node {
    int data; Node* l, * r;
    Node(int v) : data(v), l(nullptr), r(nullptr) {}
};

Node* insertNode(Node* t, int x) {
    if (!t) return new Node(x);
    if (x < t->data) t->l = insertNode(t->l, x);
    else if (x > t->data) t->r = insertNode(t->r, x);
    return t;
}
int height(Node* t) { return t ? 1 + max(height(t->l), height(t->r)) : 0; }
void destroy(Node* t) { if (!t) return; destroy(t->l); destroy(t->r); delete t; }

Node* minNode(Node* t) { while (t && t->l) t = t->l; return t; }
Node* deleteNode(Node* t, int x) {
    if (!t) return nullptr;
    if (x < t->data) t->l = deleteNode(t->l, x);
    else if (x > t->data) t->r = deleteNode(t->r, x);
    else {
        if (!t->l || !t->r) {
            Node* c = t->l ? t->l : t->r;
            delete t; return c;
        }
        Node* s = minNode(t->r);
        t->data = s->data;
        t->r = deleteNode(t->r, s->data);
    }
    return t;
}

int main() {
    srand((unsigned)time(0));

    // (a)
    const int ns[] = { 100,500,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000 };
    for (int n : ns) {
        Node* root = nullptr;
        unordered_set<int> used; used.reserve((size_t)(n * 1.3));
        for (int cnt = 0; cnt < n; ) {
            int v = rand();
            if (used.insert(v).second) { root = insertNode(root, v); cnt++; }
        }
        int h = height(root);
        cout << "n=" << n << " height=" << h
            << " ratio=" << (h / log2((double)n)) << "\n";
        destroy(root);
    }

    // (b) 只示範呼叫 deleteNode，不輸出
    Node* t = nullptr;
    int keys[] = { 50,30,70,20,40,60,80 };
    for (int x : keys) t = insertNode(t, x);
    t = deleteNode(t, 20);
    t = deleteNode(t, 30);
    t = deleteNode(t, 50);
    destroy(t);

    return 0;
}
