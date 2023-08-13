#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"

/*
  ADT SortedMultiMap – repräsentiert mithilfe einer DLL von Paaren der Form (key, value) und
  sortiert mithilfe einer Relation auf den Schlüsseln (key). Ein Schlüssel kann mehrmals vorkommen.
 */

int main() {
    testAll();
	testAllExtended();

    std::cout << "Finished SMM Tests!" << std::endl;
    system("pause");
}
