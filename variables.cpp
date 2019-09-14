//
// Created by Nozomi on 2019-08-21.
//

#include "variables.h"

variables::variables() {
    WIDTH = 100;
    FIELDSZ = WIDTH * WIDTH * WIDTH, PLAINSZ = WIDTH * WIDTH;
    viewH = WIDTH, viewW = WIDTH, PLATFORM_MAX = 4, DEVICE_MAX = 4;
    phaseNum = 16;
    updateState = true, dragState = false;
    animationCount = 0, xBegin = 0, yBegin = 0, mButton = 0;
    shiftX = 0., shiftY = 0.;

    maxPhoton2D = WIDTH * WIDTH * phaseNum;
    grad2D = (float *)malloc(sizeof(float) * PLAINSZ * 3);
    fColor2D = (float *)malloc(sizeof(float) * PLAINSZ * 3);
    fOpacity2D  = (float *)malloc(sizeof(float) * PLAINSZ);
    fRefractivity2D = (float *)malloc(sizeof(float) * PLAINSZ);
    lColor2D = (float *)malloc(sizeof(float) * PLAINSZ * 3);
    lDirection2D = (float *)malloc(sizeof(float) * PLAINSZ * 3);
    lIntensity2d = (float *)malloc(sizeof(float) * PLAINSZ);
    photonIrradiance2D =(float *)malloc(sizeof(float) * maxPhoton2D);
    photonPosition2D = (float *)malloc(sizeof(float) * maxPhoton2D * 3);
    photonDirection2D = (float *)malloc(sizeof(float) * maxPhoton2D * 3);
    photonGradDirection2D = (float *)malloc(sizeof(float) * maxPhoton2D * 3);
    photonColor2D = (float *)malloc(sizeof(float) * maxPhoton2D * 3);
    photonDestinatePosition = (float *)malloc(sizeof(float) * maxPhoton2D * 3);
    photonDestinateDirection = (float *)malloc(sizeof(float) * maxPhoton2D * 3);

    normPosition = (float *)malloc(sizeof(float) * maxPhoton2D);
    normDirection = (float *)malloc(sizeof(float) * maxPhoton2D);
}

variables::~variables() {
    free(grad2D);
    free(fColor2D);
    free(fOpacity2D);
    free(fRefractivity2D);
    free(lColor2D);
    free(lDirection2D);
    free(lIntensity2d);
    free(photonIrradiance2D);
    free(photonPosition2D);
    free(photonDirection2D);
    free(photonGradDirection2D);
    free(photonColor2D);
    free(normDirection);
    free(normPosition);
}