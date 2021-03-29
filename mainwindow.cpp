#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<opencv2/opencv.hpp>

using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    Mat src = imread("E:\\opencv\\123.jpg");
    cvtColor( src, src, CV_BGR2RGB );
    QImage     img = QImage( (src.data), src.cols, src.rows,static_cast<int>(src.step), QImage::Format_RGB888 );
    ui->label->setPixmap( QPixmap::fromImage(img));
    ui->label->resize( ui->label->pixmap()->size());


}

MainWindow::~MainWindow()
{
    delete ui;
}

