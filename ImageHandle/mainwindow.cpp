#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setStyle(qApp->applicationDirPath()+"/brown.css");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setStyle(const QString &qssFile)
{
    QFile file(qssFile);
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        qApp->setStyleSheet(qss);
        QString PaletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(PaletteColor)));
        file.close();
    }
}

//功能性
int MainWindow::calmp(int value, int minValue, int maxValue)
{
    if (value < minValue)
        return minValue;
    else if (value > maxValue)
        return maxValue;
    return value;
}

void MainWindow::reliefTrans(Mat& src, Mat& dst)
{
    dst = src.clone();
    int rowNumber = dst.rows;
    int colNumber = dst.cols;

    for (int i = 1; i < rowNumber - 1; ++i) {
        for (int j = 1; j < colNumber - 1; ++j) {
            dst.at<Vec3b>(i, j)[0] = calmp(src.at<Vec3b>(i + 1, j + 1)[0] - src.at<Vec3b>(i - 1, j - 1)[0] + 128);
            dst.at<Vec3b>(i, j)[1] = calmp(src.at<Vec3b>(i + 1, j + 1)[1] - src.at<Vec3b>(i - 1, j - 1)[1] + 128);
            dst.at<Vec3b>(i, j)[2] = calmp(src.at<Vec3b>(i + 1, j + 1)[2] - src.at<Vec3b>(i - 1, j - 1)[2] + 128);
        }
    }
}

//void cv::cvtColor(
//cv::InputArray src, // 输入序列
//cv::OutputArray dst, // 输出序列
//int code, // 颜色映射码
//int dstCn = 0 // 输出的通道数 (0='automatic')
//);
void MainWindow::ShowLabel(Mat src)
{
    Mat dest;
    QImage img;

    if(src.channels() == 3)    // RGB image
    {
        cvtColor(src, dest, CV_BGR2RGB);
        img = QImage((const uchar*)(dest.data), dest.cols, dest.rows, dest.cols*dest.channels(), QImage::Format_RGB888);
        //img = QImage( (dest.data), dest.cols, dest.rows,static_cast<int>(dest.step), QImage::Format_RGB888 );
    }else                     // gray image
    {
        //img = QImage(src.data, src.cols, src.rows, src.cols*src.channels(), QImage::Format_Indexed8);
        img = QImage(src.data, src.cols, src.rows, static_cast<int>(src.step), QImage::Format_Indexed8);
    }

    ui->label_dest->setPixmap( QPixmap::fromImage(img));
    ui->label_dest->resize(ui->label_dest->pixmap()->size());

}


//槽
void MainWindow::on_pbtn_open_clicked()
{
    qDebug() << "select a pic";

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "D:/", tr("Image Files(*.jpg *.png)"));
    if(fileName.length() == 0)
        QMessageBox::information(nullptr, tr("Tips"), tr("You didn't select any files."));
    else
    {
        m_mat_src = imread(fileName.toStdString());

        //imshow("显示图像", m_mat_src);

        cvtColor(m_mat_src, m_mat_src, CV_BGR2RGB);
        QImage img = QImage((m_mat_src.data), m_mat_src.cols, m_mat_src.rows,static_cast<int>(m_mat_src.step), QImage::Format_RGB888 );
        ui->label_src->setPixmap( QPixmap::fromImage(img));
        ui->label_src->resize( ui->label_src->pixmap()->size());
    }
}

void MainWindow::on_pbtn_relief_clicked()
{
    qDebug() << "clicked relief";

    if(m_mat_src.empty())
    {
        QMessageBox::information(nullptr, tr("Tips"), tr("You Must Select a Pic"));
        return;
    }

    Mat dstImage;
    reliefTrans(m_mat_src, dstImage);

    //imshow("显示图像", dstImage);

    ShowLabel(dstImage);
}


void MainWindow::on_pbtn_invert_single_clicked()
{
    qDebug() << "clicked invert_single";
    if(m_mat_src.empty())
    {
        QMessageBox::information(nullptr, tr("Tips"), tr("You Must Select a Pic"));
        return;
    }

    Mat dstImage;
    cvtColor(m_mat_src, dstImage, COLOR_BGR2GRAY);

    int rows = m_mat_src.rows;
    int cols = m_mat_src.cols;

    //单通道图像的反色
    for(int row = 0;row<rows;row++){
        for(int col = 0;col<cols;col++){
            dstImage.at<uchar>(row,col) = 255 - dstImage.at<uchar>(row,col);
        }
    }

    //imshow("显示图像", dstImage);

    ShowLabel(dstImage);
}


void MainWindow::on_pbtn_invert_mul_clicked()
{
    qDebug() << "clicked invert_mul";
    if(m_mat_src.empty())
    {
        QMessageBox::information(nullptr, tr("Tips"), tr("You Must Select a Pic"));
        return;
    }

    int rows = m_mat_src.rows;
    int cols = m_mat_src.cols;

    Mat dstImage;
    dstImage.create(m_mat_src.size(),m_mat_src.type());

    for(int row = 0;row<rows;row++){
        for(int col=0;col<cols;col++){
            int b = m_mat_src.at<Vec3b>(row,col)[0];
            int g = m_mat_src.at<Vec3b>(row,col)[1];
            int r = m_mat_src.at<Vec3b>(row,col)[2];

            dstImage.at<Vec3b>(row,col)[0] = 255-b;
            dstImage.at<Vec3b>(row,col)[1] = 255-g;
            dstImage.at<Vec3b>(row,col)[2] = 255-r;

        }
    }

    ShowLabel(dstImage);

    dstImage.release();


}















