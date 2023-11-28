#include "Image_blur.h"


using namespace cv;
void Image_blur(InputArray src, OutputArray dst, double redius,double reg) {
	/*
	* edius 导向滤波半径
    * reg 导向滤波正则化参数
	*/
	
	Mat _src = src.getMat();
	dst.create(_src.size(), _src.type());
	Mat _dst = dst.getMat();
	std::vector<Mat> p, q;
	split(_src, p);
	for (int i = 0; i < _src.channels(); i++) {
		GuideFilter(p[i], p[i], redius, reg);
		q.push_back(p[i]);
	}
	merge(q, _dst);
}

