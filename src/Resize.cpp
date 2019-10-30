#include "Resize.hpp"
#include "opencv2/imgproc.hpp"

void prl::resize(const cv::Mat& src, cv::Mat& dst, int scaleX, int scaleY, int nProcessedImageSize)
{
    cv::Mat imageToProc;

    //! Store source image size
    cv::Size sourceImageSize(src.size());

    cv::Size newImageSize;

    if (scaleX > 0 && scaleY > 0)
    {
        newImageSize = cv::Size(
                static_cast<int>(src.cols * scaleX),
                static_cast<int>(src.rows * scaleY)
        );

        cv::resize(src, imageToProc, newImageSize, 0, 0, cv::INTER_AREA);
    }
    else
    {
        int longSide = std::max(src.cols, src.rows);

        int scaleFactorX = 1;
        int scaleFactorY = 1;

        imageToProc = src.clone();

        while (longSide > nProcessedImageSize)
        {
            cv::pyrDown(imageToProc, imageToProc);

            longSide = std::max(imageToProc.cols, imageToProc.rows);
            scaleFactorX *= 2;
            scaleFactorY *= 2;
        }

        newImageSize = cv::Size(src.cols / scaleFactorX, src.rows / scaleFactorY);
    }
}