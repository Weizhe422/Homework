#ifndef AVAILABLELIST_H
#define AVAILABLELIST_H

#include "TermNode.h"

class AvailableList {
private:
    TermNode* available;
    AvailableList();
    ~AvailableList();

public:
    AvailableList(const AvailableList&) = delete;
    AvailableList& operator=(const AvailableList&) = delete;

    static AvailableList& getInstance();
    TermNode* GetNode(int c = 0, int e = 0);
    void ReturnNode(TermNode* n);
    void ReturnList(TermNode* head); // 歸還整串循環串列
};

#endif
