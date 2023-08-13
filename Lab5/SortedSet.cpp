#include "SortedSet.h"
#include "SortedSetIterator.h"


// worst = θ(1)
// average = θ(1)
// best = θ(1)
SortedSet::SortedSet(Relation r) {
    head = nullptr;
    relation = r;
}


// worst = θ(n)
// average = θ(log n)
// best = θ(1)
bool SortedSet::add(TComp elem) {
    auto newNode = new Node{elem, nullptr, nullptr, nullptr};

    // add the first node
    if (head == nullptr) {
        head = newNode;
        return true;
    }

    auto currentNode = head;

    // traverse the tree
    while (currentNode != nullptr) {
        // element already exists
        if (elem == currentNode->value) {
            delete newNode;
            return false;
        } else if (relation(elem, currentNode->value)) {
            // go in the left subtree and add the new value if the bottom is reached
            if (currentNode->left == nullptr) {
                currentNode->left = newNode;
                newNode->parent = currentNode;
                return true;
            }
            // go to the next node
            currentNode = currentNode->left;
        } else {
            // go in the right subtree and add the new value if the bottom is reached
            if (currentNode->right == nullptr) {
                currentNode->right = newNode;
                newNode->parent = currentNode;
                return true;
            }
            // go to the next node
            currentNode = currentNode->right;
        }
    }
    return false;
}


// worst = θ(n)
// average = θ(log n)
// best = θ(1)
bool SortedSet::remove(TComp elem) {
    auto currentNode = head;
    Node* parentNode = nullptr;

    while (currentNode != nullptr && currentNode->value != elem) {
        parentNode = currentNode;
        if (relation(elem, currentNode->value)) {
            currentNode = currentNode->left;
        } else {
            currentNode = currentNode->right;
        }
    }

    // elem was not found
    if (currentNode == nullptr) return false;

    // elem is a leaf
    if (currentNode->left == nullptr && currentNode->right == nullptr) {
        if (parentNode == nullptr) {
            // Removing the root node
            delete currentNode;
            head = nullptr;
        } else {
            if (relation(elem, parentNode->value)) {
                delete parentNode->left;
                parentNode->left = nullptr;
            } else {
                delete parentNode->right;
                parentNode->right = nullptr;
            }
        }
        return true;
    }

    // elem has only a right child
    if (currentNode->left == nullptr) {
        if (parentNode == nullptr) {
            // Removing the root node
            head = currentNode->right;
        } else {
            if (relation(elem, parentNode->value)) {
                parentNode->left = currentNode->right;
            } else {
                parentNode->right = currentNode->right;
            }
        }
        delete currentNode;
        return true;
    }

    // elem has only a left child
    if (currentNode->right == nullptr) {
        if (parentNode == nullptr) {
            // Removing the root node
            head = currentNode->left;
        } else {
            if (relation(elem, parentNode->value)) {
                parentNode->left = currentNode->left;
            } else {
                parentNode->right = currentNode->left;
            }
        }
        delete currentNode;
        return true;
    }

    // elem has two children
    Node* successorNode = currentNode->right;
    while (successorNode->left != nullptr) {
        successorNode = successorNode->left;
    }

    currentNode->value = successorNode->value;
    return remove(successorNode->value); // Remove the successor node recursively
}


// worst = θ(n)
// average = θ(log n)
// best = θ(1)
bool SortedSet::search(TComp elem) const {
    auto currentNode = head;

    while (currentNode != nullptr) {
        if (currentNode->value == elem) return true;
        if (relation(elem, currentNode->value)) {
            currentNode = currentNode->left;
        } else {
            currentNode = currentNode->right;
        }
    }
    return false;
}


// worst = θ(n)
// average = θ(n)
// best = θ(n)
int SortedSet::size() const {
    return sizeRecursive(head);
}


// worst = θ(1)
// average = θ(1)
// best = θ(1)
bool SortedSet::isEmpty() const {
    return head == nullptr;
}


// worst = θ(n)
// average = θ(n)
// best = θ(n)
SortedSetIterator SortedSet::iterator() const {
    return SortedSetIterator(*this);
}


// worst = θ(1)
// average = θ(1)
// best = θ(1)
SortedSet::~SortedSet() {
    clearRecursive(head);
}


// worst = θ(n)
// average = θ(n)
// best = θ(n)
void SortedSet::clearRecursive(Node* currentNode) {
    if (currentNode == nullptr) return;

    clearRecursive(currentNode->left);
    clearRecursive(currentNode->right);

    delete currentNode;
}


// worst = θ(n)
// average = θ(n)
// best = θ(n)
int SortedSet::sizeRecursive(Node *currentNode) const {
    if (currentNode == nullptr) return 0;
    return sizeRecursive(currentNode->right) + sizeRecursive(currentNode->left) + 1;
}


