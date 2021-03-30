#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "header.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setStyle(const QString &qssFile);
    int calmp(int value, int minValue = 0, int maxValue = 255);
    void reliefTrans(Mat& src, Mat& dst);

    void ShowLabel(Mat src);



private slots:
    void on_pbtn_open_clicked();

    void on_pbtn_relief_clicked();

    void on_pbtn_invert_single_clicked();

    void on_pbtn_invert_mul_clicked();

private:
    Ui::MainWindow *ui;

    Mat m_mat_src;
};
#endif // MAINWINDOW_H
