
#ifndef UFOCR_COLORBALANCE_HPP
#define UFOCR_COLORBALANCE_HPP

#include <opencv2/core.hpp>

namespace prl
{
//TODO: Add white balance, gamma-correction. Manual and automatic
enum class ColorBalance
{
    Simple, Grayworld
};

extern "C" void whiteBalance(const cv::Mat& src, cv::Mat& dst, ColorBalance method = ColorBalance::Simple);
}
#endif //UFOCR_COLORBALANCE_HPP
