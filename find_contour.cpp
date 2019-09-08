#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

Mat src_gray;
int thresh = 100;
RNG rng(12345);
void thresh_callback(int, void*);


int find_contour()
{
	
	Mat img1 = imread("color_chart.jpg");
	
	if (img1.empty())
	{
		cout << "Could not open or find the image!\n" << endl;
		return -1;
	}

	cvtColor(img1, src_gray, COLOR_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3));
	const char* source_window = "Source";
	namedWindow(source_window);
	imshow(source_window, img1);
	const int max_thresh = 255;
	createTrackbar("Canny thresh:", source_window, &thresh, max_thresh, thresh_callback);
	thresh_callback(0, 0);
	waitKey();
	return 0;
}

void thresh_callback(int, void*)
{
	Mat canny_output;
	Canny(src_gray, canny_output, thresh, thresh * 2);
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	// draw contours
	//Mat drawing(canny_output.size(), CV_8UC3, Scalar(255, 255, 255));
	// get the moments
	vector<Moments> mu(contours.size());
	// get the centroid of figures.
	vector<Point2f> mc(contours.size());

	putText(drawing, "HJ Park", Point(100, 100), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 143, 143), 2);

	for (size_t i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
		
		mu[i] = moments(contours[i], false);
		mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
		circle(drawing, mc[i], 4, color, -1, 8, 0);
	
	}
	
	imshow("Contours", drawing);
}