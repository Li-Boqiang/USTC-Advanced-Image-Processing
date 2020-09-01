//ͼ��Ҷȱ任
#include<iostream>
#include<string>
#include<vector>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace std;
using namespace cv;

Mat equalize_hist(Mat& input)
{
	int gray[256] = { 0 };  //��¼ÿ���Ҷȼ����µ����ظ���
	double gray_prob[256] = { 0 };  //��¼�Ҷȷֲ��ܶ�
	double gray_distribution[256] = { 0 };  //��¼�ۼ��ܶ�
	int gray_equal[256] = { 0 };  //���⻯��ĻҶ�ֵ

	int gray_sum = 0;  //��������
	Mat output = input.clone();
	gray_sum = input.cols * input.rows;

	//ͳ��ÿ���Ҷ��µ����ظ���
	for (int i = 0; i < input.rows; i++)
	{
		uchar* p = input.ptr<uchar>(i);
		for (int j = 0; j < input.cols; j++)
		{
			int vaule = p[j];
			gray[vaule]++;
		}
	}
	//ͳ�ƻҶ�Ƶ��
	for (int i = 0; i < 256; i++)
	{
		gray_prob[i] = ((double)gray[i] / gray_sum);
	}

	//�����ۼ��ܶ�
	gray_distribution[0] = gray_prob[0];
	for (int i = 1; i < 256; i++)
	{
		gray_distribution[i] = gray_distribution[i - 1] + gray_prob[i];
	}

	//���¼�����⻯��ĻҶ�ֵ���������롣�ο���ʽ��(N-1)*T+0.5
	for (int i = 0; i < 256; i++)
	{
		gray_equal[i] = (uchar)(255 * gray_distribution[i] + 0.5);
	}


	//ֱ��ͼ���⻯,����ԭͼÿ���������ֵ
	for (int i = 0; i < output.rows; i++)
	{
		uchar* p = output.ptr<uchar>(i);
		for (int j = 0; j < output.cols; j++)
		{
			p[j] = gray_equal[p[j]];
		}
	}
	return output;
}

Mat color_equalize_hist(Mat input)
{
	vector<Mat> channels;
	split(input, channels);

	Mat B = channels.at(0);          //��vector�ж�������vector::at()
	Mat G = channels.at(1);
	Mat R = channels.at(2);

	B = equalize_hist(B);
	G = equalize_hist(G);
	R = equalize_hist(R);
	channels.clear();
	channels.push_back(B);
	channels.push_back(G);
	channels.push_back(R);

	Mat res;
	merge(channels, res);
	return res;
}

Mat grayHisTrans()
{
	Mat image = imread("lena.jpg", 0), res;
	namedWindow("ԭͼ��", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("ԭͼ��", image);

	res = image.clone();
	
	res = equalize_hist(image);
	//equalizeHist(res, res);
	namedWindow("�Ҷ�ֱ��ͼ����", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("�Ҷ�ֱ��ͼ����", res);
	waitKey(0);
	destroyAllWindows();
	return res;
}

int colorHisTrans()
{
	Mat image = imread("lena.jpg", IMREAD_COLOR), res;
	if (image.empty())
	{
		return -1;
	}
	namedWindow("ԭͼ��", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("ԭͼ��", image);

	vector<Mat> t;
	split(image, t);
	for (int i = 0; i < 3; i++)
	{
		t[i]=equalize_hist( t[i]);
	}
	merge(t, res);
	namedWindow("��ɫֱ��ͼ����", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("��ɫֱ��ͼ����", res);
	waitKey(0);
	destroyAllWindows();
	return 0;
}

int drawHisRGB()
{
	Mat image = imread("lena.jpg", IMREAD_COLOR);
	namedWindow("ԭͼ��", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("ԭͼ��", image);
	int bins = 256;

	int hist_size[] = { bins };
	float range[] = { 0, 256 };
	const float* ranges[] = { range };

	MatND hist_r, hist_g, hist_b;
	int channels_r[] = { 0 };
	calcHist(&image, 1, channels_r, Mat(), // do not use mask
		hist_r, 1, hist_size, ranges,
		true, // the histogram is uniform
		false);

	int channels_g[] = { 1 };
	calcHist(&image, 1, channels_g, Mat(), // do not use mask
		hist_g, 1, hist_size, ranges,
		true, // the histogram is uniform
		false);

	int channels_b[] = { 2 };
	calcHist(&image, 1, channels_b, Mat(), // do not use mask
		hist_b, 1, hist_size, ranges,
		true, // the histogram is uniform
		false);

	double max_val_r, max_val_g, max_val_b;
	minMaxLoc(hist_r, 0, &max_val_r, 0, 0);
	minMaxLoc(hist_g, 0, &max_val_g, 0, 0);
	minMaxLoc(hist_b, 0, &max_val_b, 0, 0);
	int scale = 1;

	int hist_height = 256;
	Mat colorHis = Mat::zeros(hist_height, bins * 3, CV_8UC3);
	for (int i = 0; i < bins; i++)
	{
		float bin_val_r = hist_r.at<float>(i);
		float bin_val_g = hist_g.at<float>(i);
		float bin_val_b = hist_b.at<float>(i);
		int intensity_r = cvRound(bin_val_r*hist_height / max_val_r);  //Ҫ���Ƶĸ߶�
		int intensity_g = cvRound(bin_val_g*hist_height / max_val_g);  //Ҫ���Ƶĸ߶�
		int intensity_b = cvRound(bin_val_b*hist_height / max_val_b);  //Ҫ���Ƶĸ߶�
		rectangle(colorHis, Point(i*scale, hist_height - 1),
			Point((i + 1)*scale - 1, hist_height - intensity_r),
			CV_RGB(255, 0, 0));

		rectangle(colorHis, Point((i + bins)*scale, hist_height - 1),
			Point((i + bins + 1)*scale - 1, hist_height - intensity_g),
			CV_RGB(0, 255, 0));

		rectangle(colorHis, Point((i + bins * 2)*scale, hist_height - 1),
			Point((i + bins * 2 + 1)*scale - 1, hist_height - intensity_b),
			CV_RGB(0, 0, 255));

	}
	namedWindow("��ɫֱ��ͼ", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("��ɫֱ��ͼ", colorHis);
	waitKey(0);
	destroyAllWindows();
	return 0;

}

int drawHisGray(Mat image)
{
	imshow("ԭͼ��", image);
	int bins = 256;

	int hist_size[] = { bins };
	float range[] = { 0, 256 };
	const float* ranges[] = { range };

	MatND hist;
	int channels[] = { 0 };
	calcHist(&image, 1, channels, Mat(), // do not use mask
		hist, 1, hist_size, ranges,
		true, // the histogram is uniform
		false);

	double max_val;
	minMaxLoc(hist, 0, &max_val, 0, 0);

	int scale = 2;
	int hist_height = 256;
	Mat hist_img = Mat::zeros(hist_height, bins*scale, CV_8UC3);
	for (int i = 0; i < bins; i++)
	{
		float bin_val = hist.at<float>(i);
		int intensity = cvRound(bin_val*hist_height / max_val);  //Ҫ���Ƶĸ߶�
		rectangle(hist_img, Point(i*scale, hist_height - 1),
			Point((i + 1)*scale - 1, hist_height - intensity),
			CV_RGB(255, 255, 255));
	}

	namedWindow("�Ҷ�ֱ��ͼ", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("�Ҷ�ֱ��ͼ", hist_img);
	waitKey(0);
	destroyAllWindows();
	return 0;
}

int drawHis2D()
{
	Mat image = imread("lena.jpg", 1);
	namedWindow("ԭͼ��", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("ԭͼ��", image);

	int hbins = 256, sbins = 256;
	int histSize[] = { hbins, sbins };

	float hranges[] = { 0, 256 };
	float sranges[] = { 0, 256 };
	const float* ranges[] = { hranges, sranges };
	MatND hist;

	int channels[] = { 0, 1 };
	calcHist(&image, 1, channels, Mat(), // do not use mask
		hist, 2, histSize, ranges,
		true, // the histogram is uniform
		false);
	double maxVal = 0;
	minMaxLoc(hist, 0, &maxVal, 0, 0);
	int scale = 2;
	Mat histImg = Mat::zeros(sbins*scale, hbins*scale, CV_8UC3);
	for (int h = 0; h < hbins; h++)
		for (int s = 0; s < sbins; s++)
		{
			float binVal = hist.at<float>(h, s);
			int intensity = cvRound(binVal * 255 / maxVal);
			rectangle(histImg, Point(h*scale, s*scale),
				Point((h + 1)*scale - 1, (s + 1)*scale - 1),
				Scalar::all(intensity),
				FILLED);
		}
	namedWindow("��άֱ��ͼ", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("��άֱ��ͼ", histImg);
	waitKey(0);
	destroyAllWindows();
	return 0;
}



void test1()
{
	Mat image = imread("lena.jpg", 0);
	drawHisGray(image);
	drawHisRGB();
	drawHis2D();
	return;
}

void test2()
{
	Mat image = imread("lena.jpg", 0), res;
	drawHisGray(image);
	res = grayHisTrans();
	drawHisGray(res);
	return;
}
void test3()
{
	colorHisTrans();
	return;
}

int main()
{
	test1();
	test2();
	test3();
	return 0;
}