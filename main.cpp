

#include <iostream>

#include "ftle.h"


ftle ftle;

int main() {
    printf("setting geometry...\n");
    ftle.makeGeometry2D();
    printf("taking gradient...\n");
    ftle.gradRefraction2D();

    printf("smoothing gradient...\n");
    ftle.gradSmooth2D(3);
    ftle.gradSmooth2D(3);
    ftle.gradSmooth2D(3);
    ftle.gradSmooth2D(3);

    printf("setting photons...\n");
    ftle.photonSetting();
    printf("propagating photons...\n");
    ftle.photonDestinate();

    printf("visualizing...\n");
    ftle.visualize2D();
    ftle.visualizeGrad2D();
    ftle.visualize2DAverage();

    ftle.output();

//    std::cout << ftle.data.photonDestinatePosition[(39 + 23 * 100) * 16 * 3 + 0] << " " << ftle.data.photonDestinatePosition[(39 + 23 * 100) * 16 * 3 + 1] << std::endl;
}