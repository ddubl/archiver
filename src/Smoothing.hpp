
#ifndef UFOCR_SMOOTHING_HPP
#define UFOCR_SMOOTHING_HPP

#include "opencv2/core.hpp"

namespace prl
{
enum class SmoothMethod
{
    Median,
    Gaussian,
    Bilateral
};

//TODO: Add more filters from ximgproc
extern "C" void smooth(const cv::Mat& src, cv::Mat& dst, SmoothMethod method = SmoothMethod::Bilateral);
}
#endif //UFOCR_SMOOTHING_HPP
