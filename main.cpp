

#include <iostream>

#include "ftle.h"


ftle ftle;

int main() {
    ftle.makeGeometry2D();
    ftle.gradRefraction2D();

    ftle.gradSmooth2D(3);
    ftle.gradSmooth2D(3);
    ftle.gradSmooth2D(3);

    ftle.photonSetting();
    ftle.photonDestinate();

    ftle.visualize2D();

//    for (int i=0; i<ftle.data.maxPhoton2D * 3; i++) {
//        std::cout << ftle.data.photonDirection2D[i] << " ";
//        if ((i + 1) % 3 == 0) {
//            std::cout << i << " \n";
//        }
//    }
}