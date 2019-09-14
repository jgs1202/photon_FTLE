//
// Created by Nozomi on 2019-09-14.
//

#include <fstream>
#include "ftle.h"

void ftle::output() {
    std::ofstream csv;
    csv.open("../outputs/normOfGradient.csv", std::ios::trunc);
    csv << "x,y,theta,normPosition,normAngle\n";
    csv << "x" << "," << "y" << "," << "phi" << ",normPosition,normDirection\n";

    for (int x=0; x<data.WIDTH; ++x) {
        for (int y=0; y<data.WIDTH; ++y) {
            for (int phi=0; phi<data.phaseNum; ++phi) {
                csv << x << "," << y << "," << phi << ",";
                csv << data.normPosition[(x + y * data.WIDTH) * data.phaseNum + phi] << "," << data.normDirection[(x + y * data.WIDTH) * data.phaseNum + phi] << "\n";
            }
        }
    }
    csv.close();
}