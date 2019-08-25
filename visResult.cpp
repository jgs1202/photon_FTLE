//
// Created by Nozomi on 2019-08-24.
//

#include "ftle.h"

#include <sstream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <math.h>


cv::Scalar colorCode(cv::Mat image, int size, int position, float value, float max, float min) {
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
}

void ftle::visualize2D(void) {
    for (int phi=0; phi<data.phaseNum; ++phi) {

        std::cout << "phi is " << phi << std::endl;

        float *currentPhotonPosition = new float[data.maxPhoton2D / data.phaseNum * 3];
        float *currentPhotonDirection = new float[data.maxPhoton2D / data.phaseNum * 3];
        float *normPhotonDirection = new float[data.maxPhoton2D / data.phaseNum];
        float *normPhotonPosition = new float[data.maxPhoton2D / data.phaseNum];

        std::vector<float> normPosition(data.PLAINSZ);
        std::vector<float> normDirection(data.PLAINSZ);

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

        std::cout << normPhotonPosition[350] << std::endl;

        cv::Scalar white(255, 255, 255);
        cv::Mat heatmap(cv::Size(data.WIDTH, data.WIDTH), CV_8UC4, white);

        float min = *std::min_element(normPosition.begin(), normPosition.end());
        float max = *std::max_element(normPosition.begin(), normPosition.end());


        for (int p=0; p<data.PLAINSZ; ++p) {
            cv::Scalar color = colorCode(heatmap, p, normPosition[p], max, min);
            heatmap.at<cv::Vec4b>(p)[0] = color[0];
            heatmap.at<cv::Vec4b>(p)[1] = color[1];
            heatmap.at<cv::Vec4b>(p)[2] = color[2];
        }

        std::ostringstream number;
        number << phi;
        imwrite("../image/phase-" + number.str() + ".png", heatmap);

    }
}