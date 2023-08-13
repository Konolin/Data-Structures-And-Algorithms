#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

// worst = average = best = ϴ(1)
SortedBagIterator::SortedBagIterator(const SortedBag &b) : bag(b) {
    index = 0;
    occurIndex = 0;
}

// worst = average = best = ϴ(1)
TComp SortedBagIterator::getCurrent() {
    if (valid()) {
        return bag.elements[index].element;
    } else throw exception();
}

// worst = average = best = ϴ(1)
bool SortedBagIterator::valid() {
    if (0 <= index && index < bag.nrElems)
        return true;

    return false;
}

// goes to the next index only after repeating nrOccurrences times
// ex: <5, 1> => .next executed 1 time to get to the next index (index++)
//     <5, 3> => .next executed 3 times to get to the next index (index++)
// worst = average = best = ϴ(1)
void SortedBagIterator::next() {
    if (index < bag.nrElems)
        if (occurIndex < bag.elements[index].occurrences - 1)
            occurIndex++;
        else {
            index++;
            occurIndex = 0;
        }
    else
        throw exception();
}

// worst = average = best = ϴ(1)
void SortedBagIterator::first() {
    index = 0;
}