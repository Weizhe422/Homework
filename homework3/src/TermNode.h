#ifndef TERMNODE_H
#define TERMNODE_H

struct TermNode {
    int coef; // 係數
    int exp;  // 指數
    TermNode* nextlink; // 指向下一節點

    TermNode(int c = 0, int e = 0, TermNode* nl = nullptr)
        : coef(c), exp(e), nextlink(nl) {
    }
};

#endif
