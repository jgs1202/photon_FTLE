//
// Created by Nozomi on 2019-08-22.
//

#include "ftle.h"
#include "myMath.h"

void ftle::photonPlace(void) {
    for (int y=0; y<data.WIDTH; ++y) {
        for (int x=0; x<data.WIDTH; ++x) {
            for (int phi=0; phi<data.phaseNum; ++phi) {
                data.photonPosition2D[((x + y * data.WIDTH) * data.phaseNum + phi) * 3 + 0] = x;
                data.photonPosition2D[((x + y * data.WIDTH) * data.phaseNum + phi) * 3 + 1] = y;
                data.photonPosition2D[((x + y * data.WIDTH) * data.phaseNum + phi) * 3 + 3] = 0;
            }
        }
    }
}

void ftle::photonSetting(void) {

}