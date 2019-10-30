
#ifndef PRLIB_FORMATCONVERT_HPP
#define PRLIB_FORMATCONVERT_HPP

#include <opencv2/core.hpp>
#include <leptonica/alltypes.h>

namespace prl
{
PIX* ImgOpenCvToLepton(const cv::Mat src);
cv::Mat ImgLeptonToOpenCV(const PIX* src);
}

#endif //PRLIB_FORMATCONVERT_HPP
