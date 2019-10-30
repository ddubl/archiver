
#include "Denoising.hpp"

#include "opencv2/xphoto.hpp"
#include "opencv2/photo.hpp"

void prl::denoise(const cv::Mat& src, cv::Mat& dst)
{
    //Too slow
    //cv::xphoto::dctDenoising(src, dst, 15.0);

    cv::fastNlMeansDenoisingColored(src, dst, 5.5);
}