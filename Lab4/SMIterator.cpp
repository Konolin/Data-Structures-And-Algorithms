#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <iostream>

using namespace std;

SMIterator::SMIterator(const SortedMap &m) : map(m) {
    index = 0;
    size = m.size();
    relation = m.relation;
    sortedMap = new TElem[size];
    sortMap(m);
}

void SMIterator::first() {
    index = 0;
}

void SMIterator::next() {
    if (valid()) index++;
    else throw exception();
}

bool SMIterator::valid() const {
    return index < size;
}

TElem SMIterator::getCurrent() const {
    if (valid()) return sortedMap[index];
    throw exception();
}


void SMIterator::sortMap(const SortedMap &originalMap) {
    // put the non-empty elements of teh original map in the soon-to-be sorted map
    int sortedIndex = 0;
    for (int originalIndex = 0; originalIndex < originalMap.capacity; originalIndex++) {
        if (originalMap.elements[originalIndex].first > -1) {
            sortedMap[sortedIndex] = originalMap.elements[originalIndex];
            sortedIndex++;
        }
    }

    quicksort(0, size - 1);
}

void SMIterator::quicksort(int left, int right) {
    if (left >= right) {
        return;
    }
    int pivotIndex = partition(left, right);
    quicksort(left, pivotIndex - 1);
    quicksort(pivotIndex + 1, right);
}

int SMIterator::partition(int left, int right) {
    TElem pivot = sortedMap[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (relation(sortedMap[j].first, pivot.first)) {
            i++;
            swap(sortedMap[i], sortedMap[j]);
        }
    }
    swap(sortedMap[i + 1], sortedMap[right]);
    return i + 1;
}


