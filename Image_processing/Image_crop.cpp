#include "Image_crop.h"


extern cv::Mat Input;


Image_crop::Image_crop(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

    ui.setupUi(this);


    cv::Mat tmat;
    Input.copyTo(tmat);
    cv::cvtColor(tmat, tmat, cv::COLOR_BGR2RGB);
    QImage Qinput = QImage((const unsigned char*)(tmat.data), tmat.cols, tmat.rows, tmat.step, QImage::Format_RGB888);
    ui.crop_label->resize(tmat.size().width, tmat.size().height);
    pix = QPixmap::fromImage(Qinput.scaled(ui.crop_label->size(), Qt::KeepAspectRatio));

    labelX_ = ui.crop_label->x();
    labelY_ = ui.crop_label->y();
    labelWidth_ = ui.crop_label->width();
    labelHeigth_ = ui.crop_label->height();

    centerRect_.setX(20 + labelX_);
    centerRect_.setY(30 + labelX_);
    centerRect_.setWidth(50);
    centerRect_.setHeight(50);


    //区域内外等颜色值
    outsideColor_ = QColor(200, 200, 200, 150);
    //outsideColor_ = QColor(255, 0, 0, 255);
    insideColor_ = QColor(200, 200, 200, 0);
    dashColor_ = QColor(30, 162, 255, 255);

    //几个可以调整的点
    labelLeftBottom_ = new QLabel(this);
    labelLeftBottom_->setObjectName(QString::fromUtf8("labelLeftBottom"));
    labelLeftBottom_->setFixedSize(sDragDotWidth_, sDragDotWidth_);
    labelLeftBottom_->setCursor(QCursor(Qt::SizeBDiagCursor));
    labelLeftBottom_->setStyleSheet(QString::fromUtf8("background-color: rgb(30,162,255);"));
    labelRightBottom_ = new QLabel(this);
    labelRightBottom_->setObjectName(QString::fromUtf8("labelRightBottom"));
    labelRightBottom_->setFixedSize(sDragDotWidth_, sDragDotWidth_);
    labelRightBottom_->setCursor(QCursor(Qt::SizeFDiagCursor));
    labelRightBottom_->setStyleSheet(QString::fromUtf8("background-color: rgb(30,162,255);"));
    labelLeftTop_ = new QLabel(this);
    labelLeftTop_->setObjectName(QString::fromUtf8("labelLeftTop"));
    labelLeftTop_->setFixedSize(sDragDotWidth_, sDragDotWidth_);
    labelLeftTop_->setCursor(QCursor(Qt::SizeFDiagCursor));
    labelLeftTop_->setStyleSheet(QString::fromUtf8("background-color: rgb(30,162,255);"));
    labelRightTop_ = new QLabel(this);
    labelRightTop_->setObjectName(QString::fromUtf8("labelRightTop"));
    labelRightTop_->setFixedSize(sDragDotWidth_, sDragDotWidth_);
    labelRightTop_->setCursor(QCursor(Qt::SizeBDiagCursor));
    labelRightTop_->setStyleSheet(QString::fromUtf8("background-color: rgb(30,162,255);"));

    labelLeftBottom_->installEventFilter(this);
    labelRightBottom_->installEventFilter(this);
    labelLeftTop_->installEventFilter(this);
    labelRightTop_->installEventFilter(this);

    this->update();


}



Image_crop::~Image_crop()
{}


void Image_crop::setFixCenterRectRatio(float ratio) {
    /*
    * 按当前框大小 重新更改长 / 宽比例
    * 如果ratio > 1 固定长为图片的长度 修改宽度
    * 如果ratio < 1 固定宽为图片的宽度 修改长度
    * x y 不变
    */
    if (ratio >= 1) {

    }




}


void Image_crop::setRects() {
    leftRect_.setRect(labelX_, labelY_, centerRect_.x() - labelX_, labelHeigth_);
    topRect_.setRect(centerRect_.x(), labelY_, centerRect_.width() + sLineWidth_, centerRect_.y() - labelY_);
    rightRect_.setRect(centerRect_.width() + centerRect_.x() + sLineWidth_, labelY_, labelX_ + labelWidth_ - centerRect_.width() - centerRect_.x(), labelHeigth_);
    bottomRect_.setRect(centerRect_.x(), centerRect_.height() + centerRect_.y() + sLineWidth_, centerRect_.width() + sLineWidth_, labelY_ + labelHeigth_ - centerRect_.height() - centerRect_.y() - sLineWidth_);
}

//update() 调用
void Image_crop::paintEvent(QPaintEvent* event)
{
    setRects();

    QPainter painter(this);

    painter.drawPixmap(labelX_, labelY_, labelWidth_, labelHeigth_, pix);

    //绘制区域
    painter.fillRect(leftRect_, outsideColor_);
    painter.fillRect(topRect_, outsideColor_);
    painter.fillRect(rightRect_, outsideColor_);
    painter.fillRect(bottomRect_, outsideColor_);

    //绘制中间区域和边框虚线

    dashPen_.setBrush(QBrush(dashColor_));
    painter.setPen(dashPen_);
    painter.fillRect(centerRect_, insideColor_);
    painter.drawRect(centerRect_);

    //move zoomdot
    labelLeftBottom_->move(centerRect_.x() - sDragDotWidth_ / 2 + sDragDotOffset_, centerRect_.y() + centerRect_.height() - sDragDotWidth_ / 2 - sDragDotOffset_);
    labelRightBottom_->move(centerRect_.x() + centerRect_.width() - sDragDotWidth_ / 2 - sDragDotOffset_, centerRect_.y() + centerRect_.height() - sDragDotWidth_ / 2 - sDragDotOffset_);
    labelLeftTop_->move(centerRect_.x() - sDragDotWidth_ / 2 + sDragDotOffset_, centerRect_.y() - sDragDotWidth_ / 2 + sDragDotOffset_);
    labelRightTop_->move(centerRect_.x() + centerRect_.width() - sDragDotWidth_ / 2 - sDragDotOffset_, centerRect_.y() - sDragDotWidth_ / 2 + sDragDotOffset_);
}


void Image_crop::mousePressEvent(QMouseEvent* e) {
    if (centerRect_.contains(e->pos(), true)) {
        start_pos_ = e->pos();
        center_move_location_ = centerRect_;
        press_ = true;
    }
}

void Image_crop::mouseMoveEvent(QMouseEvent* e) {
    if (press_) {
        QPoint move_ = e->pos() - start_pos_;
        /*
        * 限制裁剪框在label内
        * label_x <= end_pos_.x <= label_x + width - centerRect.width
        * label_y <= end_pos_.y <= label_y + heigth - centerRect.heigth
        *
        * 是否要限制在图片内？
        *
        */
        centerRect_.setRect(std::min(std::max(labelX_, move_.x() + center_move_location_.x()), labelX_ + labelWidth_ - center_move_location_.width()),
            std::min(std::max(labelY_, move_.y() + center_move_location_.y()), labelY_ + labelHeigth_ - center_move_location_.height()),
            centerRect_.width(), centerRect_.height());
        this->update();
        press_ = true;
    }
}

bool Image_crop::eventFilter(QObject* obj, QEvent* e) {

    /*
    if (obj == labelLeftBottom_
        || obj == labelRightBottom_
        || obj == labelLeftTop_
        || obj == labelRightTop_) {

        if (e->type() & QEvent::MouseButtonPress) {
            QMouseEvent *event = (QMouseEvent*)e;
            /*
            * LeftButton 表示鼠标左键按下
            * NoButton 表示鼠标在移动

            if (event->buttons() & Qt::LeftButton) {
                button_press = true;
                global_start_pos_ = event->globalPos();
                center_move_location_ = centerRect_;
                return true;
            }
        }
        else if (e->type() & QEvent::MouseMove) {
            QMouseEvent* event = (QMouseEvent*)e;
            if ( button_press && event->buttons() & Qt::LeftButton){
                if (obj == labelLeftBottom_) {
                    if (fix_crop) {

                    }
                    else {

                    }
                }
            }
        }
        /*
        * 鼠标松开时候

        else if (e->type() & QEvent::MouseButtonRelease) {
            button_press = false;
            return true;
        }

    }*/

    return false;
}