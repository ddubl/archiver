
#ifndef UFOCR_BLURDETECTION_HPP
#define UFOCR_BLURDETECTION_HPP

#include <opencv2/core.hpp>

namespace prl
{

enum class BlurDetectionAlgo
{
    LAPM, LAPV, TENG, GLVN
};

extern "C" bool isBlurred(const cv::Mat& src, BlurDetectionAlgo algo);

}
#endif //UFOCR_BLURDETECTION_HPP
