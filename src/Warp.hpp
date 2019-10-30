
#ifndef UFOCR_WARP_HPP
#define UFOCR_WARP_HPP

#include "opencv2/core.hpp"

namespace prl
{
extern "C" void warpCrop(const cv::Mat& sourceImg,
              cv::Mat& destImg,
              const int x0, const int y0,
              const int x1, const int y1,
              const int x2, const int y2,
              const int x3, const int y3,
              const int borderMode = cv::BORDER_CONSTANT,
              const cv::Scalar& borderValue = cv::Scalar());
}

#endif //UFOCR_WARP_HPP
