//
// Created by Nozomi on 2019-08-21.
//

#include "ftle.h"

void ftle::surroundWall() {
    float black[] = {0., 0., 0.}, opacity = 1.;
    for (int y=0; y<data.WIDTH; ++y) {
        for (int x=0; x<data.WIDTH; ++x) {
            if ((x == 0) || (x = data.WIDTH - 1) || (y == 0) || (y == data.WIDTH - 1)) {
                data.fColor2D[(x + y * data.WIDTH) * 3 + 0] = black[0];
                data.fColor2D[(x + y * data.WIDTH) * 3 + 1] = black[1];
                data.fColor2D[(x + y * data.WIDTH) * 3 + 2] = black[2];
                data.fOpacity2D[x + y * data.WIDTH] = opacity;
                data.fRefractivity2D[x + y * data.WIDTH] = 1.3;
            }
        }
    }
}

void ftle::mirrorWall() {
    float black[] = {0., 0., 0.}, opacity = 1.;
    for (int y=0; y<data.WIDTH; ++y) {
        for (int x=0; x<data.WIDTH; ++x) {
            if ((x = data.WIDTH - 1) || (y == data.WIDTH - 1)) {
                data.fColor2D[(x + y * data.WIDTH) * 3 + 0] = black[0];
                data.fColor2D[(x + y * data.WIDTH) * 3 + 1] = black[1];
                data.fColor2D[(x + y * data.WIDTH) * 3 + 2] = black[2];
                data.fOpacity2D[x + y * data.WIDTH] = opacity;
                data.fReflectivity2D[x + y * data.WIDTH] = 1.0;
                data.fRefractivity2D[x + y * data.WIDTH] = 1.3;
            }
        }
    }
}

void ftle::squareObject() {
    float black[] = {0., 0., 0.}, opacity = 1.;
    float leftTop[] = {(float)data.WIDTH * 7 / 10, (float)data.WIDTH * 7 / 10}, side = (float)data.WIDTH / 10;
    for (int y=0; y<data.WIDTH; ++y) {
        for (int x=0; x<data.WIDTH; ++x) {
            if ((x >= leftTop[0]) && (x <= leftTop[0] + side) && (y >= leftTop[1]) && (y <= leftTop[1] + side)) {
                data.fColor2D[(x + y * data.WIDTH) * 3 + 0] = black[0];
                data.fColor2D[(x + y * data.WIDTH) * 3 + 1] = black[1];
                data.fColor2D[(x + y * data.WIDTH) * 3 + 2] = black[2];
                data.fOpacity2D[x + y * data.WIDTH] = opacity;
                data.fRefractivity2D[x + y * data.WIDTH] = 1.3;
            }
        }
    }
}

void ftle::sphereObject() {
    float black[] = {0., 0., 0.}, opacity = 0.1, refraction = 1.5;
    float center[] = {60., 50., 0.}, radius = 15;
    for (int y=0; y<data.WIDTH; ++y) {
        for (int x=0; x<data.WIDTH; ++x) {
            if ((x - center[0]) * (x - center[0]) + (y - center[1]) * (y - center[1]) < radius * radius) {
                data.fColor2D[(x + y * data.WIDTH) * 3 + 0] = black[0];
                data.fColor2D[(x + y * data.WIDTH) * 3 + 1] = black[1];
                data.fColor2D[(x + y * data.WIDTH) * 3 + 2] = black[2];
                data.fOpacity2D[x + y * data.WIDTH] = opacity;
                data.fRefractivity2D[x + y * data.WIDTH] = refraction;
            }
        }
    }
}

void ftle::makeGeometry2D() {
    std::memset(data.grad2D, 0., sizeof data.grad2D);
    std::memset(data.fRefractivity2D, 1., sizeof data.fRefractivity2D);
    std::memset(data.fRefractivity2D, 0., sizeof data.fRefractivity2D);

    for (int p=0; p<data.PLAINSZ; ++p) {
        data.fRefractivity2D[p] = 1.;
    }
    surroundWall();
    squareObject();
//    sphereObject();
}
