//
// Created by Nozomi on 2019-08-22.
//

#include <iostream>
#include <math.h>

#include "ftle.h"
#include "myMath.h"

//void gpuParticipate(int photonNumber, int time){
//    std::cout << "participating..." << std::endl;
//    clock_t start,end;
//    start = clock();
//
//    float* checker;
//    checker = (float *)malloc(sizeof(float) * photonNumber);
//
//    memset(lColor, 0., sizeof(float) * FIELDSZ * 3);
//
//    // プラットフォーム一覧を取得
//    cl_platform_id platforms[PLATFORM_MAX];
//    cl_uint platformCount;
//
//    EC(clGetPlatformIDs(PLATFORM_MAX, platforms, &platformCount), "clGetPlatformIDs");
//
//    // デバイス一覧を取得
//    cl_device_id devices[DEVICE_MAX];
//    cl_uint deviceCount;
//    EC(clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_GPU, DEVICE_MAX, devices, &deviceCount), "clGetDeviceIDs");
//
//    // コンテキストの作成
//    cl_context ctx = clCreateContext(nullptr, 1, devices, nullptr, nullptr, &err);
//    EC2("clCreateContext");
//
//    FILE *fp;
//    char fileName[] = "./photonParticipating.cl";
//    fp = fopen(fileName, "r");
//    if(!fp) {
//        std::cout << "no file.\n";
//        exit(1);
//    }
//
//    char *source_str;
//    size_t source_size;
//    source_str = (char*)malloc(0x10000);
//    source_size = fread(source_str, 1, 0x10000, fp);
//    fclose(fp);
//
//    // プログラムのビルド
//    cl_program program = NULL;
//    program = clCreateProgramWithSource(ctx, 1, (const char **)&source_str, (const size_t *)&source_size, &err);
//    clBuildProgram(program, 1, devices, NULL, NULL, NULL);
//
//    // カーネルの作成
//    cl_kernel kernel = clCreateKernel(program, "trace", &err);
//    EC2("clCreateKernel");
//
//    // コマンドキューの作成
//    cl_command_queue q = clCreateCommandQueue(ctx, devices[0], 0, &err);
//    EC2("clCreateCommandQueue");
//
//    cl_mem memGrad = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(float)*FIELDSZ*3, grad, &err);
//    cl_mem memDirection = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(float)*photonNumber*3, photonDirection, &err);
//    cl_mem memGradDirection = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(float)*photonNumber*3, photonGradDirection, &err);
//    cl_mem memPosition = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(float)*photonNumber*3, photonPosition, &err);
//    cl_mem mempColor = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(float)*photonNumber*3, photonColor, &err);
//    cl_mem memlColor = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(float)*FIELDSZ*3, lColor, &err);
//    cl_mem memfColor = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(float)*FIELDSZ*3, fColor, &err);
//    cl_mem memfOpacity = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(float)*FIELDSZ, fOpacity, &err);
//    cl_mem memfRefractivity = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(float)*FIELDSZ, fRefractivity, &err);
//    cl_mem memChecker = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(float)*photonNumber, checker, &err);
//    EC2("clCreateBuffer");
//
//    cl_int side = WIDTH;
//
//    EC(clSetKernelArg(kernel, 0, sizeof(cl_mem), &memGrad), "clSetKernelArg0");
//    EC(clSetKernelArg(kernel, 1, sizeof(cl_mem), &memDirection), "clSetKernelArg1");
//    EC(clSetKernelArg(kernel, 2, sizeof(cl_mem), &memGradDirection), "clSetKernelArg1");
//    EC(clSetKernelArg(kernel, 3, sizeof(cl_mem), &memPosition), "clSetKernelArg2");
//    EC(clSetKernelArg(kernel, 4, sizeof(cl_mem), &mempColor), "clSetKernelArg3");
//    EC(clSetKernelArg(kernel, 5, sizeof(cl_mem), &memlColor), "clSetKernelArg4");
//    EC(clSetKernelArg(kernel, 6, sizeof(cl_mem), &memfColor), "clSetKernelArg5");
//    EC(clSetKernelArg(kernel, 7, sizeof(cl_mem), &memfOpacity), "clSetKernelArg6");
//    EC(clSetKernelArg(kernel, 8, sizeof(cl_mem), &memfRefractivity), "clSetKernelArg7");
//    EC(clSetKernelArg(kernel, 9, sizeof(cl_int), &side), "clSetKernelArg8");
//    EC(clSetKernelArg(kernel, 10, sizeof(cl_mem), &memChecker), "clSetKernelArg9");
//
//    size_t global_item_size = photonNumber;
//    EC(clEnqueueNDRangeKernel(q, kernel, 1, nullptr, &global_item_size, nullptr, 0, nullptr, nullptr), "clEnqueueNDRangeKernel");
//
//    // 結果を読み込み
//    EC(clEnqueueReadBuffer(q, memlColor, CL_TRUE, 0, sizeof(float) * FIELDSZ * 3, lColor, 0, nullptr, nullptr), "clEnqueueReadBuffer");
//    EC(clEnqueueReadBuffer(q, memGradDirection, CL_TRUE, 0, sizeof(float) * photonNumber * 3, photonGradDirection, 0, nullptr, nullptr), "clEnqueueReadBuffer");
//    EC(clEnqueueReadBuffer(q, memDirection, CL_TRUE, 0, sizeof(float) * photonNumber * 3, photonDirection, 0, nullptr, nullptr), "clEnqueueReadBuffer");
//    EC(clEnqueueReadBuffer(q, memPosition, CL_TRUE, 0, sizeof(float) * photonNumber * 3, photonPosition, 0, nullptr, nullptr), "clEnqueueReadBuffer");
//    EC(clEnqueueReadBuffer(q, mempColor, CL_TRUE, 0, sizeof(float) * photonNumber * 3, photonColor, 0, nullptr, nullptr), "clEnqueueReadBuffer");
//    EC(clEnqueueReadBuffer(q, memChecker, CL_TRUE, 0, sizeof(float) * photonNumber, checker, 0, nullptr, nullptr), "clEnqueueReadBuffer");
//
////    int iniP = photonNumber / 2;
////    for (int position=iniP; position < iniP+WIDTH; ++position){
////        std::cout << checker[position] << " ";
////    }
////    printf("\n");
//
//    end = clock();
//    printf("%lf seconds\n",(double)(end-start)/CLOCKS_PER_SEC);
//
//    // コマンドキューの解放
//    EC(clReleaseCommandQueue(q), "clReleaseCommandQueue");
//    // デバイスメモリを解放
//    EC(clReleaseMemObject(memGrad), "clReleaseMemObject");
//    EC(clReleaseMemObject(memDirection), "clReleaseMemObject");
//    EC(clReleaseMemObject(memPosition), "clReleaseMemObject");
//    EC(clReleaseMemObject(mempColor), "clReleaseMemObject");
//    EC(clReleaseMemObject(memlColor), "clReleaseMemObject");
//    EC(clReleaseMemObject(memfColor), "clReleaseMemObject");
//    EC(clReleaseMemObject(memfRefractivity), "clReleaseMemObject");
//    EC(clReleaseMemObject(memChecker), "clReleaseMemObject");
//    // カーネルの解放
//    EC(clReleaseKernel(kernel), "clReleaseKernel");
//    // プログラムの解放
//    EC(clReleaseProgram(program), "clReleaseProgram");
//    // コンテキストの解放
//    EC(clReleaseContext(ctx), "clReleaseContext");
//
//    free(source_str);
//    free(checker);
//}
//

void biInter(float* tf, float* bf, float* tb, float* bb, float ratioy, float ratioz, float* value){
    float t[3], b[3];
    t[0] = tf[0] * (1 - ratioz) + tb[0] * ratioz;
    t[1] = tf[1] * (1 - ratioz) + tb[1] * ratioz;
    t[2] = tf[2] * (1 - ratioz) + tb[2] * ratioz;
    b[0] = bf[0] * (1 - ratioz) + bb[0] * ratioz;
    b[1] = bf[1] * (1 - ratioz) + bb[1] * ratioz;
    b[2] = bf[2] * (1 - ratioz) + bb[2] * ratioz;

    value[0] = t[0] * (1 - ratioy) + b[0] * ratioy;
    value[1] = t[1] * (1 - ratioy) + b[1] * ratioy;
    value[2] = t[2] * (1 - ratioy) + b[2] * ratioy;
}

void ftle::trilinearTrace(float x, float y, float z, bool flag2D, float *gradient, float *opacity) {
    unsigned int p;

    if ((x < 0) || (y < 0) | (z < 0) || (x >= data.WIDTH) || (y >= data.WIDTH) || (z >= data.WIDTH)) {
//        std::cout << "out of field in trilinearTrace\n";
        x = checkRange(x, data.WIDTH);
        y = checkRange(y, data.WIDTH);
        z = checkRange(z, data.WIDTH);
        p = ((int) (x) + (int) (y) * data.WIDTH + (int) (z) * data.WIDTH * data.WIDTH);
        *opacity = data.fOpacity2D[p];
    } else {
        float ltf[] = {floor(x), floor(y), floor(z)};
        float lbf[] = {floor(x), floor(y) + 1, floor(z)};
        float rtf[] = {floor(x) + 1, floor(y), floor(z)};
        float rbf[] = {floor(x) + 1, floor(y) + 1, floor(z)};
        float ltb[] = {floor(x), floor(y), floor(z) + 1};
        float lbb[] = {floor(x), floor(y) + 1, floor(z) + 1};
        float rtb[] = {floor(x) + 1, floor(y), floor(z) + 1};
        float rbb[] = {floor(x) + 1, floor(y) + 1, floor(z) + 1};

        float ratiox = myabs(x - floor(x));
        float ratioy = myabs(y - floor(y));
        float ratioz = myabs(z - floor(z));

        float tf[3], bf[3], tb[3], bb[3], t[3], b[3];

        //    reflectivity = fReflectivity[getScalarCoo(ltf)];
        *opacity = data.fOpacity2D[pointerScalarCoordinateFloat(ltf, data.WIDTH)];

        if (flag2D) {
            tf[0] = data.grad2D[pointerVectorCoordinateFloat(ltf, data.WIDTH)];
            tf[1] = data.grad2D[pointerVectorCoordinateFloat(ltf, data.WIDTH) + 1];
            tf[2] = data.grad2D[pointerVectorCoordinateFloat(ltf, data.WIDTH) + 2];
            bf[0] = data.grad2D[pointerVectorCoordinateFloat(rtf, data.WIDTH)];
            bf[1] = data.grad2D[pointerVectorCoordinateFloat(rtf, data.WIDTH) + 1];
            bf[2] = data.grad2D[pointerVectorCoordinateFloat(rtf, data.WIDTH) + 2];
            tb[0] = data.grad2D[pointerVectorCoordinateFloat(lbf, data.WIDTH)];
            tb[1] = data.grad2D[pointerVectorCoordinateFloat(lbf, data.WIDTH) + 1];
            tb[2] = data.grad2D[pointerVectorCoordinateFloat(lbf, data.WIDTH) + 2];
            bb[0] = data.grad2D[pointerVectorCoordinateFloat(rbf, data.WIDTH)];
            bb[1] = data.grad2D[pointerVectorCoordinateFloat(rbf, data.WIDTH) + 1];
            bb[2] = data.grad2D[pointerVectorCoordinateFloat(rbf, data.WIDTH) + 2];
            biInter(tf, bf, tb, bb, ratiox, ratioy, gradient);
        } else {
            tf[0] = data.grad2D[pointerVectorCoordinateFloat(ltf, data.WIDTH)] * (1 - ratiox) +
                    data.grad2D[pointerVectorCoordinateFloat(rtf, data.WIDTH)] * ratiox;
            tf[1] = data.grad2D[pointerVectorCoordinateFloat(ltf, data.WIDTH) + 1] * (1 - ratiox) +
                    data.grad2D[pointerVectorCoordinateFloat(rtf, data.WIDTH) + 1] * ratiox;
            tf[2] = data.grad2D[pointerVectorCoordinateFloat(ltf, data.WIDTH) + 2] * (1 - ratiox) +
                    data.grad2D[pointerVectorCoordinateFloat(rtf, data.WIDTH) + 2] * ratiox;
            bf[0] = data.grad2D[pointerVectorCoordinateFloat(lbf, data.WIDTH)] * (1 - ratiox) +
                    data.grad2D[pointerVectorCoordinateFloat(rbf, data.WIDTH)] * ratiox;
            bf[1] = data.grad2D[pointerVectorCoordinateFloat(lbf, data.WIDTH) + 1] * (1 - ratiox) +
                    data.grad2D[pointerVectorCoordinateFloat(rbf, data.WIDTH) + 1] * ratiox;
            bf[2] = data.grad2D[pointerVectorCoordinateFloat(lbf, data.WIDTH) + 2] * (1 - ratiox) +
                    data.grad2D[pointerVectorCoordinateFloat(rbf, data.WIDTH) + 2] * ratiox;
            tb[0] = data.grad2D[pointerVectorCoordinateFloat(ltb, data.WIDTH)] * (1 - ratiox) +
                    data.grad2D[pointerVectorCoordinateFloat(rtb, data.WIDTH)] * ratiox;
            tb[1] = data.grad2D[pointerVectorCoordinateFloat(ltb, data.WIDTH) + 1] * (1 - ratiox) +
                    data.grad2D[pointerVectorCoordinateFloat(rtb, data.WIDTH) + 1] * ratiox;
            tb[2] = data.grad2D[pointerVectorCoordinateFloat(ltb, data.WIDTH) + 2] * (1 - ratiox) +
                    data.grad2D[pointerVectorCoordinateFloat(rtb, data.WIDTH) + 2] * ratiox;
            bb[0] = data.grad2D[pointerVectorCoordinateFloat(lbb, data.WIDTH)] * (1 - ratiox) +
                    data.grad2D[pointerVectorCoordinateFloat(rbb, data.WIDTH)] * ratiox;
            bb[1] = data.grad2D[pointerVectorCoordinateFloat(lbb, data.WIDTH) + 1] * (1 - ratiox) +
                    data.grad2D[pointerVectorCoordinateFloat(rbb, data.WIDTH) + 1] * ratiox;
            bb[2] = data.grad2D[pointerVectorCoordinateFloat(lbb, data.WIDTH) + 2] * (1 - ratiox) +
                    data.grad2D[pointerVectorCoordinateFloat(rbb, data.WIDTH) + 2] * ratiox;
            biInter(tf, bf, tb, bb, ratioy, ratioz, gradient);
        }
    }
}


void ftle::trace3d(int photon) {
    float x = data.photonPosition2D[photon * 3 + 0];
    float y = data.photonPosition2D[photon * 3 + 1];
    float z = data.photonPosition2D[photon * 3 + 2];
    float dirx = data.photonDirection2D[photon * 3 + 0];
    float diry = data.photonDirection2D[photon * 3 + 1];
    float dirz = data.photonDirection2D[photon * 3 + 2];
    float opacity = 0., path[3], calcStep = 3., square, newGradient[3], newOpacity;

    while (!(x < 0) && !(y < 0) && !(z < 0)&& !(x >= data.WIDTH) && !(y >= data.WIDTH) && !(z >= data.WIDTH)){
        trilinearTrace(x, y, z, true, newGradient, &newOpacity);

        if (data.fReflectivity2D[(int)(x + y * data.WIDTH + z * data.WIDTH * data.WIDTH) == 1.]) {
            // refrecttion
            float normalizeN[3], projection[3], inpro, norm;
            normalize3Vector(newGradient, normalizeN);
            inpro = dirx * newGradient[0] + diry * newGradient[1] + dirz * newGradient[2];
            if (inpro < 0) {
                inpro = - inpro;
            }
            // the norm of normalizeN is 1
            projection[0] = inpro * normalizeN[0];
            projection[1] = inpro * normalizeN[1];
            projection[2] = inpro * normalizeN[2];

            dirx = dirx - 2 * projection[0];
            diry = dirx - 2 * projection[1];
            dirz = dirx - 2 * projection[2];
        } else {
            opacity += (1 - opacity) * newOpacity;
            newGradient[0] = newGradient[0] * 100 / data.WIDTH / calcStep;
            newGradient[1] = newGradient[1] * 100 / data.WIDTH / calcStep;
            newGradient[2] = newGradient[2] * 100 / data.WIDTH / calcStep;

            dirx += newGradient[0];
            diry += newGradient[1];
            dirz += newGradient[2];
        }
        square = dirx * dirx + diry * diry + dirz * dirz;
        path[0] = dirx / sqrt(square);
        path[1] = diry / sqrt(square);
        path[2] = dirz / sqrt(square);

        x = x + path[0] / calcStep;
        y = y + path[1] / calcStep;
        z = z + path[2] / calcStep;

        if (myabs(opacity - 1.0) < 0.001) {
            break;
        }
    }

    // store data
    data.photonDestinatePosition[photon * 3 + 0] = x;
    data.photonDestinatePosition[photon * 3 + 1] = y;
    data.photonDestinatePosition[photon * 3 + 2] = z;
    data.photonDestinateDirection[photon * 3 + 0] = dirx;
    data.photonDestinateDirection[photon * 3 + 1] = diry;
    data.photonDestinateDirection[photon * 3 + 2] = dirz;
}

void ftle::photonDestinate(void) {
    memset(data.photonDestinateDirection, 0., sizeof(float) * data.maxPhoton2D * 3);
    memset(data.photonDestinatePosition, 0., sizeof(float) * data.maxPhoton2D * 3);

    for (int photon = 0; photon < data.maxPhoton2D; ++photon) {
        trace3d(photon);
    }
}