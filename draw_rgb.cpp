#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;


int draw_rgb()
{
	Mat img = imread("color_chart.jpg");
	//namedWindow("image", WINDOW_NORMAL);
	int x = 30;
	int y = 200;
	
	Vec3b colour = img.at<Vec3b>(Point(x, y));
	string myText = "B:" + to_string(colour.val[0]) + " G:" + to_string(colour.val[1]) + " R:" + to_string(colour.val[2]);

	Scalar color = Scalar(0, 0, 0);
	circle(img, Point(x, y), 4, color, -1, 8, 0);
	putText(img, myText, Point(x+3, y), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 143, 143), 2);
	
	namedWindow("output", WINDOW_NORMAL);
	imshow("output", img);
	waitKey(0);
	return 0;
}
