
#include "Rotate.hpp"

#include "opencv2/imgproc.hpp"

namespace prl
{
void rotate(const cv::Mat& input, cv::Mat& output, const double angle)
{
    if (angle == 90)
    {
        // rotate on 90
        cv::transpose(input, output);
        cv::flip(output, output, 1);
        return;
    }
    else if (angle == 180)
    {
        // rotate on 180
        cv::flip(input, output, -1);
        return;
    }
    else if (angle == 270)
    {
        // rotate on 270
        cv::transpose(input, output);
        cv::flip(output, output, 0);
        return;
    }
    else
    {
        output = input.clone();
        cv::bitwise_not(input, input);

        int len = std::max(output.cols, output.rows);
        cv::Point2f pt(static_cast<float>(len / 2.0), static_cast<float>(len / 2.0));
        cv::Mat r = cv::getRotationMatrix2D(pt, angle, 1.0);

        cv::warpAffine(input, output, r, cv::Size(len, len));

        cv::bitwise_not(input, input);
        cv::bitwise_not(output, output);
    }
}
}