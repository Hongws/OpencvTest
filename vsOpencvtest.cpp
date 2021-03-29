// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("E:\\opencv\\123.jpg");
	imshow("显示图像", image);
	waitKey(0);

	return 0;
}

