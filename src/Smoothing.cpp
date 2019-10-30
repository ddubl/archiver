
#include "Smoothing.hpp"

#include "opencv2/imgproc.hpp"

void prl::smooth(const cv::Mat& src, cv::Mat& dst, SmoothMethod method /*= SmoothMethod::Bilateral*/)
{
    switch (method)
    {
        case SmoothMethod::Median:
            cv::medianBlur(src, dst, 5);
            break;
        case SmoothMethod::Gaussian:
            cv::GaussianBlur(src, dst, cv::Size(11, 11), 10, 30);
            break;
        case SmoothMethod::Bilateral:
            cv::bilateralFilter(src, dst, 5, 100, 100);
            break;
        default:
            //TODO: Implement new algorithms
            throw std::runtime_error("Smooth algorithm is not implemented yet");
    }
}