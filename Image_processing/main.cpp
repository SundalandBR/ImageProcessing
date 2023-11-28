#include "Image_processing.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Image_processing w;
    w.show();
    return a.exec();
}


/*
#include "Image_Histogram.h"
#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

int main() {
	cv::Mat src = cv::imread("D:\\git\\Image\\test_image\\forest.png");
    cv::Mat dst;
    Imgae_Histogram(src, dst);
    cv::imshow("1", dst);
    cv::waitKey();
}

*/
