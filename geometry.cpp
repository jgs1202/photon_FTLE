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
            }
        }
    }
}

void ftle::squareObject() {
    float black[] = {0., 0., 0.}, opacity = 1.;
    float leftTop[] = {(float)data.WIDTH / 2, (float)data.WIDTH / 2}, side = (float)data.WIDTH / 10;
    for (int y=0; y<data.WIDTH; ++y) {
        for (int x=0; x<data.WIDTH; ++x) {
            if ((x >= leftTop[0]) && (x <= leftTop[0] + side) && (y >= leftTop[1]) && (y <= leftTop[1] + side)) {
                data.fColor2D[(x + y * data.WIDTH) * 3 + 0] = black[0];
                data.fColor2D[(x + y * data.WIDTH) * 3 + 1] = black[1];
                data.fColor2D[(x + y * data.WIDTH) * 3 + 2] = black[2];
                data.fOpacity2D[x + y * data.WIDTH] = opacity;
            }
        }
    }
}

void ftle::makeGeometry2D() {
    std::memset(data.grad2D, 0, sizeof data.grad2D);
    surroundWall();
    squareObject();
}
