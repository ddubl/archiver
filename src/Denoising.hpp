
#ifndef UFOCR_DENOISING_HPP
#define UFOCR_DENOISING_HPP

#include "opencv2/core.hpp"

namespace prl
{
extern "C" void denoise(const cv::Mat& src, cv::Mat& dst);
}


#endif //UFOCR_DENOISING_HPP
