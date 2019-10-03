//
// Created by Nozomi on 2019-09-14.
//

#include <fstream>
#include "ftle.h"
#include <math.h>

void ftle::output() {
    std::ofstream csv;
    csv.open("../outputs/normOfGradient.csv", std::ios::trunc);
    csv << "x,y,theta,normPosition,normAngle,normTotal\n";

    double normP, normA;
    for (int x=0; x<data.WIDTH; ++x) {
        for (int y=0; y<data.WIDTH; ++y) {
            for (int phi=0; phi<data.phaseNum; ++phi) {
                csv << x << "," << y << "," << phi << ",";
//                if (data.fOpacity2D[x + y * data.WIDTH] == 1.0) {
//                    csv << 0 << "," << 0 << "\n";
//                } else {
                normP = data.normPosition[(x + y * data.WIDTH) * data.phaseNum + phi];
                normA = data.normDirection[(x + y * data.WIDTH) * data.phaseNum + phi];
                csv << normP << "," << normA << ",";
                csv << sqrt(normA * normA + normP * normP) << "\n";
//                }
            }
        }
    }
    csv.close();
}