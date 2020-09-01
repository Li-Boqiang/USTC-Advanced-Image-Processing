//ͼ��Ҷȱ任
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
	//����
	Mat image;
	image = imread("lena.jpg", IMREAD_COLOR); // Read the file

	imshow("ԭͼ", image);                // Show our image inside it.

	Mat dst = Mat::zeros(256, 256, CV_8UC3); //��Ҫת��Ϊ512*512��С��
	resize(image, dst, dst.size());

	imshow("�ߴ����֮��", dst);

	waitKey(0); // Wait for a keystroke in the window
	destroyAllWindows();
	return ;
}

void test2(double a, double b)
{
	Mat image = imread("lena.jpg");
	imshow("ԭͼ", image);

	Mat dst;
	resize(image, dst, Size(), a, b);//�ҳ�����Ϊԭ����0.5��

	imshow("�ߴ����֮��", dst);

	waitKey(0);
	destroyAllWindows();
	return;
}


void test3()
{
	Mat image = imread("lena.jpg");
	imshow("ԭͼ", image);

	Mat dst, dst2;
	pyrUp(image, dst, Size(image.cols * 2, image.rows * 2)); //�Ŵ�һ��
	pyrDown(image, dst2, Size(image.cols * 0.5, image.rows * 0.5)); //��СΪԭ����һ��

	imshow("�ߴ�Ŵ�֮��", dst);
	imshow("�ߴ���С֮��", dst2);

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