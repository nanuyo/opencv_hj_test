#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace std;
using namespace cv;
//#pragma comment(lib, "opencv_world331.lib")



int find_particle(void)
{
	Mat frame = imread("particles.bmp", IMREAD_GRAYSCALE);

	if (frame.empty())
	{
		cout << "Error loading image file" << endl;
		return -1;
	}

	threshold(frame, frame, 127, 255, THRESH_BINARY);

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	findContours(frame, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<double> areas(contours.size());

	for (int i = 0; i < contours.size(); i++)
		areas[i] = contourArea(contours[i]);

	vector<Point2d> mass_centres(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		const Moments mu = moments(contours[i], false);
		mass_centres[i] = Point2d(mu.m10 / mu.m00, mu.m01 / mu.m00);
	}

	cout << "Num particles: " << contours.size() << endl;

	for (int i = 0; i < contours.size(); i++)
		cout << "area " << (i + 1) << ": " << areas[i] << endl;

	for (int i = 0; i < contours.size(); i++)
		cout << "centre " << (i + 1) << ": " << mass_centres[i].x << " " << mass_centres[i].y << endl;

	return 0;
}