//
// Created by Nozomi on 2019-08-24.
//

#include "ftle.h"

#include <sstream>\
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <math.h>

cv::Scalar colorCode(float value, float max, float min) {
    cv::Scalar color;
    value = (value - min) / (max - min);

    if (value >= 0 && value <= 0.25) {
        color[0] = 255;      //B
        color[1] = (int)((double)255 * sin(value * 2 * M_PI));        //G
        color[2] = 0;        //R
    }
    else if (value > 0.25 && value <= 0.5) {
        color[0] = (int)((double)255 * sin(value * 2 * M_PI));  //B
        color[1] = 255;      //G
        color[2] = 0;        //R
    }
    else if (value > 0.5 && value <= 0.75) {
        color[0] = 0;        //B
        color[1] = 255;      //G
        color[2] = (int)(-(double)255 * sin(value * 2 * M_PI));  //R
    }
    else {
        color[0] = 0;        //B
        color[1] = (int)(-(double)255 * sin(value * 2 * M_PI));  //G
        color[2] = 255;      //R
    }
    return color;
}

double norm2Vec (float a, float b) {
    return sqrt((a * a) + (b * b));
}

void ftle::visualizeGrad2D(void) {
    //  make image of the object field
    std::vector<double> norm(data.PLAINSZ);
    int magnify = 5;

    for (int y=0; y<data.WIDTH; ++y) {
        for (int x=0; x<data.WIDTH; ++x) {
//            std::cout << norm2Vec(data.grad2D[(x + y * data.WIDTH) * 3], data.grad2D[(x + y * data.WIDTH) * 3 + 1]) << " ";
            norm[x + y * data.WIDTH] = norm2Vec(data.grad2D[(x + y * data.WIDTH) * 3], data.grad2D[(x + y * data.WIDTH) * 3 + 1]);
//            norm[x + y * data.WIDTH] = data.grad2D[(x + y * data.WIDTH) * 3 + 0];
        }
    }
    float max = *std::max_element(norm.begin(), norm.end());
    float min = *std::min_element(norm.begin(), norm.end());

    cv::Scalar color;
    cv::Mat grad(cv::Size(data.WIDTH * magnify, data.WIDTH * magnify), CV_8UC3);
    for (int y=0; y<data.WIDTH; ++y){
        for (int x=0; x<data.WIDTH; ++x){
            for (int i=0; i<magnify; ++i){
                for (int j=0; j<magnify; ++j) {
                    color = colorCode(norm[x + y * data.WIDTH], max, min);
                    grad.at<cv::Vec3b>(y * magnify + j, x * magnify + i)[0] = color[0];
                    grad.at<cv::Vec3b>(y * magnify + j, x * magnify + i)[1] = color[1];
                    grad.at<cv::Vec3b>(y * magnify + j, x * magnify + i)[2] = color[2];
                }
            }
        }
    }
    imwrite("../image/grad2D.png", grad);
    printf("img written\n");
}

void ftle::visualize2DAverage(void) {
    float* averagePosition = new float[data.PLAINSZ * 3];
    float* averageDirection = new float [data.PLAINSZ * 3];
    std::vector<float> averageNormPosition(data.PLAINSZ, 0.);
    std::vector<float> averageNormDirection(data.PLAINSZ, 0.);

    printf("processing...\n");

    for (int position=0; position<data.PLAINSZ; ++position) {
        float sumx = 0., sumy = 0., sumz = 0., sumxDir = 0., sumyDir = 0., sumzDir = 0.;
        for (int phi=0; phi<data.phaseNum; ++phi) {
            sumx += data.photonDestinatePosition[(position * data.phaseNum + phi) * 3 + 0];
            sumy += data.photonDestinatePosition[(position * data.phaseNum + phi) * 3 + 1];
            sumz += data.photonDestinatePosition[(position * data.phaseNum + phi) * 3 + 2];
            sumxDir += data.photonDestinateDirection[(position * data.phaseNum + phi) * 3 + 0];
            sumyDir += data.photonDestinateDirection[(position * data.phaseNum + phi) * 3 + 1];
            sumzDir += data.photonDestinateDirection[(position * data.phaseNum + phi) * 3 + 2];
        }
        averagePosition[position * 3 + 0] = sumx / data.phaseNum;
        averagePosition[position * 3 + 1] = sumy / data.phaseNum;
        averagePosition[position * 3 + 2] = sumz / data.phaseNum;
        averageDirection[position * 3 + 0] = sumxDir / data.phaseNum;
        averageDirection[position * 3 + 1] = sumyDir / data.phaseNum;
        averageDirection[position * 3 + 2] = sumzDir / data.phaseNum;
    }
    printf("processing...\n");

    gradVectorField2D(averageDirection, averageNormDirection);
    gradVectorField2D(averagePosition, averageNormPosition);

    int magnify = 5;
    cv::Scalar white(255, 255, 255);
    cv::Mat ftlemap(cv::Size(data.WIDTH * magnify, data.WIDTH * magnify), CV_8UC3, white);

    printf("processing...\n");
    float min = *std::min_element(averageNormPosition.begin(), averageNormPosition.end());
    float max = *std::max_element(averageNormPosition.begin(), averageNormPosition.end());
    for (int x=0; x<data.WIDTH; ++x) {
        for (int y=0; y<data.WIDTH; ++y) {
            cv::Scalar color = colorCode(averageNormPosition[x + y * data.WIDTH], max, min);
            for (int i=0; i<magnify; ++i) {
                for (int j=0; j<magnify; ++j) {
                    ftlemap.at<cv::Vec3b>(y * magnify + j, x * magnify + i)[0] = color[0];
                    ftlemap.at<cv::Vec3b>(y * magnify + j, x * magnify + i)[1] = color[1];
                    ftlemap.at<cv::Vec3b>(y * magnify + j, x * magnify + i)[2] = color[2];
                }
            }
        }
    }
    imwrite("../image/averageFTLE.png", ftlemap);

    delete[] averageDirection;
    delete[] averagePosition;
}

void ftle::visualize2D(void) {
    std::vector<float> normPosition(data.PLAINSZ, 0.);
    std::vector<float> normDirection(data.PLAINSZ, 0.);
    std::vector<float> totalNormPosition(data.PLAINSZ, 0.);
    std::vector<float> totalNormDirection(data.PLAINSZ, 0.);
    int magnify = 5;
    for (int phi=0; phi<data.phaseNum; ++phi) {
        float *currentPhotonPosition = new float[data.maxPhoton2D / data.phaseNum * 3];
        float *currentPhotonDirection = new float[data.maxPhoton2D / data.phaseNum * 3];
        cv::Scalar white(255, 255, 255);
        cv::Scalar black(0, 0, 0);
        cv::Mat ftlemap(cv::Size(data.WIDTH * magnify, data.WIDTH * magnify), CV_8UC3, white);

        for (int position=0; position < data.PLAINSZ; position++) {
            currentPhotonDirection[position * 3 + 0] = data.photonDestinateDirection[
                    (position * data.phaseNum + phi) * 3 + 0];
            currentPhotonDirection[position * 3 + 1] = data.photonDestinateDirection[
                    (position * data.phaseNum + phi) * 3 + 1];
            currentPhotonDirection[position * 3 + 2] = data.photonDestinateDirection[
                    (position * data.phaseNum + phi) * 3 + 2];
            currentPhotonPosition[position * 3 + 0] = data.photonDestinatePosition[
                    (position * data.phaseNum + phi) * 3 + 0];
            currentPhotonPosition[position * 3 + 1] = data.photonDestinatePosition[
                    (position * data.phaseNum + phi) * 3 + 1];
            currentPhotonPosition[position * 3 + 2] = data.photonDestinatePosition[
                    (position * data.phaseNum + phi) * 3 + 2];
        }
        gradVectorField2D(currentPhotonDirection, normDirection);
        gradVectorField2D(currentPhotonPosition, normPosition);

        float min = *std::min_element(normPosition.begin(), normPosition.end());
        float max = *std::max_element(normPosition.begin(), normPosition.end());
        for (int x=0; x<data.WIDTH; ++x) {
            for (int y=0; y<data.WIDTH; ++y) {
                cv::Scalar color = colorCode(normPosition[x + y * data.WIDTH], max, min);
                data.normPosition[(x + y * data.WIDTH) * data.phaseNum + phi] = normPosition[x + y * data.WIDTH];
                data.normDirection[(x + y * data.WIDTH) * data.phaseNum + phi] = normDirection[x + y * data.WIDTH];
                for (int i=0; i<magnify; ++i) {
                    for (int j=0; j<magnify; ++j) {
                        ftlemap.at<cv::Vec3b>(y * magnify + j, x * magnify + i)[0] = color[0];
                        ftlemap.at<cv::Vec3b>(y * magnify + j, x * magnify + i)[1] = color[1];
                        ftlemap.at<cv::Vec3b>(y * magnify + j, x * magnify + i)[2] = color[2];
                    }
                }
                float ex = data.photonDestinatePosition[((x + y * data.WIDTH) * data.phaseNum + phi) * 3 + 0];
                float ey = data.photonDestinatePosition[((x + y * data.WIDTH) * data.phaseNum + phi) * 3 + 1];
                if ((x % 10 == 0) && (y % 10 == 0)) {
                    cv::Point start = cv::Point(x * magnify + magnify / 2, y * magnify + magnify / 2);
                    cv::Point end = cv::Point((int)(ex) * magnify + magnify / 2, (int)(ey) * magnify + magnify / 2);
                    cv::arrowedLine(ftlemap, start, end, cv::Scalar(30, 30, 30), 1, 4);
                }
            }
        }

        std::ostringstream number;
        number << phi;
        imwrite("../image/phase-" + number.str() + ".png", ftlemap);

        for (int i=0; i<data.PLAINSZ; ++i) {
            totalNormPosition[i] += normPosition[i];
            totalNormDirection[i] += normDirection[i];
        }

        delete[] currentPhotonDirection;
        delete[] currentPhotonPosition;
    }
    cv::Scalar white(255, 255, 255);
    cv::Mat totalftlemap(cv::Size(data.WIDTH * magnify, data.WIDTH * magnify), CV_8UC3, white);
    float min = *std::min_element(totalNormPosition.begin(), totalNormPosition.end());
    float max = *std::max_element(totalNormPosition.begin(), totalNormPosition.end());
    for (int x=0; x<data.WIDTH; ++x) {
        for (int y=0; y<data.WIDTH; ++y) {
            cv::Scalar color = colorCode(totalNormPosition[x + y * data.WIDTH], max, min);
            for (int i=0; i<magnify; ++i) {
                for (int j=0; j<magnify; ++j) {
                    totalftlemap.at<cv::Vec3b>(y * magnify + j, x * magnify + i)[0] = color[0];
                    totalftlemap.at<cv::Vec3b>(y * magnify + j, x * magnify + i)[1] = color[1];
                    totalftlemap.at<cv::Vec3b>(y * magnify + j, x * magnify + i)[2] = color[2];
                }
            }
        }
    }
    imwrite("../image/totalFTLE.png", totalftlemap);
}