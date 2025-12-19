#ifndef CHAIN_H
#define CHAIN_H

#include <iostream>
using namespace std;

template <class T> class ChainNode;
template <class T> class ChainIterator;
template <class T> class Chain;
template <class T> class AvailableList;

// -------- ChainNode --------
template <class T>
class ChainNode {
    friend class Chain<T>;
    friend class ChainIterator<T>;
    friend class AvailableList<T>;
private:
    T element;
    ChainNode<T>* next;
public:
    ChainNode() : next(nullptr) {}
    ChainNode(const T& elem) : element(elem), next(nullptr) {}
    ChainNode(const T& elem, ChainNode<T>* nextNode)
        : element(elem), next(nextNode) {
    }
    void setElement(const T& elem) { element = elem; }
    void setNext(ChainNode<T>* nextNode) { next = nextNode; }
};

// -------- ChainIterator --------
template <class T>
class ChainIterator {
private:
    ChainNode<T>* currentNode;
public:
    ChainIterator(ChainNode<T>* startNode = nullptr) : currentNode(startNode) {}

    T& operator*() const { return currentNode->element; }
    T* operator->() const { return &currentNode->element; }

    ChainIterator& operator++() {
        if (currentNode) currentNode = currentNode->next;
        return *this;
    }

    ChainIterator operator++(int) {
        ChainIterator old = *this;
        if (currentNode) currentNode = currentNode->next;
        return old;
    }

    bool operator!=(const ChainIterator& right) const {
        return currentNode != right.currentNode;
    }
    bool operator==(const ChainIterator& right) const {
        return currentNode == right.currentNode;
    }

    int operator-(const ChainIterator& right) const {
        int distance = 0;
        ChainNode<T>* temp = right.currentNode;
        while (temp != currentNode) {
            if (temp == nullptr) return -1;
            temp = temp->next;
            ++distance;
        }
        return distance;
    }
};

// -------- AvailableList --------
template <class T>
class AvailableList {
private:
    static ChainNode<T>* availableHead;
public:
    AvailableList() {}
    ~AvailableList() {
        while (availableHead) {
            ChainNode<T>* tmp = availableHead;
            availableHead = availableHead->next;
            delete tmp;
        }
    }

    static ChainNode<T>* getNode() {
        if (!availableHead) return nullptr;
        ChainNode<T>* nodeToReturn = availableHead;
        availableHead = availableHead->next;
        nodeToReturn->next = nullptr;
        return nodeToReturn;
    }

    static void getBack(ChainNode<T>* firstNode) {
        if (!firstNode) return;
        ChainNode<T>* current = firstNode;
        while (current->next) current = current->next;
        current->next = availableHead;
        availableHead = firstNode;
    }

    static bool isEmpty() { return availableHead == nullptr; }

    static ChainNode<T>* getOneNodeOrNew(const T& elem) {
        ChainNode<T>* node = getNode();
        if (!node) node = new ChainNode<T>(elem);
        else node->setElement(elem);
        return node;
    }
};

template <class T>
ChainNode<T>* AvailableList<T>::availableHead = nullptr;

// -------- Chain --------
template <class T>
class Chain {
    friend class ChainIterator<T>;
    friend class AvailableList<T>;
private:
    ChainNode<T>* head;
public:
    Chain() : head(nullptr) {}
    ~Chain() {
        ChainNode<T>* current = head;
        while (current != nullptr) {
            ChainNode<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
    }

    ChainNode<T>* release() {
        ChainNode<T>* oldHead = head;
        head = nullptr;
        return oldHead;
    }

    ChainIterator<T> begin() const { return ChainIterator<T>(head); }
    ChainIterator<T> end() const { return ChainIterator<T>(nullptr); }

    void insert(int idx, const T& element) {
        ChainNode<T>* newNode = AvailableList<T>::getNode();
        if (!newNode) newNode = new ChainNode<T>(element);
        else newNode->setElement(element);

        if (idx == 0 || head == nullptr) {
            newNode->next = head;
            head = newNode;
        }
        else {
            ChainNode<T>* prev = head;
            for (int i = 0; i < idx - 1 && prev != nullptr; ++i)
                prev = prev->next;

            if (prev != nullptr) {
                newNode->next = prev->next;
                prev->next = newNode;
            }
            else {
                // index 超出範圍，回收
                AvailableList<T>::getBack(newNode);
            }
        }
    }
};

#endif
