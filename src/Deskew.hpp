
#ifndef UFOCR_DESKEW_HPP
#define UFOCR_DESKEW_HPP

#include "opencv2/core.hpp"

namespace prl
{
    //TODO: Add manual deskew and auto-deskew
extern "C" bool deskew(cv::Mat& inputImage, cv::Mat& deskewedImage);
}

#endif //UFOCR_DESKEW_HPP
