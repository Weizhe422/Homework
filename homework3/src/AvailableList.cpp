#include "AvailableList.h"

AvailableList::AvailableList() : available(nullptr) {}

AvailableList& AvailableList::getInstance() {
    static AvailableList instance;
    return instance;
}

AvailableList::~AvailableList() {
    TermNode* current = available;
    while (current != nullptr) {
        TermNode* next = current->nextlink;
        delete current;
        current = next;
    }
}

TermNode* AvailableList::GetNode(int c, int e) {
    if (available) {
        TermNode* n = available;
        available = available->nextlink;
        n->coef = c;
        n->exp = e;
        return n;
    }
    return new TermNode(c, e);
}

void AvailableList::ReturnNode(TermNode* n) {
    if (!n) return;
    n->nextlink = available;
    available = n;
}

void AvailableList::ReturnList(TermNode* head) {
    if (!head) return;
    // 找到循環串列的最後一個節點
    TermNode* last = head;
    while (last->nextlink != head) {
        last = last->nextlink;
    }
    // 將整個循環串列插到 available 前端
    last->nextlink = available;
    available = head;
}
