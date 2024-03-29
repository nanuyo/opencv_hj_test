#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;


int detect_circle()
{
	Mat src, src_gray;
	src = imread("red_ball.jpg");
	/// Convert it to gray
	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	/// Reduce the noise so we avoid false circle detection
	GaussianBlur(src_gray, src_gray, Size(9, 9), 2, 2);

	vector<Vec3f> circles;

	/// Apply the Hough Transform to find the circles
	HoughCircles(src_gray, circles, HOUGH_GRADIENT, 1, src_gray.rows / 8, 200, 100, 0, 0);

	/// Draw the circles detected
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// circle center
		circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		// circle outline
		circle(src, center, radius, Scalar(0, 0, 255), 3, 8, 0);
		cout << circles[i][0] <<"\n";
		cout << circles[i][1] << "\n";
		cout << circles[i][2] << "\n";
		cout << center.x << "\n";
		cout << center.y << "\n";
		cout << radius << "\n";
	}

	/// Show your results
	namedWindow("Hough Circle Transform Demo", WINDOW_AUTOSIZE);
	imshow("Hough Circle Transform Demo", src);

	waitKey(0);
	return 0;
}
