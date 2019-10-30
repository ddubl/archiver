
#ifndef UFOCR_THINNING_HPP
#define UFOCR_THINNING_HPP

#include "opencv2/core.hpp"

namespace prl
{
enum class Thinning
{
    ZhangSuen, GuoHall
};

extern "C" void thinning(const cv::Mat& src, cv::Mat& dst, Thinning method = Thinning::ZhangSuen);
}

#endif //UFOCR_THINNING_HPP
