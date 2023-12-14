#include "Image_whitebalance.h"

void whilepatch(InputArray src,OutputArray dst,int percent) {
	double per = percent / 100.f;
	Mat _src = src.getMat();
	dst.create(src.size(), src.type());
	Mat _dst = dst.getMat();
	split(_src, p);
	vector<double> max_pixel;
	double max_val;
	//BGR
	for (int i = 0; i < _src.channels(); i++) {
		//minMaxIdx(p[i], NULL, &max_val);
		max_val = percentileValue(p[i], 85);
	}

	for (int i = 0; i < _src.rows; i++) {
		for (int j = 0; j < _src.cols; j++) {
			Vec3b point = _src.at<Vec3b>(i, j);
			_dst.at<Vec3b>(i, j)[0] = saturate_cast<uchar>(per * (max_pixel[0] - 1.f) * point[0] + point[0]);
			_dst.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(per * (max_pixel[1] - 1.f) * point[1] + point[1]);
			_dst.at<Vec3b>(i, j)[2] = saturate_cast<uchar>(per * (max_pixel[2] - 1.f) * point[2] + point[2]);
		}
	}
}

double percentileValue(cv::Mat src,int percent) {

	vector<double>mat_data;
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			mat_data.push_back(src.at<uchar>(i, j));
		}
	}

	sort(mat_data.begin(), mat_data.end());

	int index = mat_data.size() * percent / 100.f;
	//index = (index < 0 ? index : 0) > 255 ? 255 : (index < 0 ? index : 0);
	return mat_data[index];

}