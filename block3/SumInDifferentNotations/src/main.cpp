#include <iostream>
#include "RadixTranslation.h"
#include "DiffRadixPlus.h"

using namespace std;

#define CODE(s) (s - 'A' + 10)

int main() {
    LongNumber a = {15, 15};
    LongNumber b = {CODE('H'), CODE('E'), CODE('L'), CODE('L'), CODE('O')};
    LongNumber res = my_plus(a, 16, b, 36, 2);
    for (auto i : res) {
        cout << i;
    }
    return 0;
}