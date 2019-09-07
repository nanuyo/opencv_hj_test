#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;


float calcBlurriness(const Mat& src)
{
	Mat Gx, Gy;
	Sobel(src, Gx, CV_32F, 1, 0);
	Sobel(src, Gy, CV_32F, 0, 1);
	double normGx = norm(Gx);
	double normGy = norm(Gy);
	double sumSq = normGx * normGx + normGy * normGy;
	return static_cast<float>(1. / (sumSq / src.size().area() + 1e-6));
}

int blur_detect()
{
	Mat src = imread("lena.jpg");
	if (src.empty())
	{
		cout << "Error loading image file" << endl;
		return -1;
	}

	if (src.data)
	{
		//(the lesser value means more sharpness)
		std::cout << "original image : " << calcBlurriness(src) << std::endl;

		for (int i = 3; i < 80; i += 2)
		{
			Mat blurred;
			GaussianBlur(src, blurred, Size(i, i), 0);
			imshow("blurred image", blurred);
			waitKey(200);
			std::cout << "blurred image  : " << calcBlurriness(blurred) << std::endl;
		}
	}
	return 0;
}
