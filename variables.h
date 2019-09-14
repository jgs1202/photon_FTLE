//
// Created by Nozomi on 2019-08-21.
//

#ifndef FTLE_PHOTON_VARIABLES_H
#define FTLE_PHOTON_VARIABLES_H

#include <iostream>

class variables
{
private:
public:
    int WIDTH, FIELDSZ, PLAINSZ;
    bool updateState, dragState;
    int animationCount, xBegin, yBegin, mButton, viewH, viewW, PLATFORM_MAX, DEVICE_MAX, phaseNum;
    int plainX, plainY, plainZ;
    float shiftX, shiftY;

    int maxPhoton2D;
    float *grad2D, *fColor2D, *fOpacity2D, *fRefractivity2D;
    float *lColor2D, *lDirection2D, *lIntensity2d;
    float *photonIrradiance2D, *photonPosition2D, *photonDirection2D, *photonGradDirection2D, *photonColor2D;
    float *photonDestinatePosition, *photonDestinateDirection;
    float *normPosition, *normDirection;


    variables(void);
    ~variables(void);
};

#endif //FTLE_PHOTON_VARIABLES_H
