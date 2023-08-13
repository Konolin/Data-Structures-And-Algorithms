#include "ExtendedTest.h"
#include "ShortTest.h"
#include "SortedMap.h"
#include <iostream>


using namespace std;

/*
    18. ADT SortedMap – repräsentiert mithilfe einer Hashtabelle mit offener Adressierung, mit doppeltem Hashing.
    In dem Constructor des Iterators erstelle ein sortiertes Array von Elementen und benutze es für die Iterierung.
*/

int main() {
    testAll();
	testAllExtended();

    cout << "That's all!" << endl;
    system("pause");
    return 0;
}


