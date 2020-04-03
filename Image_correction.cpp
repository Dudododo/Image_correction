#include <iostream>
#include <opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	cv::Mat srcMat = imread("lena_rot.jpg", 1);
	cv::Mat grayMat = imread("lena_rot.jpg", 0);
	cv::Mat dstMat;

	int height = grayMat.rows;
	int width = grayMat.cols;
	int x1, y1, x2, y2, x3, y3, x4, y4 = 0;
	for (int j = 0; j < height; j++) 
	{
		for (int i = 0; i < width; i++) 
		{
			if (j == 0 && grayMat.at<uchar>(j, i) < 240)
			{
				x1 = j;
				y1 = i;
			}
			if (i == width - 1 && grayMat.at<uchar>(j, i) < 240) 
			{
				x2 = j;
				y2 = i;
			}
			if (i == 0 && grayMat.at<uchar>(j, i) < 240) 
			{
				x3 = j;
				y3 = i;
			}
			if (i == 0 && grayMat.at<uchar>(j, i) < 240)
			{
				x3 = j;
				y3 = i;
			}
			if (j == height - 1 && grayMat.at<uchar>(j, i) < 240) 
			{
				x4 = j;
				y4 = i;
			}
		}
	}

	cout << x1 << " " << y1 << endl;
	cout << x2 << " " << y2 << endl;
	cout << x3 << " " << y3 << endl;
	cout << x4 << " " << y4 << endl;


	//变换前的四点坐标
	cv::Point2f pts1[] = {
		cv::Point2f(y1,x1),
		cv::Point2f(y2,x2),
		cv::Point2f(y3,x3),
		cv::Point2f(y4,x4)
	};

	//变换后的四点坐标
	cv::Point2f pts2[] = {
		cv::Point2f(0,0),
		cv::Point2f(width - 1,0),
		cv::Point2f(0,height - 1),
		cv::Point2f(width - 1,height - 1)
	};

	//计算仿射矩阵
	cv::Mat perspective_matrix = cv::getPerspectiveTransform(pts1, pts2);

	cv::warpPerspective(srcMat, dstMat, perspective_matrix, srcMat.size());
	cv::imshow("srcMat", srcMat);
	cv::imshow("dstMat", dstMat);
	waitKey(0);
}
