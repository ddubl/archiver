
#ifndef PRLIB_ROTATE_HPP
#define PRLIB_ROTATE_HPP

#include "opencv2/core.hpp"

namespace prl
{
extern "C" void rotate(const cv::Mat& input, cv::Mat& output, const double angle);
}

#endif //PRLIB_ROTATE_HPP
