#include "ShortTest.h"
#include "ExtendedTest.h"
#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>

using namespace std;
/*
    7. ADT SortedSet – repräsentiert mithilfe eines BST mit einer verketteten Repräsentierung mit dynamischer Allokation
    BONUS: iterator bidirectional (next si previous)
*/
int main() {
	testAll();
	testAllExtended();

	cout << "Test end" << endl;
	system("pause");
}