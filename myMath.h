//
// Created by Nozomi on 2019-05-06.
//

#ifndef REFRACTION_OPENCL_MYMATH_H
#define REFRACTION_OPENCL_MYMATH_H

float roundInt (float x);
float slope2 (float p1, float p2, int WIDTH);
float slope3 (float p1, float p2, float p3, int WIDTH);
bool checkInteger(float *vec);
unsigned long pointerVectorCoordinateFloat(float *coordinate, int WIDTH);
unsigned long pointerVectorCoordinateInt(int *coordinate, int WIDTH);
unsigned long pointerScalarCoordinateFloat(float *coordinate, int WIDTH);
unsigned long pointerScalarCoordinateInt(int *coordinate, int WIDTH);
unsigned long valueVectorCoordinateFloat(float x, float y, float z, int WIDTH);
unsigned long valueVectorCoordinateInt(int x, int y, int z, int WIDTH);
unsigned long valueScalarCoordinateFloat(float x, float y, float z, int WIDTH);
unsigned long valueScalarCoordinateInt(int x, int y, int z, int WIDTH);
unsigned long valueVectorCoordinateFloatPhase(float x, float y, float z, int WIDTH, int maxPhase, int phase);
unsigned long valueVectorCoordinateIntPhase(int x, int y, int z, int WIDTH, int maxPhase, int phase);
unsigned long valueScalarCoordinateFloatPhase(float x, float y, float z, int WIDTH, int maxPhase, int phase);
unsigned long valueScalarCoordinateIntPhase(int x, int y, int z, int WIDTH, int maxPhase, int phase);
void checkMinus(float *vec);
bool checkRangeInt(int x, int side);
float checkRange(float x, int side);
float gaussFunc(float x);
float exponential(float x);
bool checkPosition(int x, int y, int z, int side);
float myabs(float x);
float normFlobenius22 (float a00, float a01, float a10, float a11);
void normalize3Vector(float *a, float *b);
float norm3Vectoor(float *a);
bool checkRangeFloat(float x, int side);

#endif //REFRACTION_OPENCL_MYMATH_H
