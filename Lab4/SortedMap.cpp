#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <cstdlib>

using namespace std;

/// worst = average = best = θ(m)
SortedMap::SortedMap(Relation r) {
    capacity = 11;
    relation = r;

    elements = new TElem[capacity];
    for (int index = 0; index < capacity; index++) {
        elements[index] = NULL_TPAIR;
    }
}

/// worst = average = best = θ()
TValue SortedMap::add(TKey k, TValue v) {
    // check if a resize & rehash is needed
    if (size() == capacity) resizeRehash(2);

    int i = 0;
    int position = hashFunc(k, i);

    // traverser the array until: an empty position / the key "k" / there are no more empty positions
    while (elements[position].first != NULL_TVALUE && elements[position].first != k && i < capacity) {
        i++;
        position = hashFunc(k, i);
    }

    // check if a key needs to be overwritten
    if (elements[position].first == k) {
        int oldValue = elements[position].second;
        elements[position].second = v;
        return oldValue;
    }

    // adds a new key value pair
    elements[position] = TElem(k, v);
    return NULL_TVALUE;
}

/// worst = average = best = θ()
TValue SortedMap::search(TKey k) const {
    int i = 0;
    int position = hashFunc(k, i);

    // traverser the array until: an empty position / the key "k" / there are no more empty positions
    while (elements[position].first != NULL_TVALUE && elements[position].first != k && i < capacity) {
        i++;
        position = hashFunc(k, i);
    }

    // check if the key was found
    if (i < capacity && elements[position].first == k)
        return elements[position].second;
    else return NULL_TVALUE;
}

/// worst = average = best = θ()
TValue SortedMap::remove(TKey k) {
    // check if a resize is needed
    if (size() <= capacity / 4 && capacity > 11) resizeRehash(0.5);

    int i = 0;
    int position = hashFunc(k, i);

    // traverser the array until: an empty position / the key "k" / there are no more empty positions
    while (elements[position].first != NULL_TVALUE && elements[position].first != k && i < capacity) {
        i++;
        position = hashFunc(k, i);
    }

    // check if the key "k" was found
    if (elements[position].first == NULL_TVALUE || i == capacity) return NULL_TVALUE;

    // remove the pair
    int oldValue = elements[position].second;
    elements[position].first = NULL_TVALUE - 1;
    elements[position].second = NULL_TVALUE;

    return oldValue;
}

/// worst = average = best = θ(m)
int SortedMap::size() const {
    int size = 0;

    for (int index = 0; index < capacity; index++) {
        if (elements[index].first > NULL_TVALUE) { size++; }
    }

    return size;
}

/// worst = average = best = θ(m)
bool SortedMap::isEmpty() const {
    return size() == 0;
}

/// worst = average = best = θ()
SMIterator SortedMap::iterator() const {
    return SMIterator(*this);
}

/// worst = average = best = θ(1)
SortedMap::~SortedMap() {
    delete[] elements;
}

/// worst = average = best = θ(1)
int SortedMap::hashFunc1(TKey key) const {
    return abs(key) % capacity;
}

/// worst = average = best = θ(1)
int SortedMap::hashFunc2(TKey key) const {
    return 1 + (abs(key) % (capacity - 1));
}

/// worst = average = best = θ(1)
int SortedMap::hashFunc(TKey key, int i) const {
    return (hashFunc1(key) + i * hashFunc2(key)) % capacity;
}

/// worst = average = best = θ()
void SortedMap::resizeRehash(float factor) {
    int oldCapacity = capacity;
    capacity = generatePrime(capacity * factor);

    // initialize the new array of elements
    auto newElements = new TElem[capacity];
    for (int index = 0; index < capacity; index++) {
        newElements[index] = NULL_TPAIR;
    }

    // move the key from the old, to the new array
    for (int index = 0; index < oldCapacity; index++) {
        if (elements[index].first > NULL_TVALUE)
            addRehash(newElements, elements[index]);
    }

//    delete[] elements;
    elements = newElements;
}

/// worst = average = best = θ(1)
int SortedMap::generatePrime(int x) {
    while (!isPrime(x)) x++;
    return x;
}

/// worst = average = θ(sqrt(x))
/// best = θ(1)
bool SortedMap::isPrime(int x) {
    if (x <= 1) return false;
    for (int i = 2; i * i <= x; i++)
        if (x % i == 0) return false;
    return true;
}

/// worst = average = best = θ()
void SortedMap::addRehash(TElem *newElements, TElem elem) {
    int i = 0;
    int position = hashFunc(elem.first, i);

    // find empty position
    while (newElements[position].first != NULL_TVALUE) {
        i++;
        position = hashFunc(elem.first, i);
    }

    newElements[position] = elem;
}
