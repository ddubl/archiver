#include "Deblur.hpp"
#include "opencv2/imgproc.hpp"

void basicDeblur(const cv::Mat& src, cv::Mat& dst)
{
    std::vector<cv::Mat> channels;
    cv::split(src, channels);

    for (auto& channel : channels)
    {
        cv::Mat channelfloat;
        channel.convertTo(channelfloat, CV_32F);
        cv::GaussianBlur(
                channelfloat, channel,
                cv::Size(11, 11),
                10, 30);
        cv::addWeighted(
                channelfloat, 2.0 * 0.75,
                channel, 2.0 * 0.75 - 2.0,
                0.0,
                channel);

        // convert back to 8bits gray scale
        channel.convertTo(channel, CV_8U);
    }

    cv::merge(channels, dst);
}


void prl::deblur(const cv::Mat& src, cv::Mat& dst,
                 DeblurMethod method /*= DeblurMethod::Simple*/)
{
    switch(method)
    {
        case DeblurMethod::Simple:
            basicDeblur(src, dst);
            break;
        default:
            //TODO: implement algorithms
            throw std::runtime_error("Deblur algorithm not implemented yet");
    }
}