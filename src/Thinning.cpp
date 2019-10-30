
#include "Thinning.hpp"

#include "opencv2/opencv.hpp"
#include "opencv2/ximgproc.hpp"

void prl::thinning(const cv::Mat& src, cv::Mat& dst, Thinning method /*= Thinning::ZhangSuen*/)
{
    switch (method)
    {
        case Thinning::ZhangSuen:
            cv::ximgproc::thinning(src, dst, cv::ximgproc::THINNING_ZHANGSUEN);
            break;
        case Thinning::GuoHall:
            cv::ximgproc::thinning(src, dst, cv::ximgproc::THINNING_GUOHALL);
            break;
    }
}

