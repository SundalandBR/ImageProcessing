#pragma once

#include <QMainWindow>
#include "Image_opencv.h"
#include "ui_Image_crop.h"
#include <qpen.h>
#include <qpainter.h>
#include <qevent.h>

class Image_crop : public QMainWindow
{
	Q_OBJECT

public:
	Image_crop(QWidget *parent = nullptr);
	~Image_crop();


void setRects();

private:
	Ui::Image_cropClass ui;
	QRect leftRect_;//�м��ο����������ɲ�Rect
	QRect topRect_;//�м��ο�����Ķ����ɲ�Rect
	QRect rightRect_;//�м��ο�������Ҳ��ɲ�Rect
	QRect bottomRect_;//�м��ο�����ĵײ��ɲ�Rect
	QRect centerRect_;//�м��ο������Rect

	QColor outsideColor_;//�ⲿ�ɲ����ɫֵ
	QColor insideColor_;//�ڲ��ο��������ɫֵ
	QColor dashColor_;//�м��ο���������߱߿����ɫֵ

	QPen dashPen_;//�м��ο���������߱߿��Pen�������������߳��Ⱥͼ�����ȵȣ�
	QVector<qreal> dashes_;//dashPen_�����߳��Ⱥͼ����������

	QLabel* labelLeftBottom_ = nullptr;//���Դ������ţ��ο��������߱߿����²��Ķ���
	QLabel* labelRightBottom_ = nullptr;//���Դ������ţ��ο��������߱߿����²��Ķ���
	QLabel* labelLeftTop_ = nullptr;//���Դ������ţ��ο��������߱߿����ϲ��Ķ���
	QLabel* labelRightTop_ = nullptr;//���Դ������ţ��ο��������߱߿����ϲ��Ķ���

	QPoint start_pos_;//����ƶ���ʼλ��
	QPoint end_pos_;//����ƶ�Ŀ��λ��
	QPoint global_start_pos_;//����ƶ�ȫ����ʼλ��
	QRect center_move_location_;//���Ŀ���ʼλ��

	QPixmap pix;

	float fix_ratio;//�������ŵı���ֵ 16/9,4/3 
	bool fix_crop = false;//�Ƿ񰴱�������
	bool button_press = false;//�Ƿ������Ķ�����ק
	bool press_ = false;//�Ƿ�����ü�����ק

	int labelX_;//����ͼƬ��label���x����
	int labelY_;//����ͼƬ��label���y����
	int labelWidth_;//����ͼƬ��label��Ŀ��
	int labelHeigth_;//����ͼƬ��label��ĳ���

	static int sDragDotWidth_;      //ѡ�������ϼ������ԷŴ���С�ĵ��С
	static int sCenterRectMinWidth_;//ѡ������С��Ⱥ͸߶ȣ���ֹѡ�������ص�
	static int sLineWidth_;//ѡ�����߿��
	static int sDragDotOffset_;//�ĸ������offsetֵ

private:
	virtual void mousePressEvent(QMouseEvent* e) override;
	virtual void mouseMoveEvent(QMouseEvent* e) override;
	virtual void paintEvent(QPaintEvent* event) override;
	virtual bool eventFilter(QObject*, QEvent*) override;

private slots:
	void setFixCenterRectRatio(float ratio);

};
