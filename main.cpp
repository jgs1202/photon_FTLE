

#include <iostream>

#include "ftle.h"

ftle ftle;

int main() {
    ftle.makeGeometry2D();
    std::cout << ftle.data.PLATFORM_MAX << std::endl;
    return 0;
}