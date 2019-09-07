#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;


int change_color()
{
	Mat img = imread("red_ball.jpg");
	//namedWindow("image", WINDOW_NORMAL);
	namedWindow("image", WINDOW_FREERATIO);
	imshow("image", img);
	waitKey(0);

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			if ((img.at<Vec3b>(i, j)[0] == 255) && (img.at<Vec3b>(i, j)[1] = 255) && (img.at<Vec3b>(i, j)[2] == 255))
			{
				img.at<Vec3b>(i, j)[0] = 0; //blue
				img.at<Vec3b>(i, j)[1] = 0; //green
				img.at<Vec3b>(i, j)[2] = 0; //red
			}
		}
	}

	namedWindow("output", WINDOW_FREERATIO);
	imshow("output", img);
	waitKey(0);
	return 0;
}
