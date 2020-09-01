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

//����ͼ����ʾ
int loadimage()
{
	Mat image;
	image = imread("lena.jpg", IMREAD_COLOR); // Read the file
	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Display window", image);                // Show our image insid	e it.
	waitKey(0); // Wait for a keystroke in the window
	destroyAllWindows();
	return 0;
}

//��ֵ��
int Binarization()
{
	Mat image,res;
	image = imread("lena.jpg", 0); // �Ҷȶ���
	namedWindow("ԭͼ", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("ԭͼ", image);                // Show our image insid	e it.
	
	res = image.clone();
	int gray;
	for (int i = 0; i < res.rows; i++)
	{
		for (int j = 0; j < res.cols; j++)
		{
			gray = res.at<uchar>(i, j);
			if (gray > 80)
				gray = 255;
			else
				gray = 0;
			res.at<uchar>(i, j) = saturate_cast<uchar>(gray);
		}
	}

	//threshold(image, res, 80, 255, 0);
	namedWindow("��ֵ����ͼ", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("��ֵ����ͼ", res);                // Show our image insid	e it.
	waitKey(0); // Wait for a keystroke in the window
	destroyAllWindows();
	return 0;
}

//�����任
int logTrans()					//�����任
{
	Mat image, res;
	image = imread("lena.jpg", 0); // �Ҷȶ���
	namedWindow("ԭͼ", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("ԭͼ", image);                // Show our image insid	e it.
	res = image.clone();
	
	double r = 5, gray;
	for (int i = 0; i < res.rows; i++)
	{
		for (int j = 0; j < res.cols; j++)
		{
			gray = (double)res.at<uchar>(i, j);
			gray = r * log((double)(1 + gray));
			res.at<uchar>(i,j)= saturate_cast<uchar>(gray);
		}
	}
	normalize(res, res, 0, 255, NORM_MINMAX);		//��һ����0~255
	convertScaleAbs(res, res);						//ת��uint8

	namedWindow("�����任��ͼ", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("�����任��ͼ", res);                // Show our image insid	e it.
	waitKey(0); // Wait for a keystroke in the window
	destroyAllWindows();
	return 0;
}

//٤��任
int gamma()
{
	Mat image, res;
	image = imread("lena.jpg", 0); // �Ҷȶ���
	namedWindow("ԭͼ", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("ԭͼ", image);                // Show our image insid	e it.
	res = image.clone();

	double r = 1.2, gray, a = 1;
	for (int i = 0; i < res.rows; i++)
	{
		for (int j = 0; j < res.cols; j++)
		{
			gray = (double)res.at<uchar>(i, j);
			gray = a * pow(gray, r);
			res.at<uchar>(i, j) = saturate_cast<uchar>(gray);
		}
	}
	normalize(res, res, 0, 255, NORM_MINMAX);			//��һ����0~255
	convertScaleAbs(res, res);							//ת��uint8

	namedWindow("gamma�任��ͼ", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("gamma��ͼ", res);                // Show our image insid	e it.
	waitKey(0); // Wait for a keystroke in the window
	destroyAllWindows();
	return 0;
}


//��ɫ�任
void imcomplement_CMY()
{
	Mat image, res;
	image = imread("lena.jpg", IMREAD_COLOR); // ����
	namedWindow("ԭͼ", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("ԭͼ", image);                // Show our image insid	e it.
	res = image.clone();
	Vec3b pixel, temp;
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			pixel = image.at<Vec3b>(i, j);			//RGB->CMY
			/*
			pixel�������ͨ����BGR���䲹ɫ��CMYɫ��ģ��任��ϵ���£�
			C=255-R��
			M=255-G��
			Y=255-B��
			*/
			temp[0] = 255 - pixel[2];		//C=255-R��
			temp[1] = 255 - pixel[1];		//M=255-G��
			temp[2] = 255 - pixel[0];		//Y=255-B��

			res.at <Vec3b>(i, j) = temp;
		}
	}
	imshow("��ɫͼ", res);
	waitKey(0); // Wait for a keystroke in the window
	destroyAllWindows();
	return;
}

void imcomplement_HSV()
{
	Mat image, res, res1;
	image = imread("lena.jpg", IMREAD_COLOR); // ����
	namedWindow("ԭͼ", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("ԭͼ", image);                // Show our image insid	e it.
	res = image.clone();
	res1 = image.clone();
	cvtColor(image, res, COLOR_BGR2HSV);
	imshow("HSVͼ", res);
	Vec3b pixel, temp;
	for (int i = 0; i < res.rows; i++)
	{
		for (int j = 0; j < res.cols; j++)
		{
			pixel = res.at<Vec3b>(i, j);			//3��double
			if (pixel[0] >= 180.0)
				temp[0] = pixel[0] - 180.0;
			else
				temp[0] = 180.0 - pixel[0];
			temp[1] = pixel[1];
			temp[2] = 1.0 - pixel[2];
			res1.at<Vec3b>(i, j) = temp;
		}
	}
	imshow("��ɫͼ", res1);
	waitKey(0); // Wait for a keystroke in the window
	destroyAllWindows();
	return;
}


void test1()
{
	loadimage();				//���� OpenCV ��ȡͼ��
	return;
}

void test2()
{
	Binarization();			//��ֵ��
	return;
}

void test3()
{
	logTrans();				//�����任
	return;
}

void test4()
{
	gamma();
	return;
}

void test5()
{
	imcomplement_CMY();
	imcomplement_HSV();
}
int main()
{
	test1();
	test2();
	test3();
	test4();
	test5();	
	return 0;
}