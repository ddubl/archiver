
#ifndef PRLIB_DEBLUR_HPP
#define PRLIB_DEBLUR_HPP

#include "opencv2/core.hpp"

namespace prl
{
    enum class DeblurMethod {Simple};

    //TODO: Maybe we should use other algorithm by default
extern "C" void deblur(const cv::Mat& src, cv::Mat& dst,
                DeblurMethod method = DeblurMethod::Simple);
}

#endif //PRLIB_DEBLUR_HPP
