
#include "Image_contras.h"


#define CLIP_RANGE(value, min, max)  ( (value) > (max) ? (max) : (((value) < (min)) ? (min) : (value)) )
#define COLOR_RANGE(value)  CLIP_RANGE(value, 0, 255)


void Image_contras(cv::InputArray Input, cv::OutputArray Output, double beta,double alpha) {
	/*
	* beta [-1,1]
	* alpha [-1,1]
	*/
	cv::Mat src = Input.getMat();
	Output.create(src.size(), src.type());
	cv::Mat dst = Output.getMat();
	/*
	y = [x - 127.5 * (1 - B)] * k + 127.5 * (1 + B);
	x is the input pixel value
	y is the output pixel value
	B is brightness, value range is [-1,1]
	k is used to adjust contrast
	k = tan( (45 + 44 * c) / 180 * PI );
	c is contrast, value range is [-1,1]
	*/
	cv::Mat_<uchar>::iterator src_begin = src.begin<uchar>();
	cv::Mat_<uchar>::iterator src_end = src.end<uchar>();

	uchar MAX_PIXEL = 0;
	uchar MIN_PIXEL = UCHAR_MAX;

	for (; src_begin != src_end; src_begin++) {
		int t = (*src_begin);
		MAX_PIXEL = MAX_PIXEL > t ? MAX_PIXEL : t;
		MIN_PIXEL = MIN_PIXEL < t ? MIN_PIXEL : t;
	}

	double MID_PIXEL = (MAX_PIXEL + MIN_PIXEL) / 2.0;

	double k = tan((45 + 44 * alpha) / 180 * CV_PI);
	cv::Mat lookuptable(1, 256, CV_8U);
	for (int i = 0; i < 256; i++) {
		//lookuptable.at<uchar>(i) = round(COLOR_RANGE((i - MID_PIXEL * (1 - beta)) * k + MID_PIXEL * (1 + beta)));
		lookuptable.at<uchar>(i) = COLOR_RANGE((i / 255.0) * (round(COLOR_RANGE((i - MID_PIXEL * (1 - beta)) * k + MID_PIXEL * (1 + beta))) - i) + i);
	}
	cv::LUT(src, lookuptable, dst);

}



/*
* 
*  i = new_i
*  i = i / 255 * (new_i - i) + i
* 
*/

void Image_contras_gamma(cv::InputArray _src, cv::OutputArray _dst, double gamma) {
	/*
	* gamma [-1,1]
	*/
	cv::Mat lookuptable(1, 256, CV_8U);
	for (int i = 0; i < 256; i++) {
		lookuptable.at<uchar>(i) = cv::saturate_cast<uchar>(pow(i / 255.0, gamma) * 255.0);
	}
	cv::LUT(_src, lookuptable, _dst);
}

void Image_contras_bright(cv::InputArray Input, cv::OutputArray Output, double beta, double alpha) {

	std::vector<cv::Mat> p, q;
	cv::split(Input, p);

	for (int i = 0; i < Input.channels(); i++) {

		Image_contras(p[i], p[i], beta, alpha);
		q.push_back(p[i]);
	}
	cv::merge(q, Output);
}