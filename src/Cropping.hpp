
#ifndef UFOCR_CROPPING_HPP
#define UFOCR_CROPPING_HPP

#include "opencv2/core.hpp"

namespace prl
{
    //TODO: Research question about value for longSide
    extern "C" std::vector<cv::Point> getContour(const cv::Mat& src, size_t longSide = 1024);
}

#endif //UFOCR_CROPPING_HPP
