//ͼ��Ҷȱ任
#include<iostream>
#include<string>
#include <cstdlib>
#include <limits>
#include <cmath>
#include <windows.h>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/core/core_c.h>
//#include <opencv2/core/hal/intrin_sse.hpp>
using namespace std;
using namespace cv;


//����������������
void addSalt(Mat& image, int n)
{
	srand((unsigned)time(NULL));
	int i, j;
	for (int k = 0; k < n; k++)//��ͼ����n�������������
	{
		i = rand() % image.cols;
		j = rand() % image.rows;
		//��ͼ����ɫ����ı�
		if (image.channels() == 1)
			image.at<uchar>(j, i) = 255;
		else
		{
			for (int t = 0; t < image.channels(); t++)
			{
				image.at<Vec3b>(j, i)[t] = 255;
			}
		}
	}
}

void addPepper(Mat& image, int n)//���������뽷����
{
	srand((unsigned)time(NULL));
	for (int k = 0; k < n; k++)//��ͼ����n�������������
	{
		int i = rand() % image.cols;
		int j = rand() % image.rows;
		//��ͼ����ɫ����ı�
		if (image.channels() == 1)
			image.at<uchar>(j, i) = 0;
		else
		{
			for (int t = 0; t < image.channels(); t++)
			{
				image.at<Vec3b>(j, i)[t] = 0;
			}
		}

	}
}

int GaussianNoise(double mu, double sigma)
{
	//����һ���ر�С��ֵ
	const double epsilon = numeric_limits<double>::min();//����Ŀ�����������ܱ�ʾ����ƽ�1��������1�Ĳ�ľ���ֵ
	static double z0, z1;
	static bool flag = false;
	flag = !flag;
	//flagΪ�٣������˹�������
	if (!flag)
		return z1 * sigma + mu;
	double u1, u2;
	//�����������

	do
	{
		u1 = rand()*(1.0 / RAND_MAX);
		u2 = rand()*(1.0 / RAND_MAX);
	} while (u1 <= epsilon);
	//flagΪ�湹���˹�������X
	z0 = sqrt(-2.0*log(u1))*cos(2 * CV_PI * u2);
	z1 = sqrt(-2.0*log(u1))*sin(2 * CV_PI * u2);
	return z1 * sigma + mu;
}

Mat addGaussianNoise(Mat& srcImage)
{
	Mat resultImage = srcImage.clone();    //���,��¡
	int channels = resultImage.channels();    //��ȡͼ���ͨ��
	int nRows = resultImage.rows;    //ͼ�������

	int nCols = resultImage.cols*channels;   //ͼ���������
	//�ж�ͼ���������
	if (resultImage.isContinuous())    //�жϾ����Ƿ��������������������൱��ֻ��Ҫ����һ��һά���� 
	{
		nCols *= nRows;
		nRows = 1;
	}
	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{	//��Ӹ�˹����
			int val = resultImage.ptr<uchar>(i)[j] + GaussianNoise(2, 0.8) * 32;
			if (val < 0)
				val = 0;
			if (val > 255)
				val = 255;
			resultImage.ptr<uchar>(i)[j] = (uchar)val;
		}
	}
	return resultImage;
}

//��ֵ�˲���
void medeanFilter(Mat& src, int win_size) {
	int rows = src.rows, cols = src.cols;
	int start = win_size / 2;
	for (int m = start; m < rows - start; m++) {
		for (int n = start; n < cols - start; n++) {
			vector<uchar> model;
			for (int i = -start + m; i <= start + m; i++) {
				for (int j = -start + n; j <= start + n; j++) {
					//cout << int(src.at<uchar>(i, j)) << endl;
					model.push_back(src.at<uchar>(i, j));
				}
			}
			sort(model.begin(), model.end());     //���ÿ����������
			src.at<uchar>(m, n) = model[win_size*win_size / 2];
		}
	}
}

//������ֵ�˲���
void meanFilter(Mat& src, int win_size) {
	int rows = src.rows, cols = src.cols;
	int start = win_size / 2;
	for (int m = start; m < rows - start; m++) {
		for (int n = start; n < cols - start; n++) {
			if (src.channels() == 1)				//��ɫͼ
			{
				int sum = 0;
				for (int i = -start + m; i <= start + m; i++) 
				{
					for (int j = -start + n; j <= start + n; j++) {
						sum += src.at<uchar>(i, j);
					}
				}
				src.at<uchar>(m, n) = uchar(sum / win_size / win_size);
			}
			else
			{
				Vec3b pixel;
				int sum1[3] = { 0 };
				for (int i = -start + m; i <= start + m; i++) 
				{
					for (int j = -start + n; j <= start + n; j++) 
					{
						pixel = src.at<Vec3b>(i, j);
						for (int k = 0; k < src.channels(); k++)
						{
							sum1[k] += pixel[k];
						}
					}
					
				}
				for (int k = 0; k < src.channels(); k++)
				{
					pixel[k] = sum1[k] / win_size / win_size;
				}
				src.at<Vec3b>(m, n) = pixel;
			}
		}
	}
}

//���ξ�ֵ�˲���
Mat GeometryMeanFilter(Mat src)
{
	Mat dst = src.clone();
	int row, col;
	int h = src.rows;
	int w = src.cols;
	double mul;
	double dc;
	int mn;
	//����ÿ�����ص�ȥ��� color ֵ
	for (int i = 0; i < src.rows; i++) 
	{
		for (int j = 0; j < src.cols; j++)
		{

			if (src.channels() == 1)				//��ɫͼ
			{
				mul = 1.0;
				mn = 0;
				//ͳ�������ڵļ���ƽ��ֵ�������С 5*5
				for (int m = -2; m <= 2; m++) {
					row = i + m;
					for (int n = -2; n <= 2; n++) {
						col = j + n;
						if (row >= 0 && row < h && col >= 0 && col < w) {
							int s = src.at<uchar>(row, col);
							mul = mul * (s == 0 ? 1 : s); //�����ڵķ������ص���ˣ���Сֵ�趨Ϊ1
							mn++;
						}
					}
				}
				//���� 1/mn �η�
				dc = pow(mul, 1.0 / mn);
				//ͳ�Ƴɹ�����ȥ���ͼ��
				int res = (int)dc;
				dst.at<uchar>(i, j) = res;
			}
			else
			{
				double multi[3] = { 1.0,1.0,1.0 };
				mn = 0;
				Vec3b pixel;

				for (int m = -2; m <= 2; m++) 
				{
					row = i + m;
					for (int n = -2; n <= 2; n++)
					{
						col = j + n;
						if (row >= 0 && row < h && col >= 0 && col < w) 
						{
							pixel = src.at<Vec3b>(row, col);
							for (int k = 0; k < src.channels(); k++)
							{
								multi[k] = multi[k] * (pixel[k] == 0 ? 1 : pixel[k]);//�����ڵķ������ص���ˣ���Сֵ�趨Ϊ1
							}
							mn++;
						}
					}
				}
				double d;
				for (int k = 0; k < src.channels(); k++)
				{
					d = pow(multi[k], 1.0 / mn);
					pixel[k] = (int)d;
				}
				dst.at<Vec3b>(i, j) = pixel;
			}
		}
	}
	return dst;
}

//г����ֵ�˲�������ģ���С 5*5
Mat HarmonicMeanFilter(Mat src)
{
	//IplImage* dst = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
	Mat dst = src.clone();
	int row, col;
	int h = src.rows;
	int w = src.cols;
	double sum;
	double dc;
	int mn;
	//����ÿ�����ص�ȥ��� color ֵ
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			sum = 0.0;
			mn = 0;
			//ͳ������,5*5 ģ��
			for (int m = -2; m <= 2; m++) {
				row = i + m;
				for (int n = -2; n <= 2; n++) {
					col = j + n;
					if (row >= 0 && row < h && col >= 0 && col < w) {
						int s = src.at<uchar>(row, col);
						sum = sum + (s == 0 ? 255 : 255.0 / s);					//�����0���趨Ϊ255
						mn++;
					}
				}
			}
			int d;
			dc= mn * 255.0 / sum;
			d = dc;
			//ͳ�Ƴɹ�����ȥ���ͼ��
			dst.at<uchar>(i, j) = d;
		}
	}
	return dst;
}

//��г����ֵ��С�˲�������ģ���С 5*5
Mat InverseHarmonicMeanFilter(Mat src,double Q)
{
	Mat dst = src.clone();
	int row, col;
	int h = src.rows;
	int w = src.cols;
	double sum;
	double sum1;
	double dc;
	//double Q = 2;
	//����ÿ�����ص�ȥ��� color ֵ
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			sum = 0.0;
			sum1 = 0.0;
			//ͳ������
			for (int m = -2; m <= 2; m++) {
				row = i + m;
				for (int n = -2; n <= 2; n++) {
					col = j + n;
					if (row >= 0 && row < h && col >= 0 && col < w) {

						int s = src.at<uchar>(row, col);
						sum = sum + pow(s , Q + 1);
						sum1 = sum1 + pow(s , Q);
					}
				}
			}
			//���� 1/mn �η�
			int d;
			dc = sum1 == 0 ? 0 : (sum / sum1);
			d = (int)dc;
			//ͳ�Ƴɹ�����ȥ���ͼ��
			dst.at<uchar>(i, j) = d;
		}
	}
	return dst;
}

//����Ӧ��ֵ�˲�
Mat SelfAdaptMedianFilter(Mat src) 
{
	Mat dst = src.clone();
	int row, col;
	int h = src.rows;
	int w = src.cols;
	double Zmin, Zmax, Zmed, Zxy, Smax = 7;
	int wsize;
	//����ÿ�����ص�ȥ��� color ֵ
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			//ͳ������
			wsize = 1;
			while (wsize <= 3) {
				Zmin = 255.0;
				Zmax = 0.0;
				Zmed = 0.0;
				int  Zxy = src.at<uchar>(i,j);
				int mn = 0;
				for (int m = -wsize; m <= wsize; m++) 
				{
					row = i + m;
					for (int n = -wsize; n <= wsize; n++)
					{
						col = j + n;
						if (row >= 0 && row < h && col >= 0 && col < w)
						{
							int s = src.at<uchar>(row,col);
							if (s > Zmax) 
							{
								Zmax = s;
							}
							if (s < Zmin) 
							{
								Zmin = s;
							}
							Zmed = Zmed + s;
							mn++;
						}
					}
				}
				Zmed = Zmed / mn;
				int d;
				if ((Zmed - Zmin) > 0 && (Zmed - Zmax) < 0) {
					if ((Zxy - Zmin) > 0 && (Zxy - Zmax) < 0) {
						d = Zxy;
					}
					else {
						d = Zmed;
					}
					dst.at<uchar>(i, j) = d;
					break;
				}
				else {
					wsize++;
					if (wsize > 3) {
						int d;
						d = Zmed;
						dst.at<uchar>(i, j) = d;
						break;
					}
				}
			}
		}
	}
	return dst;
}

//����Ӧ��ֵ�˲�
Mat SelfAdaptMeanFilter(Mat src)
{
	Mat dst = src.clone();
	blur(src, dst, Size(7, 7));
	int row, col;
	int h = src.rows;
	int w = src.cols;
	int mn;
	double Zxy;
	double Zmed;
	double Sxy;
	double Sl;
	double Sn = 100;
	for (int i = 0; i < src.rows; i++) 
	{
		for (int j = 0; j < src.cols; j++)
		{
			int Zxy = src.at<uchar>(i, j);
			int Zmed = src.at<uchar>(i, j);
			Sl = 0;
			mn = 0;
			for (int m = -3; m <= 3; m++) {
				row = i + m;
				for (int n = -3; n <= 3; n++) {
					col = j + n;
					if (row >= 0 && row < h && col >= 0 && col < w) {
						int Sxy = src.at<uchar>(row, col); 
						Sl = Sl + pow(Sxy - Zmed, 2);
						mn++;
					}
				}
			}
			Sl = Sl / mn;
			int d =(int) (Zxy - Sn / Sl * (Zxy - Zmed));
			dst.at<uchar>(i, j) = d;
		}
	}
	return dst;
}

IplImage * MatToIplImage(Mat image)
{
	Mat t = image.clone();
	IplImage *res= &IplImage(t);
	return res;
}

Mat IplImageToMat(IplImage* image)
{
	Mat res= cvarrToMat(image, true);
	return res;
}

void test1()
{
	Mat image, noise, res;

	/*----------��˹����+������ֵ-----------*/
	image = imread("lena.jpg", 0); // Read the file
	imshow("ԭʼͼ��", image);                // Show our image inside it.
	
	noise = addGaussianNoise(image);			//��Ӹ�˹����
	imshow("��Ӹ�˹����", noise);
	
	res = noise.clone();
	meanFilter(res, 5);					//������ֵ�˲���
	imshow("������ֵ�˲���", res);
	/*------չʾͼ��-------*/
	waitKey(0);
	destroyAllWindows();
	
	/*----------��������+���ξ�ֵ-----------*/
	image = imread("lena.jpg", 0); // Read the file
	imshow("ԭʼͼ��", image);                // Show our image inside it.

	noise = image.clone();
	addPepper(noise, 1000);
	imshow("���1000����������", noise);

	res = noise.clone();
	meanFilter(res, 5);
	imshow("���ξ�ֵ�˲���", res);

	/*------չʾͼ��-------*/
	waitKey(0);
	destroyAllWindows();

	/*--------------������+г����ֵ�˲���------------*/
	image = imread("lena.jpg", 0); // Read the file
	imshow("ԭʼͼ��", image);                // Show our image inside it.

	noise = image.clone();
	addSalt(noise, 1000);
	imshow("���1000��������", noise);

	res = HarmonicMeanFilter(noise);
	imshow("5*5г����ֵ�˲���", res);

	/*------չʾͼ��-------*/
	waitKey(0);
	destroyAllWindows();


	/*-----------��������+��г����ֵ�˲���-----------*/
	image = imread("lena.jpg", 0); // Read the file
	imshow("ԭʼͼ��", image);                // Show our image inside it.

	noise = image.clone();
	addSalt(noise, 1000);
	Sleep(2000);					//��ֹ���������һ��
	addPepper(noise, 1000);
	imshow("���1000��������+1000����������", noise);

	res = InverseHarmonicMeanFilter(noise, 1);				//�ڶ���������Q��Q=0�˻���������ֵ
	imshow("5*5��г����ֵ�˲���", res);

	/*------չʾͼ��-------*/
	waitKey(0);
	destroyAllWindows();
	return;
}

void test2()
{
	Mat image, noise, res1, res2;

	/*---------����------------*/
	image = imread("lena.jpg", 0); // Read the file
	imshow("ԭʼͼ��", image);                // Show our image inside it.

	noise = image.clone();
	addPepper(noise, 1000);
	imshow("���1000����������", noise);

	res1 = noise.clone();
	medeanFilter(res1, 5);
	imshow("5*5�о�ֵ�˲���", res1);

	res2 = noise.clone();

	res2 = noise.clone();
	medeanFilter(res2, 9);
	imshow("9*9�о�ֵ�˲���", res2);
	/*------չʾͼ��-------*/
	waitKey(0);
	destroyAllWindows();

	/*-----------������---------------*/
	image = imread("lena.jpg", 0); // Read the file
	imshow("ԭʼͼ��", image);                // Show our image inside it.

	noise = image.clone();
	addSalt(noise, 1000);
	imshow("���1000��������", noise);

	res1 = noise.clone();
	medeanFilter(res1, 5);
	imshow("5*5�о�ֵ�˲���", res1);

	res2 = noise.clone();

	res2 = noise.clone();
	medeanFilter(res2, 9);
	imshow("9*9�о�ֵ�˲���", res2);
	/*------չʾͼ��-------*/
	waitKey(0);
	destroyAllWindows();


	/*-----------������+��������---------------*/
	image = imread("lena.jpg", 0); // Read the file
	imshow("ԭʼͼ��", image);                // Show our image inside it.

	noise = image.clone();
	addSalt(noise, 1000);
	addPepper(noise, 1000);
	imshow("���1000��������+1000����������", noise);

	res1 = noise.clone();
	medeanFilter(res1, 5);
	imshow("5*5�о�ֵ�˲���", res1);

	res2 = noise.clone();

	res2 = noise.clone();
	medeanFilter(res2, 9);
	imshow("9*9�о�ֵ�˲���", res2);
	/*------չʾͼ��-------*/
	waitKey(0);
	destroyAllWindows();
	return;
}

void test3()
{
	Mat image, res1, res2,noise;
	image = imread("lena.jpg", 0); // Read the file
	imshow("ԭʼͼ��", image);

	noise = image.clone();
	addPepper(noise, 1000);
	Sleep(2000);
	addSalt(noise, 1000);
	imshow("���1000����������+1000��������", noise);

	res1 = SelfAdaptMeanFilter(image);
	imshow("����Ӧ��ֵ�˲�", res1);

	res2 = noise.clone();
	meanFilter(res2, 7);
	imshow("7*7������ֵ�˲�", res2);
	
	waitKey(0); // Wait for a keystroke in the window
	destroyAllWindows();
}

void test4()
{
	Mat image, res1, res2, noise;
	image = imread("lena.jpg", 0); // Read the file
	imshow("ԭʼͼ��", image);

	noise = image.clone();
	addPepper(noise, 1000);
	Sleep(2000);
	addSalt(noise, 1000);
	imshow("���1000����������+1000��������", noise);

	res1 = SelfAdaptMedianFilter(image);
	imshow("����Ӧ��ֵ�˲�", res1);

	res2 = noise.clone();
	medeanFilter(res2, 7);
	imshow("7*7��ֵ�˲�", res2);

	waitKey(0); // Wait for a keystroke in the window
	destroyAllWindows();
}

void test5()
{
	Mat image, res1, res2, noise;
	image = imread("lena.jpg", 1); // Read the file
	imshow("ԭʼͼ��", image);

	noise = addGaussianNoise(image);
	imshow("��Ӹ�˹����", noise);

	res1 = noise.clone();
	meanFilter(res1, 5);					//������ֵ�˲���
	imshow("������ֵ�˲���", res1);

	res2 = GeometryMeanFilter(noise);
	imshow("���ξ�ֵ�˲���", res2);

	waitKey(0); // Wait for a keystroke in the window
	destroyAllWindows();

}
int main()
{	
	test1();
	test2();
	test3();
	test4();
	test5();
	destroyAllWindows();
	return 0;
}