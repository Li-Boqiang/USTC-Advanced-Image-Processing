//图像灰度变换
#include<iostream>
#include<string>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;

void test1()
{
	//缩放
	Mat image;
	image = imread("lena.jpg", IMREAD_COLOR); // Read the file

	imshow("原图", image);                // Show our image inside it.

	Mat dst = Mat::zeros(256, 256, CV_8UC3); //我要转化为512*512大小的
	resize(image, dst, dst.size());

	imshow("尺寸调整之后", dst);

	waitKey(0); // Wait for a keystroke in the window
	destroyAllWindows();
	return ;
}

void test2(double a, double b)
{
	Mat image = imread("lena.jpg");
	imshow("原图", image);

	Mat dst;
	resize(image, dst, Size(), a, b);//我长宽都变为原来的0.5倍

	imshow("尺寸调整之后", dst);

	waitKey(0);
	destroyAllWindows();
	return;
}


void test3()
{
	Mat image = imread("lena.jpg");
	imshow("原图", image);

	Mat dst, dst2;
	pyrUp(image, dst, Size(image.cols * 2, image.rows * 2)); //放大一倍
	pyrDown(image, dst2, Size(image.cols * 0.5, image.rows * 0.5)); //缩小为原来的一半

	imshow("尺寸放大之后", dst);
	imshow("尺寸缩小之后", dst2);

	waitKey(0);
	destroyAllWindows();
	return;
}

int main()
{
	test1();
	test2(0.3, 0.3);
	test3();
	return 0;
}