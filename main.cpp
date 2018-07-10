
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
using namespace std;
using namespace cv;
#define  PI 3.14159


Mat cylinder(Mat src) {

	
	Mat img_result = src.clone();
	for (int i = 0; i<img_result.rows; i++)
	{
		for (int j = 0; j<img_result.cols; j++)
		{
			img_result.at<Vec3b>(i, j) = 0;
		}
	}
	int W = src.cols;
	int H = src.rows;
	float r = W / (2 * tan(PI / 6));
	float k = 0;
	float fx = 0;
	float fy = 0;
	for (int i = 0; i<src.rows; i++)
	{
		for (int j = 0; j<src.cols; j++)
		{
			k = sqrt((float)(r*r + (W / 2 - j)*(W / 2 - j)));
			fx = r*sin(PI / 6) + r*sin(atan((j - W / 2) / r));
			fy = H / 2 + r*(i - H / 2) / k;
			int ix = (int)fx;
			int iy = (int)fy;
			if (ix<W&&ix >= 0 && iy<H&&iy >= 0)
			{
				img_result.at<Vec3b>(iy, ix) = src.at<Vec3b>(i, j);
			}

		}
	}

	return img_result;

}


int main(int argc, char** argv)
{
	Mat img_1 = imread("D:/pictures/pic.jpg");
	namedWindow("桶狀投影",0);
	imshow("桶狀投影", cylinder(img_1));
	waitKey(0);
	destroyWindow("桶狀投影");
	return 0;
}