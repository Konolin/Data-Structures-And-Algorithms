#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>

using namespace std;

// best = average = worst = θ(1)
SortedMultiMap::SortedMultiMap(Relation r) {
    relation = r;
    head = nullptr;
    tail = nullptr;
}

// best = θ(1)
// average = worst = θ(n)
void SortedMultiMap::add(TKey c, TValue v) {
    // create a new node
    Node *newNode = new Node;
    newNode->data = pair(c, v);
    newNode->next = nullptr;
    newNode->prev = nullptr;

    // add first node
    if (size() == 0) {
        head = newNode;
        tail = newNode;
        return;
    }

    // find position
    Node *current = head;
    while (current != nullptr && relation(current->data.first, c))
        current = current->next;

    // add first
    if (current == head){
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        return;
    }

    // add last
    if (current == nullptr) {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
        return;
    }

    // add middle
    newNode->next = current;
    newNode->prev = current->prev;
    current->prev->next = newNode;
    current->prev = newNode;
}

// best = θ(1)
// average = worst = θ(n)
vector<TValue> SortedMultiMap::search(TKey c) const {
    vector<TValue> result;
    Node *current = head;

    while (current != nullptr && relation(current->data.first, c)) {
        if (current->data.first == c)
            result.push_back(current->data.second);
        current = current->next;
    }

    return result;
}

// best = θ(1)
// average = worst = θ(n)
bool SortedMultiMap::remove(TKey c, TValue v) {
    bool removed = false;

    // check if value is head
    while (head != nullptr && head->data.first == c && head->data.second == v) {
        // check if there is only on elem left
        if (size() == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
            return true;
        }
        Node *temp = head;
        head = head->next;
        head->prev = nullptr;
        delete temp;
        removed = true;
    }

    // check if value is tail
    while (tail != nullptr && tail->data.first == c && tail->data.second == v) {
        Node *temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete temp;
        removed = true;
    }

    Node *current = head;
    // find position of key-value pair
    while (current != nullptr && relation(current->data.first, c))
        // delete node if found
        if (current->data.first == c && current->data.second == v) {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            Node *temp = current;
            current = current->next;
            delete temp;
            removed = true;
        } else current = current->next;

    return removed;
}

// best = average = worst = θ(n)
int SortedMultiMap::size() const {
    if (head == nullptr) return 0;

    int size = 1;
    Node *current = head;
    while (current->next != nullptr) {
        size++;
        current = current->next;
    }
    return size;
}

// best = average = worst = θ(1)
bool SortedMultiMap::isEmpty() const {
    return head == nullptr && tail == nullptr;
}

// best = average = worst = θ(1)
SMMIterator SortedMultiMap::iterator() const {
    return SMMIterator(*this);
}

// best = average = worst = θ(n)
SortedMultiMap::~SortedMultiMap() {
    while (head != nullptr) {
        Node *temp = head;
        head = head->next;
        if (head != nullptr) head->prev = nullptr;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
}

/*
    complexities:
        worst: θ(n)
        average: θ(n)
        best: θ(1)

    descr: deletes all occurrences of a specified key
    pre: SMM of TElem, key of TKey
    post: ture if min 1 elem was deleted
          false no elem was deleted
*/
bool SortedMultiMap::deleteAllValues(TKey key) {
    vector<TValue> result = search(key);

    if (result.empty()) return false;

    int index = 0;
    while (index < result.size()) {
        removeKey(key);
        index++;
    }
    return true;
}

/*
    complexities:
        worst: θ(n)
        average: θ(n)
        best: θ(1)

    descr: deletes Tvalue by key
    pre: SMM of TElem, key of TKey
    post: ture if elem was deleted
          false no elem was deleted
*/
bool SortedMultiMap::removeKey(TKey c) {
    bool removed = false;

    // check if value is head
    if (head->data.first == c) {
        // check if there is only on elem left
        if (size() == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
            return true;
        }
        Node *temp = head;
        head = head->next;
        head->prev = nullptr;
        delete temp;
        return true;
    }

    // check if value is tail
    if (tail->data.first == c) {
        Node *temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete temp;
        return true;
    }

    Node *current = head;
    // find position of key-value pair
    while (current->data.first != c) current = current->next;

    current->prev->next = current->next;
    current->next->prev = current->prev;
    Node *temp = current;
    delete temp;

    return removed;
}


/*
function deleteAllValues(TKey key)
    vector<TValue> result = search(key)

    if (result.empty())
        return false
    end-if

    int index = 0;
    while (index < result.size())
        removeKey(key)
        index++
    end-while

    return true
end-function


function removeKey(TKey c) {
    bool removed = false;

    if (head->data.first == c)
        if (size() == 1)
            delete head
            head = nullptr
            tail = nullptr
            return true
        end-if

        Node *temp = head
        head = head->next
        head->prev = nullptr
        delete temp
        return true
    end-if

    if (tail->data.first == c)
        Node *temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete temp;
        return true;
    end-if

    Node *current = head;

    while (current->data.first != c)
        current = current->next;
    end-while

    current->prev->next = current->next
    current->next->prev = current->prev
    Node *temp = current
    delete temp

    return removed
}*/
