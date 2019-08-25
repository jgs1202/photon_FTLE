//
// Created by Nozomi on 2019-08-21.
//

#ifndef FTLE_PHOTON_FTLE_H
#define FTLE_PHOTON_FTLE_H

#include <iostream>
#include "variables.h"

class ftle
{
public:
    variables data;

    ftle(void);
    ~ftle(void);

    // geoometry
    void surroundWall(void);
    void squareObject(void);
    void makeGeometry2D(void);

    // gradient
    void gradRefraction2D(void);
    void gradSmooth2D(unsigned int kernelSz);
    void gradVectorField2D(float *data2D, std::vector<float>& norm);

    // photonSetting
    void photonInit(void);
    void photonSetting(void);

    // photonParicipate
    void trilinearTrace(float x, float y, float z, bool flag2D, float *gradient, float *opacity);
    void trace3d(int photon);
    void photonDestinate(void);

    // visResult
    void visualize2D(void);
};

#endif //FTLE_PHOTON_FTLE_H
