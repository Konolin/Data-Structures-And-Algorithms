#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>

// best = average = worst = θ(1)
SMMIterator::SMMIterator(const SortedMultiMap &d) : map(d) {
    current = map.head;
}

// best = average = worst = θ(1)
void SMMIterator::first() {
    current = map.head;
}

// best = average = worst = θ(1)
void SMMIterator::next() {
    if (valid()) current = current->next;
    else throw exception();
}

// best = average = worst = θ(1)
bool SMMIterator::valid() const {
    return current != nullptr;
}

// best = average = worst = θ(1)
TElem SMMIterator::getCurrent() const {
    if (valid()) return current->data;
    throw exception();
}
