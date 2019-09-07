#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;


int detect_color()
{
	Mat img = imread("blue_ball.jpg");
	//namedWindow("image", WINDOW_NORMAL);
	namedWindow("image", WINDOW_FREERATIO);
	imshow("image", img);
	waitKey(0);

	//get  the red color
	Mat outimg;
	//B G R
	inRange(img, Scalar(0, 0, 100), Scalar(100, 100, 255), outimg);

	//get  the blue color
	Mat outimg2;
	//B G R
	inRange(img, Scalar(100, 10, 10), Scalar(255, 100, 100), outimg2);

	int x1, x2;
	x1 = countNonZero(outimg);
	x2 = countNonZero(outimg2);
	namedWindow("output", WINDOW_FREERATIO);
	if (x1 > x2)
	{
		cout << "RED BALL";
		imshow("output", outimg);
	}
	else 
	{
		cout << "BLUE BALL";
		imshow("output", outimg2);
	}

	cout << x1 << "    " << x2;
	cout << outimg2;

	
	
	waitKey(0);
	return 0;
}
