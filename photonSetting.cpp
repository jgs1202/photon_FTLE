//
// Created by Nozomi on 2019-08-22.
//

#include <math.h>

#include "ftle.h"
#include "myMath.h"

void ftle::photonInit(void) {
    for (int y=0; y<data.WIDTH; ++y) {
        for (int x=0; x<data.WIDTH; ++x) {
            for (int phi=0; phi<data.phaseNum; ++phi) {
                data.photonPosition2D[valueVectorCoordinateIntPhase(x, y, 0, data.WIDTH, data.phaseNum, phi) + 0] = x;
                data.photonPosition2D[valueVectorCoordinateIntPhase(x, y, 0, data.WIDTH, data.phaseNum, phi) + 1] = y;
                data.photonPosition2D[valueVectorCoordinateIntPhase(x, y, 0, data.WIDTH, data.phaseNum, phi) + 2] = 0;

                data.photonDirection2D[valueVectorCoordinateIntPhase(x, y, 0, data.WIDTH, data.phaseNum, phi) + 0] = cos(2 * M_PI / data.phaseNum * phi);
                data.photonDirection2D[valueVectorCoordinateIntPhase(x, y, 0, data.WIDTH, data.phaseNum, phi) + 1] = sin(2 * M_PI / data.phaseNum * phi);
                data.photonDirection2D[valueVectorCoordinateIntPhase(x, y, 0, data.WIDTH, data.phaseNum, phi) + 2] = 0;
            }
        }
    }
    memset(data.photonColor2D, 1., data.maxPhoton2D * 3);
    memset(data.photonGradDirection2D, 0., data.maxPhoton2D * 3);
    memset(data.photonIrradiance2D, 1., data.maxPhoton2D);
}

void ftle::photonSetting(void) {
    photonInit();
}