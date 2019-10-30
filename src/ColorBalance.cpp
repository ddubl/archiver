
#include "ColorBalance.hpp"
#include "opencv2/xphoto.hpp"
#include "opencv2/photo.hpp"

void prl::whiteBalance(const cv::Mat& src, cv::Mat& dst, ColorBalance method/* = ColorBalance::Simple*/)
{
    switch (method)
    {
        case ColorBalance::Simple:
            cv::xphoto::createSimpleWB()->balanceWhite(src, dst);
            break;
        case ColorBalance::Grayworld:
            cv::xphoto::createGrayworldWB()->balanceWhite(src, dst);
            break;
        default:
            throw std::runtime_error("Balance algorithm is not implemented yet!");
    }

}