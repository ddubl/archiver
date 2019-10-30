
#ifndef PRLIB_SAUVOLABINARIZATION_H
#define PRLIB_SAUVOLABINARIZATION_H

#include "opencv2/core.hpp"

namespace prl
{
    void sauvolaBinarization(
            cv::Mat &imageCopy, cv::Mat& imageSauvola,
            int windowSize = 101,
            double thresholdCoefficient = 0.01,
            int morphIterationCount = 2);
}

#endif //PRLIB_SAUVOLABINARIZATION_H
