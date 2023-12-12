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

#include "Image_blur.h"
#include "Image_sharpening.h"
#include "Image_HSL.h"
#include "Image_whitebalance.h"

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

int main() {
    cv::Mat src = cv::imread("D:\\git\\Image\\test_image\\people.png");
    cv::Mat dst;

    whilepatch(src, dst, 100);
    imshow("1", src);
    imshow("2", dst);
    cv::waitKey();
}


*/