#include "SortedBag.h"
#include "SortedBagIterator.h"

// worst = average = best = ϴ(1)
SortedBag::SortedBag(Relation r) {
    relation = r;
    nrElems = 0;
    capacity = 10;
    elements = new TElem[capacity];
}

// worst: ϴ(n) (insert on the first position, all elem need to be shifted)
// average: ϴ(n)
// best: ϴ(1)  (if e already is in the bag and only needs to have it`s nrOccurrence increased)
// total: O(n)
void SortedBag::add(TComp e) {
    // check if there is space in the container
    if (nrElems == capacity) resize(2);

    // if the element already exists in the bag, only the occurrences gets modified
    int insertIndex = searchIndex(e);
    if (insertIndex != -1) {
        elements[insertIndex].occurrences++;
        return;
    }

    nrElems++;

    // finds the position where the element should be inserted
    insertIndex = 0;
    while (relation(elements[insertIndex].element, e) && insertIndex < nrElems - 1)
        insertIndex++;

    // moves the elements right from insertIndex one position to the right
    for (int index = nrElems - 1; index > insertIndex; index--)
        elements[index] = elements[index - 1];

    // inserts the new element
    elements[insertIndex].element = e;
    elements[insertIndex].occurrences = 1;
}

// worst: ϴ(n)  (e is the first element in the bag, all elem need to be shifted)
// average: ϴ(n)
// best: ϴ(1)  (e is in the element element in the bag and its number of occurrences is greater than 1)
// total: O(n)
bool SortedBag::remove(TComp e) {
    // find the index of the element we want to remove
    int removeIndex = searchIndex(e);

    // returns false if the element doesn't exist
    if (removeIndex == -1) return false;

    // the entire pair needs to be removed
    if (elements[removeIndex].occurrences == 1) {
        // move the elements one position to the left
        for (int index = removeIndex; index < nrElems - 1; index++)
            elements[index] = elements[index + 1];

        nrElems--;

        // check if the capacity needs to be made smaller
        if (capacity >= 4 * nrElems) resize(0.5);

        // if e appears more than once, .occurrences only needs to be decreased by one
    } else elements[removeIndex].occurrences--;

    return true;
}

// worst = average = best = ϴ(n)
void SortedBag::resize(float multiplier) {
    // edit the capacity
    capacity *= multiplier;

    // create new array with the new capacity
    auto *newElements = new TElem[capacity];

    // move the elements in the new array
    for (int index = 0; index < nrElems; index++)
        newElements[index] = elements[index];

    // deletes old elements and stores the new ones
    delete[] elements;
    elements = newElements;
}

// worst = ϴ(log n); average = ϴ(log n); best = ϴ(1); total = O(log n)
int SortedBag::searchIndex(TComp elem) const {
    int left = 0;
    int right = nrElems - 1;
    int middle;

    while (left <= right) {
        middle = (left + right) / 2;
        if (elements[middle].element == elem)
            return middle;
        else if (relation(elements[middle].element, elem))
            left = middle + 1;
        else
            right = middle - 1;
    }
    return -1;
}

// worst = ϴ(log n); average = ϴ(log n); best = ϴ(1); total = O(log n)
bool SortedBag::search(TComp elem) const {
    return searchIndex(elem) != -1;
}

// worst = ϴ(log n); average = ϴ(log n); best = ϴ(1); total = O(log n)
int SortedBag::nrOccurrences(TComp elem) const {
    int index = searchIndex(elem);

    // returns 0 if elem is not in the bag
    if (index == -1) return 0;

    return elements[index].occurrences;
}

// worst = average = best = ϴ(n)
int SortedBag::size() const {
    // size = sum of all occurrences
    int bagSize = 0;

    for (int index = 0; index < nrElems; index++)
        bagSize += elements[index].occurrences;

    return bagSize;
}

// worst = average = best = ϴ(1)
bool SortedBag::isEmpty() const {
    return nrElems == 0;
}

// worst = average = best = ϴ(1)
SortedBagIterator SortedBag::iterator() const {
    return SortedBagIterator(*this);
}

// worst = average = best = ϴ(1)
SortedBag::~SortedBag() {
    delete[] elements;
}

bool SortedBag::removeNAppearances(TComp elem, int appearances) {
    // check if appearances has a valid value
    if (appearances <= 0) return false;

    // binary search of the index
    int index = -1;
    int left = 0;
    int right = nrElems - 1;
    int middle;

    while (left <= right) {
        middle = (left + right) / 2;
        if (elements[middle].element == elem) {
            index = middle;
            break;
        }
        else if (relation(elements[middle].element, elem))
            left = middle + 1;
        else
            right = middle - 1;
    }

    // if elem is not in the bag or there are not enough appearances of elem
    if (index == -1 || elements[index].occurrences < appearances) return false;

    // if there are more occurrences than we want to remove
    if (elements[index].occurrences > appearances) {
        elements[index].occurrences -= appearances;
        return true;
    }

    // if appearances and occurrences are the same, remove the entire element
    // move the elements one position to the left
    for (int i = index; i < nrElems - 1; i++) elements[i] = elements[i + 1];

    nrElems--;

    // check if the capacity needs to be made smaller
    if (capacity >= 4 * nrElems) {
        capacity /= 2;

        // create new array with the new capacity
        auto *newElements = new TElem[capacity];

        // move the elements in the new array
        for (int i = 0; i < nrElems; i++)
            newElements[i] = elements[i];

        // deletes old elements and stores the new ones
        delete[] elements;
        elements = newElements;
    }

    return true;
}

/*
 complexity:
    worst = ϴ(n) - deletes the first element, move all other to the left
    average = ϴ(n)
    best = ϴ(1) - elem in the middle, occur > deleted occur or appearances <= 0
    overall = O(n)

 descr: deletes n number of appearances of an element, and returns a boolean corresponding to the success of the operation
 pre: bag of TElem, TComp elem, int appearances
 post: removeNAppearances <- | true : TComp elem in TElem und elem.occurrences >= appearances
                             | false : else

 function removeNAppearances (TComp elem, int appearances)
    if appearances <= 0
        return false
    end-if

    index <- -1
    left <- 0
    right <- nrElems - 1

    while (left <= right)
        middle <- (left + right) / 2
        if (elements[middle].element == elem)
            index <- middle
            @break out of the while loop
        else if (relation(elements[middle].element, elem))
            left <- middle + 1
        else
            right <- middle - 1
        end-if
    end-while

    if (index == -1 || elements[index].occurrences < appearances)
        removeNAppearances <- false
    end-if

    if (elements[index].occurrences > appearances) {
        elements[index].occurrences <- elements[index].occurrences - appearances
        removeNAppearances <- true
    end-if

    for (int i = index; i < nrElems - 1; i++)
        elements[i] = elements[i + 1]
    end-for

    nrElems <- nrElems - 1

    if (capacity >= 4 * nrElems)
        capacity <- capacity / 2

        // create a new array of pairs(value, occurences)
        auto *newElements <- new TElem[capacity]

        for (int i = 0; i < nrElems; i++)
            newElements[i] <- elements[i]
        end-for

        @deallocate elements
        elements <- newElements
    end-if

    removeNAppearances <- true;

 end-function

*/
