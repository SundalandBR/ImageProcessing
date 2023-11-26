#include "Image_exposure.h"

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))


void Image_exposure(cv::InputArray _src, cv::OutputArray _dst, double strength) {
	cv::Mat src = _src.getMat();
	_dst.create(src.size(), src.type());
	cv::Mat dst = _dst.getMat();
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			dst.at<uchar>(i, j) = (uchar)min(255, max(0,dst.at<uchar>(i,j)*pow(2,strength)));
		}
	}
}