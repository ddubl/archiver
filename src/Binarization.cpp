#include "Binarization.hpp"
#include "SauvolaBinarization.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/ximgproc.hpp"

void prl::binarize(const cv::Mat& src, cv::Mat& dst,
                   BinarizationMethod method /*= BinarizationMethod::Otsu*/)
{
    switch (method)
    {
        case BinarizationMethod::Otsu:
            cv::threshold(src, dst, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
            break;
        case BinarizationMethod::Adaptive:
            cv::adaptiveThreshold(src, dst, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 13, 1);
            break;
        case BinarizationMethod::Niblack:
            //TODO: rewrite constants in Niblack binarization
            cv::ximgproc::niBlackThreshold(src, dst, 255, cv::THRESH_BINARY, 2 * (11) + 1, ((8.0) - 10.0) / 10.0);
            break;
        case BinarizationMethod::Sauvola: {
            cv::Mat temp = src.clone();
            prl::sauvolaBinarization(temp, dst);
        }
        default:
            throw std::runtime_error("Binarization algorithm not implemented!");
    }
}
