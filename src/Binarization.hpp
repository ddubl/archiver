
#ifndef UFOCR_BINARIZATION_HPP
#define UFOCR_BINARIZATION_HPP

#include <opencv2/core.hpp>

namespace prl
{
enum class BinarizationMethod
{
    Otsu, /*!< Otsu global binarization */
    Adaptive,
    OtsuMA,
    Niblack, /*!< Niblack adaptive binarization */
    Sauvola, /*!< Sauvola adaptive binarization */
    MaxEntropy, /*!< Maximum entropy global binarization */
    Bradley, /*!< Bradley adaptive binarization */
    Iterative, /*!< Global iterative binarization */
    Bernsen, /*!< Bernsen adaptive binarization */
    Gatos /*!< Ga'tos adaptive binarization */
};

//TODO: Rewrite all binarization algorithms. By default should use OtsuThreshold.
extern "C" void binarize(const cv::Mat& src, cv::Mat& dst, BinarizationMethod method = BinarizationMethod::Otsu);
}

#endif //UFOCR_BINARIZATION_HPP
