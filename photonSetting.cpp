//
// Created by Nozomi on 2019-08-22.
//

#include <math.h>

#include "ftle.h"
#include "gpuSetting.h"
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

void ftle::photonInitGpu(void) {
    std::cout << "propergating light..." << std::endl;

    float* checker;
    checker = (float *)malloc(sizeof(float) * data.PLAINSZ);
    cl_int side = data.WIDTH;

    clock_t start,end;
    start = clock();

    // プラットフォーム一覧を取得
    cl_platform_id platforms[data.PLATFORM_MAX];
    cl_uint platformCount;
    EC(clGetPlatformIDs(data.PLATFORM_MAX, platforms, &platformCount), "clGetPlatformIDs");
    if (platformCount == 0) {
        std::cerr << "No platform.\n";
    }

    // デバイス一覧を取得
    cl_device_id devices[data.DEVICE_MAX];
    cl_uint deviceCount;
    EC(clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_GPU, data.DEVICE_MAX, devices, &deviceCount), "clGetDeviceIDs");
    if (deviceCount == 0) {
        std::cerr << "No device.\n";
    }

    // コンテキストの作成
    cl_context ctx = clCreateContext(nullptr, 1, devices, nullptr, nullptr, &err);
    EC2("clCreateContext");

    FILE *fp;
    char fileName[] = "../photonSetting.cl";
    fp = fopen(fileName, "r");
    if(!fp) {
        std::cout << "no file.\n";
        exit(1);
    }

    char *source_str;
    size_t source_size;
    source_str = (char*)malloc(0x5000);
    source_size = fread(source_str, 1, 0x5000, fp);
    fclose(fp);

    // プログラムのビルド
    cl_program program = NULL;
    program = clCreateProgramWithSource(ctx, 1, (const char **)&source_str, (const size_t *)&source_size, &err);
    clBuildProgram(program, 1, devices, NULL, NULL, NULL);

    // カーネルの作成
    cl_kernel kernel = clCreateKernel(program, "setPhotons", &err);
    EC2("clCreateKernel");



    // デバイスメモリを確保しつつデータをコピ-
    // make buffer
    cl_mem memGrad;
    cl_mem memfColor;
    cl_mem memfMedium;
    cl_mem memfOpacity;
    cl_mem memlColor;
    cl_mem memlDirection;
    cl_mem memlIntensity;
    cl_mem memChecker;
    EC2("clCreateBuffer");

//    // コマンドキューの作成
//    cl_command_queue q = clCreateCommandQueue(ctx, devices[0], 0, &err);
//
//    for (cl_int plain=0; plain<2; ++plain) {
//        // write buffer
////        std::cout << "plain: " << plain << std::endl;
//        if (plain == 0) {
//            for (unsigned int j=0; j<data.WIDTH; ++j) {
//                for (unsigned int k=0; k < data.WIDTH; ++k) {
//                    unsigned coordinate = (j + k * data.WIDTH);
//                    setVec3Float(&lColor[coordinate * 3], color);
//                    lIntensity[coordinate] = 1.0;
//                    setVec3Float(&lDirection[coordinate * 3], direction);
//                }
//            }
//        } else {
//
//            memGrad = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(float)*FIELDSZ*3, grad, &err);
//            memfColor = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(float)*FIELDSZ*3, fColor, &err);
//            memfMedium = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(float)*FIELDSZ*3, fMedium, &err);
//            memfOpacity = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(float)*FIELDSZ, fOpacity, &err);
//            memlColor = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(float)*FIELDSZ*3, lColor, &err);
//            memlDirection = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(float)*FIELDSZ*3, lDirection, &err);
//            memlIntensity = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(float)*FIELDSZ, lIntensity, &err);
//            memChecker = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(float) * PLAINSZ, checker, &err);
//            EC2("clCreateBuffer");
//
//            EC(clSetKernelArg(kernel, 0, sizeof(cl_mem), &memGrad), "clSetKernelArg");
//            EC(clSetKernelArg(kernel, 1, sizeof(cl_mem), &memfColor), "clSetKernelArg");
//            EC(clSetKernelArg(kernel, 2, sizeof(cl_mem), &memfMedium), "clSetKernelArg");
//            EC(clSetKernelArg(kernel, 3, sizeof(cl_mem), &memfOpacity), "clSetKernelArg");
//            EC(clSetKernelArg(kernel, 4, sizeof(cl_mem), &memlColor), "clSetKernelArg");
//            EC(clSetKernelArg(kernel, 5, sizeof(cl_mem), &memlDirection), "clSetKernelArg");
//            EC(clSetKernelArg(kernel, 6, sizeof(cl_mem), &memlIntensity), "clSetKernelArg");
//            EC(clSetKernelArg(kernel, 7, sizeof(cl_int), &side), "clSetKernelArg");
//            EC(clSetKernelArg(kernel, 8, sizeof(cl_int), &plain), "clSetKernelArg");
//            EC(clSetKernelArg(kernel, 9, sizeof(cl_mem), &memChecker), "clSetKernelArg");
//
//            EC2("clCreateCommandQueue");
//
////            size_t local_item_size = data.WIDTH;
//            size_t global_item_size = data.WIDTH * data.WIDTH;
//
//            EC(clEnqueueNDRangeKernel(q, kernel, 1, nullptr, &global_item_size, nullptr, 0, nullptr, nullptr), "clEnqueueNDRangeKernel");
//
//            // 結果を読み込み
//            EC(clEnqueueReadBuffer(q, memlColor, CL_TRUE, 0, sizeof(float) * FIELDSZ * 3, lColor, 0, nullptr, nullptr), "clEnqueueReadBuffer");
//            EC(clEnqueueReadBuffer(q, memlDirection, CL_TRUE, 0, sizeof(float) * FIELDSZ * 3, lDirection, 0, nullptr, nullptr), "clEnqueueReadBuffer");
//            EC(clEnqueueReadBuffer(q, memlIntensity, CL_TRUE, 0, sizeof(float) * FIELDSZ, lIntensity, 0, nullptr, nullptr), "clEnqueueReadBuffer");
//            EC(clEnqueueReadBuffer(q, memChecker, CL_TRUE, 0, sizeof(float) * PLAINSZ, checker, 0, nullptr, nullptr), "clEnqueueReadBuffer");
//
////            std::cout << "new      " << nlDirection[(43 + 98 * data.WIDTH) * 3] << " " << checker[(43 + 98 * data.WIDTH)] << std::endl;
//
////            lightSmoothing(lColor);
////            lightSmoothing(lDirection);
////            lightSmoothing(lDirection);
//
//            if (plain == 1) {
//                for (int p=0; p<data.WIDTH; ++p) {
//                    std::cout << (checker[p + plainY * data.WIDTH]) << " ";
//                }
//                printf("\n");
//            }
//        }
//    }
//
//    end = clock();
//    printf("%lf seconds\n",(double)(end-start)/CLOCKS_PER_SEC);
//
//    // コマンドキューの解放
//    EC(clReleaseCommandQueue(q), "clReleaseCommandQueue");
//    // デバイスメモリを解放
//    EC(clReleaseMemObject(memGrad), "clReleaseMemObject");
//    EC(clReleaseMemObject(memfColor), "clReleaseMemObject");
//    EC(clReleaseMemObject(memfMedium), "clReleaseMemObject");
//    EC(clReleaseMemObject(memfOpacity), "clReleaseMemObject");
//    EC(clReleaseMemObject(memlColor), "clReleaseMemObject");
//    EC(clReleaseMemObject(memlDirection), "clReleaseMemObject");
//    EC(clReleaseMemObject(memlIntensity), "clReleaseMemObject");
//    EC(clReleaseMemObject(memChecker), "clReleaseMemObject");
//
//    // カーネルの解放
//    EC(clReleaseKernel(kernel), "clReleaseKernel");
//    // プログラムの解放
//    EC(clReleaseProgram(program), "clReleaseProgram");
//    // コンテキストの解放
//    EC(clReleaseContext(ctx), "clReleaseContext");
//
//    free(source_str);
//    delete[] checker;
//
//    visLight();
//    visLightDirection();
//



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