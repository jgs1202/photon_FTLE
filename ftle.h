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

    // photonSetting;
    void photonPlace(void);
    void photonSetting(void);
};

#endif //FTLE_PHOTON_FTLE_H
