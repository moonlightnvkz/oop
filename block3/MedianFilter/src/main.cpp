#include <string>
#include <fstream>
#include "MedianFilter.h"

using namespace std;

int main() {
    string input, output;
    unsigned aperture, threshold;

    ifstream in("input");
    in >> input >> aperture >> threshold >> output;

    MedianFilter::median_filter(input, aperture, threshold, output);
    return 0;
}