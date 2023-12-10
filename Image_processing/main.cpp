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
#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

int main() {
    cv::Mat src = cv::imread("D:\\git\\Image\\test_image\\ff.PNG");
    cv::Mat dst;
    hsl** hsl;
    hsl = RGB2HSL(src);
    

    //channel_hsl(hsl, 50, RED, src.rows, src.cols);
    //HUE(hsl, 50, src.rows, src.cols);

    HSL2RGB(src, dst, hsl);
    imshow("1", src);
    imshow("2", dst);
    cv::waitKey();
}
*/

