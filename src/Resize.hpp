
#ifndef PRLIB_RESIZE_HPP
#define PRLIB_RESIZE_HPP

#include "opencv2/core.hpp"

namespace prl
{
extern "C" void resize(const cv::Mat& src, cv::Mat& dst, int scaleX, int scaleY, int nProcessedImageSize);
}

#endif //PRLIB_RESIZE_HPP
