//�����˲�
#include<iostream>
#include<string>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/core/core_c.h>

using namespace std;
using namespace cv;
int MeanFilter_Gray(int a,int b)
{
	Mat image, meanRes;
	image = imread("lena.jpg", 0); // Read the file
	namedWindow("ԭͼ", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("ԭͼ", image);                // Show our image inside it.

	blur(image, meanRes, Size(a, b));			//��ֵ�˲�

	namedWindow("��ֵ�˲�", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("��ֵ�˲�", meanRes);                // Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window
	destroyAllWindows();
	return 0;
}

int MeanFilter_Color(int a, int b)
{
	Mat image, meanRes;
	image = imread("lena.jpg", 1); // Read the file
	namedWindow("ԭͼ", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("ԭͼ", image);                // Show our image inside it.

	blur(image, meanRes, Size(a, b));			//��ֵ�˲�

	namedWindow("��ֵ�˲�", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("��ֵ�˲�", meanRes);                // Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window
	destroyAllWindows();
	return 0;
}

int GaussianFilter_Gray(int a, int b)
{
	Mat image, res;
	image = imread("lena.jpg", 0); // Read the file
	namedWindow("ԭͼ", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("ԭͼ", image);                // Show our image inside it.

	GaussianBlur(image, res, Size(a, b), 1);

	namedWindow("��˹�˲�", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("��˹�˲�", res);                // Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window
	destroyAllWindows();
	return 0;
}

int GaussianFilter_Color(int a, int b)
{
	Mat image, res;
	image = imread("lena.jpg", 1); // Read the file
	namedWindow("ԭͼ", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("ԭͼ", image);                // Show our image inside it.

	GaussianBlur(image, res, Size(a, b), 1);

	namedWindow("��˹�˲�", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("��˹�˲�", res);                // Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window
	destroyAllWindows();
	return 0;
}


int Sobel()
{
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;
	Mat image, res;
	image = imread("lena.jpg", 0); // Read the file
	namedWindow("ԭͼ", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("ԭͼ", image);                // Show our image inside it.

	Sobel(image, grad_x, image.depth(), 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	imshow("��Ч��ͼ�� X����Sobel", abs_grad_x);

	Sobel(image, grad_y, image.depth(), 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("��Ч��ͼ��Y����Sobel", abs_grad_y);

	//��5���ϲ��ݶ�(����)
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, res);
	imshow("��Ч��ͼ�����巽��Sobel", res);

	waitKey(0); // Wait for a keystroke in the window
	destroyAllWindows();
	return 0;
}

int Sobel_Color()
{
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;
	Mat image, res;
	image = imread("lena.jpg", 1); // Read the file
	namedWindow("ԭͼ", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("ԭͼ", image);                // Show our image inside it.

	Sobel(image, grad_x, image.depth(), 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	imshow("��Ч��ͼ�� X����Sobel", abs_grad_x);

	Sobel(image, grad_y, image.depth(), 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("��Ч��ͼ��Y����Sobel", abs_grad_y);

	//��5���ϲ��ݶ�(����)
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, res);
	imshow("��Ч��ͼ�����巽��Sobel", res);

	waitKey(0); // Wait for a keystroke in the window
	destroyAllWindows();
	return 0;
}

//������˹ģ��
int Laplacian_Color()
{
	Mat image, res;
	image = imread("lena.jpg", IMREAD_COLOR); // Read the file
	namedWindow("ԭͼ", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("ԭͼ", image);                // Show our image inside it.
	
	Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(image, res, image.depth(), kernel);

	namedWindow("������˹ģ��", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("������˹ģ��", res);                // Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window
	destroyAllWindows();
	return 0;
}

int Laplacian_Gray()
{
	Mat image, res;
	image = imread("lena.jpg", 0); // Read the file
	namedWindow("ԭͼ", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("ԭͼ", image);                // Show our image inside it.

	Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(image, res, image.depth(), kernel);

	namedWindow("������˹ģ��", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("������˹ģ��", res);                // Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window
	destroyAllWindows();
	return 0;
}


int Lap2()
{
	Mat image, res;
	image = imread("lena.jpg", IMREAD_COLOR); // Read the file
	namedWindow("ԭͼ", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("ԭͼ", image);                // Show our image inside it.

	res.create(image.size(), image.type());//Ϊ���ͼ���������

		/*������˹�˲���3*3
		 0  -1   0
		-1   5  -1
		 0  -1   0  */
		 //���������ΧһȦ�����������ֵ

	for (int i = 1; i < image.rows - 1; i++)
	{
		const uchar * pre = image.ptr<const uchar>(i - 1);//ǰһ��
		const uchar * cur = image.ptr<const uchar>(i);//��ǰ�У���i��
		const uchar * next = image.ptr<const uchar>(i + 1);//��һ��
		uchar * output = res.ptr<uchar>(i);//���ͼ��ĵ�i��
		int ch = image.channels();//ͨ������
		int startCol = ch;//ÿһ�еĿ�ʼ�����
		int endCol = (image.cols - 1)* ch;//ÿһ�еĴ��������
		for (int j = startCol; j < endCol; j++)
		{
			//���ͼ��ı���ָ���뵱ǰ�е�ָ��ͬ������, ��ÿ�е�ÿһ�����ص��ÿһ��ͨ��ֵΪһ��������, ��ΪҪ

			//���ǵ�ͼ���ͨ����
				//saturate_cast<uchar>��֤�����uchar��Χ��
				*output++ = saturate_cast<uchar>(5 * cur[j] - pre[j] - next[j] - cur[j - ch] - cur[j + ch]);
		}
	}
	//������ΧһȦ������ֵ��Ϊ0
	res.row(0).setTo(Scalar(0));
	res.row(res.rows - 1).setTo(Scalar(0));
	res.col(0).setTo(Scalar(0));
	res.col(res.cols - 1).setTo(Scalar(0));
	/*/����Ҳ���Գ��Խ�����ΧһȦ����Ϊԭͼ������ֵ
	image.row(0).copyTo(result.row(0));
	image.row(image.rows-1).copyTo(result.row(result.rows-1));
	image.col(0).copyTo(result.col(0));
	image.col(image.cols-1).copyTo(result.col(result.cols-1));*/
	namedWindow("������˹ģ��-��д", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("������˹ģ��-��д", res);                // Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window
	destroyAllWindows();
	return 0;
}

int Robert_RGB()
{
	Mat image, res;
	image = imread("lena.jpg", 1); // Read the file
	namedWindow("ԭͼ", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("ԭͼ", image);                // Show our image inside it.

	res = image.clone();

	CvScalar t1, t2, t3, t4, t;
	IplImage res2 = IplImage(image);

	for (int i = 0; i < res2.height-1; i++)
	{
		for (int j = 0; j < res2.width-1; j++)
		{
			t1 = cvGet2D(&res2, i, j);
			t2 = cvGet2D(&res2, i+1, j+1);
			t3 = cvGet2D(&res2, i, j + 1);
			t4 = cvGet2D(&res2, i + 1, j);


			for (int k = 0; k < 3; k++)
			{
				int t7 = (t1.val[k] - t2.val[k])*(t1.val[k] - t2.val[k])+ (t4.val[k] - t3.val[k])*(t4.val[k] - t3.val[k]);
				t.val[k] = sqrt(t7);
			}
			cvSet2D(&res2, i, j, t);
		}
	}
	res = cvarrToMat(&res2);
	namedWindow("Robert_RGB�˲�", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Robert_RGB�˲�", res);                // Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window
	destroyAllWindows();
	return 0;
}

int Robert_G()
{
	Mat image, res;
	image = imread("lena.jpg", 0); // Read the file
	namedWindow("ԭͼ", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("ԭͼ", image);                // Show our image inside it.
	res = image.clone();

	for (int i = 0; i < image.rows - 1; i++) {
		for (int j = 0; j < image.cols - 1; j++) {
		//���ݹ�ʽ����
		int t1 = (image.at<uchar>(i, j) -
			image.at<uchar>(i + 1, j + 1))*
			(image.at<uchar>(i, j) -
				image.at<uchar>(i + 1, j + 1));
		int t2 = (image.at<uchar>(i + 1, j) -
			image.at<uchar>(i, j + 1))*
			(image.at<uchar>(i + 1, j) -
				image.at<uchar>(i, j + 1));
		//����g��x,y��
		res.at<uchar>(i, j) = (uchar)sqrt(t1 + t2);
		}
	}

	namedWindow("Robert_G�˲�", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Robert_G�˲�", res);                // Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window
	destroyAllWindows();
	return 0;

}


void EnhanceFilter(Mat img, Mat &dst, double dProportion, int nTempH, int nTempW, int nTempMY, int nTempMX, float *pfArray, float fCoef)
{
	

	int i, j, nHeight = img.rows, nWidth = img.cols;
	vector<vector<int>> GrayMat1, GrayMat2, GrayMat3;//�ݴ水��������ͼ��R,G,B��ͨ��
	vector<int> vecRow1(nWidth, 0), vecRow2(nWidth, 0), vecRow3(nWidth, 0);
	for (i = 0; i < nHeight; i++)
	{
		GrayMat1.push_back(vecRow1);
		GrayMat2.push_back(vecRow2);
		GrayMat3.push_back(vecRow3);
	}

	//��ͼ�������������Ӧ������ԭͼ�񰴱�������
	for (i = nTempMY; i < nHeight - (nTempH - nTempMY) + 1; i++)
	{
		for (j = nTempMX; j < nWidth - (nTempW - nTempMX) + 1; j++)
		{
			float fResult1 = 0;
			float fResult2 = 0;
			float fResult3 = 0;
			for (int k = 0; k < nTempH; k++)
			{
				for (int l = 0; l < nTempW; l++)
				{
					//�ֱ������ͨ����Ȩ��
					fResult1 += img.at<Vec3b>(i, j)[0] * pfArray[k*nTempW + 1];
					fResult2 += img.at<Vec3b>(i, j)[1] * pfArray[k*nTempW + 1];
					fResult3 += img.at<Vec3b>(i, j)[2] * pfArray[k*nTempW + 1];
				}
			}

			//��ͨ����Ȩ�ͷֱ����ϵ����������Ӧ��Χ������ԭͼ�񰴱������
			fResult1 *= fCoef;
			if (fResult1 > 255)
				fResult1 = 255;
			if (fResult1 < -255)
				fResult1 = -255;
			GrayMat1[i][j] = dProportion * img.at<Vec3b>(i, j)[0] + fResult1 + 0.5;

			fResult2 *= fCoef;
			if (fResult2 > 255)
				fResult2 = 255;
			if (fResult2 < -255)
				fResult2 = -255;
			GrayMat2[i][j] = dProportion * img.at<Vec3b>(i, j)[1] + fResult2 + 0.5;

			fResult3 *= fCoef;
			if (fResult3 > 255)
				fResult3 = 255;
			if (fResult3 < -255)
				fResult3 = -255;
			GrayMat3[i][j] = dProportion * img.at<Vec3b>(i, j)[2] + fResult3 + 0.5;
		}
	}
	int nMax1 = 0, nMax2 = 0, nMax3 = 0;//��ͨ�����ҶȺ�ֵ
	int nMin1 = 65535, nMin2 = 65535, nMin3 = 65535;//��ͨ����С�ҶȺ�ֵ
	//�ֱ�ͳ����ͨ�����ֵ��Сֵ
	for (i = nTempMY; i < nHeight - (nTempH - nTempMY) + 1; i++)
	{
		for (j = nTempMX; j < nWidth - (nTempW - nTempMX) + 1; j++)
		{
			if (GrayMat1[i][j] > nMax1)
				nMax1 = GrayMat1[i][j];
			if (GrayMat1[i][j] < nMin1)
				nMin1 = GrayMat1[i][j];

			if (GrayMat2[i][j] > nMax2)
				nMax2 = GrayMat2[i][j];
			if (GrayMat2[i][j] < nMin2)
				nMin2 = GrayMat2[i][j];

			if (GrayMat3[i][j] > nMax3)
				nMax3 = GrayMat3[i][j];
			if (GrayMat3[i][j] < nMin3)
				nMin3 = GrayMat3[i][j];
		}
	}
	//�����������Ӻ����ͨ��ͼ��ȡֵ��Χ���¹�һ����[0,255]
	int nSpan1 = nMax1 - nMin1, nSpan2 = nMax2 - nMin2, nSpan3 = nMax3 - nMin3;
	for (i = nTempMY; i < nHeight - (nTempH - nTempMY) + 1; i++)
	{
		for (j = nTempMX; j < nWidth - (nTempW - nTempMX) + 1; j++)
		{
			int br, bg, bb;
			if (nSpan1 > 0)
				br = (GrayMat1[i][j] - nMin1) * 255 / nSpan1;
			else if (GrayMat1[i][j] <= 255)
				br = GrayMat1[i][j];
			else
				br = 255;
			dst.at<Vec3b>(i, j)[0] = br;

			if (nSpan2 > 0)
				bg = (GrayMat2[i][j] - nMin2) * 255 / nSpan2;
			else if (GrayMat2[i][j] <= 255)
				bg = GrayMat2[i][j];
			else
				bg = 255;
			dst.at<Vec3b>(i, j)[1] = bg;

			if (nSpan3 > 0)
				bb = (GrayMat3[i][j] - nMin3) * 255 / nSpan3;
			else if (GrayMat3[i][j] <= 255)
				bb = GrayMat3[i][j];
			else
				bb = 255;
			dst.at<Vec3b>(i, j)[2] = bb;
		}
	}
}

void test4()
{
	Mat img = imread("lena.jpg");
	imshow("ԭͼ", img);
	Mat dst = img.clone();
	//�����˲�ģ������
//ƽ��ƽ��1/9
	float Template_Smooth_Avg[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	//Gaussƽ��1/16
	float Template_Smooth_Gauss[9] = { 1, 2, 1, 2, 4, 2, 1, 2, 1 };
	//Sobel��ֱ��Ե���
	float Template_Smooth_HSobel[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
	//Sobelˮƽ��Ե���
	float Template_Smooth_VSobel[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
	//LOG��Ե���
	float Template_Log[25] = { 0, 0, -1, 0, 0, 0, -1, -2, -1, 0, -1, -2, 16, -2, -1, 0, -1, -2, -1, 0, 0, 0, -1, 0, 0 };
	//Laplacian��Ե���
	float Template_Laplacian1[9] = { 0, -1, 0, -1, 4, -1, 0, -1, 0 };//��90�ȸ���ͬ��
	float Template_Laplacian2[9] = { -1, -1, -1, -1, 8, -1, -1, -1, -1 };//��45�ȸ���ͬ��
	/*************************************************************************************************************
	�������˲�
	dProportion���������˲���ԭͼ��Ļ�ϱ���
	nTempH��ģ��߶ȣ�nTempW��ģ����
	nTempMY��ģ������Ԫ�����꣬nTempMX��ģ������Ԫ������
	fpArray��ָ��ģ�������ָ�룬����ѡȡ��ͬģ��ʵ�ֲ�ͬ�˲��ĸ������汾
	fCoef��ģ��ϵ��
	**************************************************************************************************************/
	EnhanceFilter(img, dst, 1.8, 3, 3, 1, 1, Template_Laplacian2, 1);

	imshow("������Laplacian", dst);
	waitKey(0);
	destroyAllWindows();
	return;
}


int main()
{
	
	MeanFilter_Gray(3,3);
	MeanFilter_Gray(5, 5);
	MeanFilter_Gray(9, 9);
	GaussianFilter_Gray(3,3);
	GaussianFilter_Gray(5, 5);
	GaussianFilter_Gray(9, 9);
	Laplacian_Gray();
	Robert_G();
	Sobel();
	test4();
	MeanFilter_Color(3, 3);
	MeanFilter_Color(5, 5);
	MeanFilter_Color(9, 9);
	GaussianFilter_Color(3, 3);
	GaussianFilter_Color(5, 5);
	GaussianFilter_Color(9, 9);
	Lap2();
	Laplacian_Color();
	Robert_RGB();
	Sobel_Color();
	return 0;
}