//
// Created by Nozomi on 2019-05-06.
//


#include "variables.h"
#include "myMath.h"
#include <iostream>
#include <cmath>

float roundInt (float x){
    float decimal = x - std::floor(x);
    if (decimal < 0.5) {
        return std::floor(x);
    } else {
        return std::ceil(x);
    }
}

float slope2 (float p1, float p2, int WIDTH){
    return (p2 - p1) / (100 / (float)WIDTH);
}
float slope3 (float p1, float p2, float p3, int WIDTH){
    return ((p2 - p1) / 2 + (p3 - p2) / 2) / (100 / (float)WIDTH);
}

bool checkInteger(float *vec){
    if ((std::ceil(vec[0]) == std::floor(vec[0])) && (std::ceil(vec[1]) == std::floor(vec[1])) && (std::ceil(vec[2]) == std::floor(vec[2])) ){
        return true;
    } else {
        return false;
    }
}

unsigned long pointerVectorCoordinateFloat(float *coordinate, int WIDTH){
    return ((int)coordinate[0] + (int)coordinate[1] * WIDTH + (int)coordinate[2] * WIDTH * WIDTH) * 3;
}

unsigned long pointerVectorCoordinateInt(int *coordinate, int WIDTH){
    return (coordinate[0] + coordinate[1] * WIDTH + coordinate[2] * WIDTH * WIDTH) * 3;
}

unsigned long pointerScalarCoordinateFloat(float *coordinate, int WIDTH){
    return ((int)coordinate[0] + (int)coordinate[1] * WIDTH + (int)coordinate[2] * WIDTH * WIDTH);
}

unsigned long pointerScalarCoordinateInt(int *coordinate, int WIDTH){
    return (coordinate[0] + coordinate[1] * WIDTH + coordinate[2] * WIDTH * WIDTH);
}

unsigned long valueVectorCoordinateFloat(float x, float y, float z, int WIDTH) {
    return ((int)x + (int)y * WIDTH + (int)z * WIDTH * WIDTH) * 3;
}

unsigned long valueVectorCoordinateInt(int x, int y, int z, int WIDTH) {
    return (x + y * WIDTH + z * WIDTH * WIDTH) * 3;
}

unsigned long valueScalarCoordinateFloat(float x, float y, float z, int WIDTH) {
    return ((int)x + (int)y * WIDTH + (int)z * WIDTH * WIDTH);
}

unsigned long valueScalarCoordinateInt(int x, int y, int z, int WIDTH) {
    return (x + y * WIDTH + z * WIDTH * WIDTH);
}

unsigned long valueVectorCoordinateFloatPhase(float x, float y, float z, int WIDTH, int maxPhase, int phase) {
    return (((int)x +(int)y * WIDTH + (int)z * WIDTH * WIDTH) * maxPhase + phase) * 3;
}
unsigned long valueVectorCoordinateIntPhase(int x, int y, int z, int WIDTH, int maxPhase, int phase) {
    return ((x + y * WIDTH + z * WIDTH * WIDTH) * maxPhase + phase) * 3;
}
unsigned long valueScalarCoordinateFloatPhase(float x, float y, float z, int WIDTH, int maxPhase, int phase) {
    return ((int)x +(int)y * WIDTH + (int)z * WIDTH * WIDTH) * maxPhase + phase;
}
unsigned long valueScalarCoordinateIntPhase(int x, int y, int z, int WIDTH, int maxPhase, int phase) {
    return (x + y * WIDTH + z * WIDTH * WIDTH) * maxPhase + phase;
}

void checkMinus(float *vec){
    if (vec[0] < 0){
        vec[0] = 0;
    } if (vec[1] < 0) {
        vec[1] = 0;
    } if (vec[2] < 0) {
        vec[2] = 0;
    }
}

bool checkRangeInt(int x, int side){
    if ((x >= 0) && (x < side)){
        return true;
    } else {
        return false;
    }
}

bool checkPosition(int x, int y, int z, int side) {
    if ((x < 0) || (x >= side)){
        return false;
    } else if ((y < 0) || (y >= side)) {
        return false;
    } else if ((z < 0) || (z >= side)) {
        return false;
    } else {
        return true;
    }
}

float checkRange(float x, int side){
    float c = x;
    if (x < 0){
        c = 0;
    } else if (x >= side){
        c = side - 0.01;
    }
    return c;
}

float gaussFunc(float x) {
    float c = 50;
    return exp(-x * x / 2 / c / c);
}

float exponential(float x) {
    return exp(x);
}

float myabs(float x) {
    if (x < 0) {
        return -x;
    } else {
        return x;
    }
}

float normFlobenius22 (float a00, float a01, float a10, float a11) {
    return sqrt(a00 * a00 + a01 * a01 + a10 * a10 + a11 * a11);
}