#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Image_processing.h"
#include "Image_opencv.h"



class Image_processing : public QMainWindow
{
    Q_OBJECT

public:
    Image_processing(QWidget *parent = nullptr);
    ~Image_processing();

private:
    Ui::Image_processingClass ui;

private slots:
    void on_ImgRead_menu_clicked();
    void on_Removal_button_clicked();
    void on_Rotate_button_clicked();
    void on_open_file_menu_clicked();
    //void on_Crop_button_clicked();
    void receive_mat(cv::Mat r_Mat);

private:
    void update_photo_label();

};

