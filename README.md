

[用OpenCV实现Photoshop算法(三): 曲线调整_opencv绘制曲线-CSDN博客](https://blog.csdn.net/c80486/article/details/52499919)

构图（裁剪) [Qt中截图功能的实现 - mengfanrong - 博客园 (cnblogs.com)](https://www.cnblogs.com/mengfanrong/p/5136797.html)

旋转 

文字



亮度：

光感 双边滤波 根据光的强弱变

亮度 Gamma校正 一起变亮

曝光 直方图修正  均值法AE、N段统计法

[自动曝光_自动曝光算法-CSDN博客](https://blog.csdn.net/htjacky/article/details/78588953)

对比度 暗的更暗亮的更亮

直方图均衡化

[图像编辑之对比度调整 亮度对比度的算法公式 - jack船长大哥 - 博客园 (cnblogs.com)](https://www.cnblogs.com/skiwnchiwns/p/10130833.html)



颜色：

色温

色调

曲线调整/曲线调色

饱和度调整，曲线调色

HSL [[c++\]opencv实现RGB和HSI的相互转换_c++ hsi转rgb-CSDN博客](https://blog.csdn.net/OTZ_2333/article/details/110222799)



锐化

平滑 导向滤波 



| BORDER_CONSTANT Python: cv.BORDER_CONSTANT       | `iiiiii|abcdefgh|iiiiiii` with some specified `i` 指定像素值补充边界 |
| ------------------------------------------------ | ------------------------------------------------------------ |
| BORDER_REPLICATE Python: cv.BORDER_REPLICATE     | `aaaaaa|abcdefgh|hhhhhhh`复制边界像素填充                    |
| BORDER_REFLECT Python: cv.BORDER_REFLECT         | `fedcba|abcdefgh|hgfedcb`选定一个像素为轴，反射图中像素      |
| BORDER_WRAP Python: cv.BORDER_WRAP               | `cdefgh|abcdefgh|abcdefg`用另一边的像素补充                  |
| BORDER_REFLECT_101 Python: cv.BORDER_REFLECT_101 | `gfedcb|abcdefgh|gfedcba`以边界为轴，反射图中像素            |
| BORDER_TRANSPARENT Python: cv.BORDER_TRANSPARENT | `uvwxyz|abcdefgh|ijklmno`不做边界处理，以边界像素本身作为边界像素 |
| BORDER_REFLECT101 Python: cv.BORDER_REFLECT101   | same as BORDER_REFLECT_101                                   |
| BORDER_DEFAULT Python: cv.BORDER_DEFAULT         | same as BORDER_REFLECT_101                                   |
| BORDER_ISOLATED Python: cv.BORDER_ISOLATED       | do not look outside of ROI 填充0                             |

[【精选】VS2019+opencv4.5.1+Qt5.12.10配置+Qt设计图片处理GUIDemo实操 全记录_111今天学习了吗的博客-CSDN博客](https://blog.csdn.net/weixin_43470995/article/details/112862159)









请注意，由于历史原因，由bottom()和right()函数返回的值偏离了矩形真正的右下角:right()函数返回left() + width() - 1, bottom()函数返回top() + height() - 1。由bottomRight()函数返回的point也是同样的情况。另外，topRight()函数和bottomLeft()函数的x坐标和y坐标与右真边和底边的偏差是相同的。

我们建议使用x() + width()和y() + height()来找到真正的右下角，避免使用right()和bottom()。另一种解决方案是使用QRectF: QRectF类使用浮点精度在坐标上定义平面中的矩形，QRectF::right()和QRectF::bottom()函数确实返回右坐标和底坐标。



```c++
#ifndef SELECTRECTWIDGET_H
#define SELECTRECTWIDGET_H


#include <QWidget>
#include <QPen>
#include <QLabel>
#include <functional>


namespace Ui {
class SelectRectWidget;
}
class SelectRectWidget : public QWidget
{
    Q_OBJECT


public:
    explicit SelectRectWidget(QWidget *parent = nullptr);
    ~SelectRectWidget();


    /**
     * @brief setFixCenterRectRatio 设置选择框为固定比例
     * @param ratio 比例值width:height，比如16:9
     */
    void setFixCenterRectRatio(float ratio);


    //中间镂空区域的Rect
    QRect centerRect() const;


    /**
     * @brief setSelectRectChange 设置选择框变化时回调函数
     * @param selectRectChange
     */
    void setSelectRectChange(const std::function<void (QRect rect)> &selectRectChange);


protected:
    virtual void paintEvent(QPaintEvent *event) override;
    bool eventFilter(QObject *, QEvent *) override;


private:
    //根据centerRect_设置各种Rect
    void setRects();
    //检测centerRect区域值是否有效
    void checkCenterRect();


private:
    Ui::SelectRectWidget *ui;
    QRect leftRect_;//中间镂空区域的左侧蒙层Rect
    QRect topRect_;//中间镂空区域的顶部蒙层Rect
    QRect rightRect_;//中间镂空区域的右侧蒙层Rect
    QRect bottomRect_;//中间镂空区域的底部蒙层Rect
    QRect centerRect_;//中间镂空区域的Rect
    QRect preCenterRect_;//记录上一次中间镂空区域的Rect，避免中间区域相同时重复绘制
    QColor outsideColor_;//外部蒙层的颜色值
    QColor insideColor_;//内部镂空区域的颜色值
    QColor dashColor_;//中间镂空区域的虚线边框的颜色值


    QPen dashPen_;//中间镂空区域的虚线边框的Pen（可以设置虚线长度和间隔长度等）
    QVector<qreal> dashes_;//dashPen_的虚线长度和间隔长度设置


    QLabel * labelLeftBottom_ = nullptr;//可以触发缩放，镂空区域虚线边框左下部的顶点
    QLabel * labelRightBottom_ = nullptr;//可以触发缩放，镂空区域虚线边框右下部的顶点
    QLabel * labelLeftTop_ = nullptr;//可以触发缩放，镂空区域虚线边框左上部的顶点
    QLabel * labelRightTop_ = nullptr;//可以触发缩放，镂空区域虚线边框右上部的顶点
    QRect    dragMoveLocation_;//保存centerRect_移动时的初始值
    QPoint   dragZoomPos_;//四个顶点被QMouseEvent press时的初始值
    bool     dragZoomRunning_;//四个顶点被QMouseEvent press时的
    QRect    dragZoomLocation_;//四个顶点被QMouseEvent press时，保存centerRect_的初始值
    bool     press_ = false;//鼠标press centerRect_区域时为true
    QPoint   startPos_;//保存鼠标press时的QMouseEvent初始值
    float    fixCenterRectRatio_;//选择框固定比例值缩放，不设置该值时非固定比例缩放
    std::function<void (QRect rect)> selectRectChange_;//选择框变化时回调函数


    static int  sDragDotWidth_;      //选择框边线上几个可以放大缩小的点大小
    static int  sCenterRectMinWidth_;//选择框的最小宽度和高度，防止选择框边线重叠
    static int  sLineWidth_;//选择框边线宽度
    static int  sDragDotOffset_;//四个顶点的offset值


protected:
    virtual void mousePressEvent(QMouseEvent *e) override;
    virtual void mouseMoveEvent(QMouseEvent *e) override;
    virtual void mouseReleaseEvent(QMouseEvent *e) override;
};


#endif // SELECTRECTWIDGET_H



```

```c++
#include "selectrectwidget.h"
#include "ui_selectrectwidget.h"


#include <QPainter>
#include <QVector>
#include <QMouseEvent>


#include "qdebug.h"


int  SelectRectWidget::sDragDotWidth_ = 6;
int  SelectRectWidget::sDragDotOffset_ = 2;
int  SelectRectWidget::sCenterRectMinWidth_ = 6;
int  SelectRectWidget::sLineWidth_ = 1;


void SelectRectWidget::setRects()
{
    leftRect_.setRect(0,0,centerRect_.x(),height());
    topRect_.setRect(centerRect_.x(),0,centerRect_.width()+sLineWidth_,centerRect_.y());
    rightRect_.setRect(centerRect_.width()+centerRect_.x()+sLineWidth_,0,width()-centerRect_.width()-centerRect_.x(),height());
    bottomRect_.setRect(centerRect_.x(),centerRect_.height()+centerRect_.y()+sLineWidth_,centerRect_.width()+sLineWidth_,height()-centerRect_.height()-centerRect_.y());
}


SelectRectWidget::SelectRectWidget(QWidget *parent) :
    QWidget(parent),fixCenterRectRatio_(-1.0f),
    ui(new Ui::SelectRectWidget)
{
    ui->setupUi(this);
    //绘制区域
    setRects();
    centerRect_.setWidth(0);


    //区域内外等颜色值
    outsideColor_ = QColor(200,200,200,150);
    insideColor_ = QColor(200,200,200,0);
    dashColor_ = QColor(30,162,255,255);


    //虚线的样式
    dashPen_.setBrush(QBrush(dashColor_ , Qt::SolidPattern));
    qreal space = 2;
    dashes_ << 3 << space << 3 <<space;
    dashPen_.setDashPattern(dashes_);
    dashPen_.setWidth(sLineWidth_);


    //几个可以调整的点
    labelLeftBottom_ = new QLabel(this);
    labelLeftBottom_->setObjectName(QString::fromUtf8("labelLeftBottom"));
    labelLeftBottom_->setFixedSize(sDragDotWidth_,sDragDotWidth_);
    labelLeftBottom_->setCursor(QCursor(Qt::SizeBDiagCursor));
    labelLeftBottom_->setStyleSheet(QString::fromUtf8("background-color: rgb(30,162,255);"));
    labelRightBottom_ = new QLabel(this);
    labelRightBottom_->setObjectName(QString::fromUtf8("labelRightBottom"));
    labelRightBottom_->setFixedSize(sDragDotWidth_,sDragDotWidth_);
    labelRightBottom_->setCursor(QCursor(Qt::SizeFDiagCursor));
    labelRightBottom_->setStyleSheet(QString::fromUtf8("background-color: rgb(30,162,255);"));
    labelLeftTop_ = new QLabel(this);
    labelLeftTop_->setObjectName(QString::fromUtf8("labelLeftTop"));
    labelLeftTop_->setFixedSize(sDragDotWidth_,sDragDotWidth_);
    labelLeftTop_->setCursor(QCursor(Qt::SizeFDiagCursor));
    labelLeftTop_->setStyleSheet(QString::fromUtf8("background-color: rgb(30,162,255);"));
    labelRightTop_ = new QLabel(this);
    labelRightTop_->setObjectName(QString::fromUtf8("labelRightTop"));
    labelRightTop_->setFixedSize(sDragDotWidth_,sDragDotWidth_);
    labelRightTop_->setCursor(QCursor(Qt::SizeBDiagCursor));
    labelRightTop_->setStyleSheet(QString::fromUtf8("background-color: rgb(30,162,255);"));


    //事件监听
    labelLeftBottom_->installEventFilter(this);
    labelRightBottom_->installEventFilter(this);
    labelLeftTop_->installEventFilter(this);
    labelRightTop_->installEventFilter(this);


}


SelectRectWidget::~SelectRectWidget()
{
    labelLeftBottom_->removeEventFilter(this);
    labelRightBottom_->removeEventFilter(this);
    labelLeftTop_->removeEventFilter(this);
    labelRightTop_->removeEventFilter(this);
    delete ui;
}


void SelectRectWidget::checkCenterRect()
{
    centerRect_ = centerRect_.intersected(this->rect());
    if(centerRect_.bottom() >= this->rect().bottom()){
        centerRect_.setBottom(this->rect().bottom());
    }
    if(centerRect_.right() >= this->rect().right()){
        centerRect_.setRight(this->rect().right()-sLineWidth_);
    }
}


QRect SelectRectWidget::centerRect() const
{
    return centerRect_;
}


void SelectRectWidget::setSelectRectChange(const std::function<void (QRect rect)> &selectRectChange)
{
    selectRectChange_ = selectRectChange;
}


void SelectRectWidget::setFixCenterRectRatio(float ratio)
{
    fixCenterRectRatio_ = ratio;


    float widthBHeight = this->width()*1.0f/this->height();
    int tmpWidth = 0;
    int tmpHeight = 0;
    if(widthBHeight > ratio){
        tmpHeight = this->height();
        tmpWidth = ratio * tmpHeight;
    }else{
        tmpWidth = this->width();
        tmpHeight = tmpWidth/ratio;
    }


    //设置选择框值
    centerRect_.setRect((this->width() - tmpWidth)/2 , (this->height() - tmpHeight)/2 , tmpWidth , tmpHeight);
    this->update();
}


void SelectRectWidget::mousePressEvent(QMouseEvent *e)
{


    if(centerRect_.contains(e->pos(),true)){
        press_ = true;
        startPos_ = e->pos();
        dragMoveLocation_ = centerRect_;
    }
}


void SelectRectWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (press_){
        QPoint movePos = e->pos()-startPos_;
        centerRect_.setRect(
            std::max(std::min(dragMoveLocation_.x()+movePos.x(), rect().width()-dragMoveLocation_.width()-sLineWidth_) , 0) , 				std::max(std::min(dragMoveLocation_.y()+movePos.y(), rect().height()-dragMoveLocation_.height()-sLineWidth_) , 0) ,
            centerRect_.width() , 
            centerRect_.height() );
        this->update();
    }
}


void SelectRectWidget::mouseReleaseEvent(QMouseEvent *e)
{
    press_ = false;
}
void SelectRectWidget::paintEvent(QPaintEvent *event)
{
    checkCenterRect();
    setRects();
    if(selectRectChange_ && (centerRect_ != preCenterRect_) ){
        selectRectChange_(centerRect_);
        preCenterRect_ = centerRect_;
    }
    QPainter painter(this);
    //绘制区域
    painter.fillRect(leftRect_, outsideColor_);
    painter.fillRect(topRect_, outsideColor_);
    painter.fillRect(rightRect_, outsideColor_);
    painter.fillRect(bottomRect_, outsideColor_);


    //绘制中间区域和边框虚线
//    dashPen_.setBrush(QBrush(dashColor_));
    painter.setPen(dashPen_);
    painter.fillRect(centerRect_, insideColor_);
    painter.drawRect(centerRect_);


    //move zoomdot
    labelLeftBottom_->move(centerRect_.x()-sDragDotWidth_/2+sDragDotOffset_,centerRect_.y()+centerRect_.height()-sDragDotWidth_/2-sDragDotOffset_);
    labelRightBottom_->move(centerRect_.x()+centerRect_.width()-sDragDotWidth_/2-sDragDotOffset_,centerRect_.y()+centerRect_.height()-sDragDotWidth_/2-sDragDotOffset_);
    labelLeftTop_->move(centerRect_.x()-sDragDotWidth_/2+sDragDotOffset_,centerRect_.y()-sDragDotWidth_/2+sDragDotOffset_);
    labelRightTop_->move(centerRect_.x()+centerRect_.width()-sDragDotWidth_/2-sDragDotOffset_,centerRect_.y()-sDragDotWidth_/2+sDragDotOffset_);




}


bool SelectRectWidget::eventFilter(QObject * obj, QEvent * e)
{
    if (obj == labelLeftBottom_
            || obj == labelLeftTop_
            || obj == labelRightBottom_
            || obj == labelRightTop_){
        //实现拖动右下角缩放窗口
        if(e->type() == QEvent::MouseButtonPress){
            QMouseEvent *event = (QMouseEvent *)e;
            // NoButton: fix frist press is NoButton bugs
            if (event->buttons() & Qt::LeftButton || event->buttons() == Qt::NoButton){
                dragZoomRunning_ = true;
                dragZoomLocation_ = centerRect_;
                dragZoomPos_ = event->globalPos();
                return true;
            }
        }
        else if(e->type() == QEvent::MouseMove){
            QMouseEvent *event = (QMouseEvent *)e;
            if (dragZoomRunning_ && (event->buttons() & Qt::LeftButton)){
                int dx = event->globalPos().x() - dragZoomPos_.x();
                int dy = event->globalPos().y() - dragZoomPos_.y();


                QRect rc = dragZoomLocation_;
                if (obj == labelLeftBottom_){
                    if(fixCenterRectRatio_ > 0){
                        if(std::abs(dx) > std::abs(dy)){
                            centerRect_.setLeft(std::max(rc.left() + dx , 0));
                            if(centerRect_.left()+sCenterRectMinWidth_ > centerRect_.right()){
                                centerRect_.setLeft(centerRect_.right() - sCenterRectMinWidth_);
                            }
                            centerRect_.setBottom(rc.top() + centerRect_.width()/fixCenterRectRatio_);
                            if(centerRect_.bottom() > this->height()-sLineWidth_){
                                centerRect_.setBottom(this->height() - sLineWidth_);
                                centerRect_.setLeft(rc.right() - centerRect_.height()*fixCenterRectRatio_);
                            }
                        }else{
                            centerRect_.setBottom(std::min(rc.bottom() + dy , this->height()-sLineWidth_));
                            if(centerRect_.bottom()-sCenterRectMinWidth_ < centerRect_.top()){
                                centerRect_.setBottom(rc.top() + sCenterRectMinWidth_);
                            }
                            centerRect_.setLeft(rc.right() - centerRect_.height()*fixCenterRectRatio_);
                            if(centerRect_.left() < 0){
                                centerRect_.setLeft(0);
                                centerRect_.setBottom(rc.top() + centerRect_.width()/fixCenterRectRatio_);
                            }
                        }
                    }else{
                        centerRect_.setLeft(rc.left() + dx);
                        centerRect_.setBottom(rc.bottom() + dy);
                        if(centerRect_.left()+sCenterRectMinWidth_ > centerRect_.right()){
                            centerRect_.setLeft(centerRect_.right() - sCenterRectMinWidth_);
                        }
                        if(centerRect_.bottom()-sCenterRectMinWidth_ < centerRect_.top()){
                            centerRect_.setBottom(centerRect_.top() + sCenterRectMinWidth_);
                        }
                    }


                }else if (obj == labelLeftTop_){
                    if(fixCenterRectRatio_ > 0){
                        if(std::abs(dx) > std::abs(dy)){
                            centerRect_.setLeft(std::max(rc.left() + dx , 0));
                            if(centerRect_.left()+sCenterRectMinWidth_ > centerRect_.right()){
                                centerRect_.setLeft(centerRect_.right() - sCenterRectMinWidth_);
                            }
                            centerRect_.setTop(rc.bottom() - centerRect_.width()/fixCenterRectRatio_);
                            if(centerRect_.top() < 0){
                                centerRect_.setTop(0);
                                centerRect_.setLeft(rc.right() - centerRect_.height()*fixCenterRectRatio_);
                            }
                        }else{
                            centerRect_.setTop(std::max(rc.top() + dy , 0));
                            if(centerRect_.bottom()-sCenterRectMinWidth_ < centerRect_.top()){
                                centerRect_.setTop(rc.bottom() - sCenterRectMinWidth_);
                            }
                            centerRect_.setLeft(rc.right() - centerRect_.height()*fixCenterRectRatio_);
                            if(centerRect_.left() < 0){
                                centerRect_.setLeft(0);
                                centerRect_.setTop(rc.bottom() - centerRect_.width()/fixCenterRectRatio_);
                            }
                        }
                    }else{
                        centerRect_.setLeft(rc.left() + dx);
                        centerRect_.setTop(rc.top() + dy);
                        if(centerRect_.left()+sCenterRectMinWidth_ > centerRect_.right()){
                            centerRect_.setLeft(centerRect_.right() - sCenterRectMinWidth_);
                        }
                        if(centerRect_.bottom()-sCenterRectMinWidth_ < centerRect_.top()){
                            centerRect_.setTop(centerRect_.bottom() - sCenterRectMinWidth_);
                        }
                    }


                }else if (obj == labelRightBottom_){
                    if(fixCenterRectRatio_ > 0){
                        if(std::abs(dx) > std::abs(dy)){
                            centerRect_.setRight(std::min(rc.right() + dx , this->width()-sLineWidth_));
                            if(centerRect_.left()+sCenterRectMinWidth_ > centerRect_.right()){
                                centerRect_.setRight(centerRect_.left() + sCenterRectMinWidth_);
                            }
                            centerRect_.setBottom(rc.top() + centerRect_.width()/fixCenterRectRatio_);
                            if(centerRect_.bottom() > this->height()-sLineWidth_){
                                centerRect_.setBottom(this->height() - sLineWidth_);
                                centerRect_.setRight(rc.left() + centerRect_.height()*fixCenterRectRatio_);
                            }
                        }else{
                            centerRect_.setBottom(std::min(rc.bottom() + dy , this->height()-sLineWidth_));
                            if(centerRect_.bottom()-sCenterRectMinWidth_ < centerRect_.top()){
                                centerRect_.setBottom(rc.top() + sCenterRectMinWidth_);
                            }
                            centerRect_.setRight(rc.left() + centerRect_.height()*fixCenterRectRatio_);
                            if(centerRect_.right() > this->width()-sLineWidth_){
                                centerRect_.setRight(this->width()-sLineWidth_);
                                centerRect_.setBottom(rc.top() + centerRect_.width()/fixCenterRectRatio_);
                            }
                        }
                    }else{
                        centerRect_.setRight(rc.right() + dx);
                        centerRect_.setBottom(rc.bottom() + dy);
                        if(centerRect_.left()+sCenterRectMinWidth_ > centerRect_.right()){
                            centerRect_.setRight(centerRect_.left() + sCenterRectMinWidth_);
                        }
                        if(centerRect_.bottom()-sCenterRectMinWidth_ < centerRect_.top()){
                            centerRect_.setBottom(centerRect_.top() + sCenterRectMinWidth_);
                        }
                    }


                }else if (obj == labelRightTop_){
                    if(fixCenterRectRatio_ > 0){
                        if(std::abs(dx) > std::abs(dy)){
                            centerRect_.setRight(std::min(rc.right() + dx , this->width()-sLineWidth_));
                            if(centerRect_.left()+sCenterRectMinWidth_ > centerRect_.right()){
                                centerRect_.setRight(centerRect_.left() + sCenterRectMinWidth_);
                            }
                            centerRect_.setTop(rc.bottom() - centerRect_.width()/fixCenterRectRatio_);
                            if(centerRect_.top() < 0){
                                centerRect_.setTop(0);
                                centerRect_.setRight(rc.left() + centerRect_.height()*fixCenterRectRatio_);
                            }
                        }else{
                            centerRect_.setTop(std::max(rc.top() + dy , 0));
                            if(centerRect_.bottom()-sCenterRectMinWidth_ < centerRect_.top()){
                                centerRect_.setTop(rc.bottom() - sCenterRectMinWidth_);
                            }
                            centerRect_.setRight(rc.left() + centerRect_.height()*fixCenterRectRatio_);
                            if(centerRect_.right() > this->width()-sLineWidth_){
                                centerRect_.setRight(this->width()-sLineWidth_);
                                centerRect_.setTop(rc.bottom() - centerRect_.width()/fixCenterRectRatio_);
                            }
                        }
                    }else{
                        centerRect_.setRight(rc.right() + dx);
                        centerRect_.setTop(rc.top() + dy);
                        if(centerRect_.left()+sCenterRectMinWidth_ > centerRect_.right()){
                            centerRect_.setRight(centerRect_.left() + sCenterRectMinWidth_);
                        }
                        if(centerRect_.bottom()-sCenterRectMinWidth_ < centerRect_.top()){
                            centerRect_.setTop(centerRect_.bottom() - sCenterRectMinWidth_);
                        }
                    }
                }
                this->update();
                return true;
            }
        }
        else if(e->type() == QEvent::MouseButtonRelease){
            dragZoomRunning_ = false;
            return true;
        }
    }
    return QWidget::eventFilter(obj, e);
}



```

已知是点的终点坐标  以及中心矩形的起始位置



以左下角为例 

如果 x变化大于y

先处理x 

x 需要满足  labelx <=  dx + 原矩形的x <= 原矩形的右侧x - 最小宽度

然后 再根据 新矩阵的宽度 确定 高度

再判断高度是否越界

如果越界更新并修改宽度

反之

先处理y

y 需要满足 labely + labelh <= dy + 原矩阵的y + h <= labely

确定宽度

判断宽度越界

如果越界更新并修改高度





左上角



RGB  R

255  128 255

255  127 254

255  126 253

255 125  252

255 121 247

255 120 246

255 101 220

255 100 219



255 80 184

255 81 186



255 65 154

255 64 152        102

255 63 149

255 0 0

255 1 2

255 2 5

255 3 7









[0,1] = 0.254901



rgbl = (rgb/128) * r

