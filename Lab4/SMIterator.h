#pragma once

#include "SortedMap.h"

//DO NOT CHANGE THIS PART
class SMIterator {
    friend class SortedMap;

private:
    const SortedMap &map;

    SMIterator(const SortedMap &mapionar);

    int index;
    int size;
    Relation relation;

    TElem *sortedMap;

    void sortMap(const SortedMap &originalMap);

    void quicksort(int left, int right);

    int partition(int left, int right);

public:
    void first();

    void next();

    bool valid() const;

    TElem getCurrent() const;
};

