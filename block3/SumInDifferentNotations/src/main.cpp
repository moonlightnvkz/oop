#include <iostream>
#include "RadixTranslation.h"
#include "DiffRadixPlus.h"

using namespace std;

int main() {
    LongNumber a = {15, 15};
    LongNumber b = {'H' - 'A' + 10, 'E' - 'A' + 10, 'L' - 'A' + 10, 'L' - 'A' + 10, 'O' - 'A' + 10};
    LongNumber res = my_plus(a, 16, b, 36, 2);
    for (auto i : res) {
        cout << i;
    }
    return 0;
}