// opencv_split_color.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int split_color()
{
	cout << "Hello World!\n";
	Mat img = imread("red_ball.jpg");
	//namedWindow("image", WINDOW_NORMAL);
	namedWindow("image", WINDOW_FREERATIO);
	imshow("image", img);
	waitKey(0);

	vector<Mat> BGR;
	split(img, BGR);

	namedWindow("blue", WINDOW_FREERATIO);
	namedWindow("green", WINDOW_FREERATIO);
	namedWindow("red", WINDOW_FREERATIO);

	imshow("blue", BGR[0]);
	imshow("green", BGR[1]);
	imshow("red", BGR[2]);

	waitKey(0);

	//return 0;
}
