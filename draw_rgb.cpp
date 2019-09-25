#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;


int draw_rgb()
{
#if 1
	Mat frame;
	VideoCapture cap;
	// open the default camera using default API
	// cap.open(0);
	// OR advance usage: select any API backend
	int deviceID = 0;             // 0 = open default camera
	int apiID = cv::CAP_ANY;      // 0 = autodetect default API
	// open selected camera using selected API
	cap.open(deviceID + apiID);
	// check if we succeeded
	if (!cap.isOpened()) {
		cerr << "ERROR! Unable to open camera\n";
		return -1;
	}

	//--- GRAB AND WRITE LOOP
	cout << "Start grabbing" << endl
		<< "Press any key to terminate" << endl;
	for (;;)
	{
		// wait for a new frame from camera and store it into 'frame'
		cap.read(frame);
		// check if we succeeded
		if (frame.empty()) {
			cerr << "ERROR! blank frame grabbed\n";
			break;
		}
		// show live and wait for a key with timeout long enough to show images
		imshow("Live", frame);
		if (waitKey(5) >= 0)
			break;
	}

	imwrite("image.png", frame);
#endif
	//Mat img = imread("RGBTest.jpg");
	Mat img = imread("image.png");

	//namedWindow("image", WINDOW_NORMAL);
	cout << img.cols << " x " << img.rows;
#define R1_MAX 255
#define R1_MIN 200
#define G1_MAX 150
#define G1_MIN 10
#define B1_MAX 100
#define B1_MIN 10

#define R2_MAX 150
#define R2_MIN 10
#define G2_MAX 255
#define G2_MIN 200
#define B2_MAX 100
#define B2_MIN 10

#define R3_MAX 150
#define R3_MIN 10
#define G3_MAX 230
#define G3_MIN 10
#define B3_MAX 255
#define B3_MIN 100


	Vec3b colour[3];
	Vec3b colour_max[3];
	Vec3b colour_min[3];

	colour_max[0].val[2] = R1_MAX;
	colour_max[0].val[1] = G1_MAX;
	colour_max[0].val[0] = B1_MAX;

	colour_max[1].val[2] = R2_MAX;
	colour_max[1].val[1] = G2_MAX;
	colour_max[1].val[0] = B2_MAX;

	colour_max[2].val[2] = R3_MAX;
	colour_max[2].val[1] = G3_MAX;
	colour_max[2].val[0] = B3_MAX;

	colour_min[0].val[2] = R1_MIN;
	colour_min[0].val[1] = G1_MIN;
	colour_min[0].val[0] = B1_MIN;

	colour_min[1].val[2] = R2_MIN;
	colour_min[1].val[1] = G2_MIN;
	colour_min[1].val[0] = B2_MIN;

	colour_min[2].val[2] = R3_MIN;
	colour_min[2].val[1] = G3_MIN;
	colour_min[2].val[0] = B3_MIN;

	string myText;
	int x;
	char okfailflag[3] = { 0, };

#define RL_DIST 150

	for (int i = 0; i < 3; i++)
	{
		if(i == 0)
			x = img.cols / 2 - RL_DIST;
		else if (i == 1)
			x = img.cols / 2 ;
		else if (i == 2)
			x = img.cols / 2 + RL_DIST;

		int y = img.rows / 2;

		colour[i] = img.at<Vec3b>(Point(x, y));

#if 1


//		myText = "OK R:" + to_string(colour[i].val[2]) + " G:" + to_string(colour[i].val[1]) + " B:" + to_string(colour[i].val[0]);
		myText = "OK";



		if ((colour[i].val[2] > colour_max[i].val[2]) || (colour[i].val[2] < colour_min[i].val[2]))
			okfailflag[i] = 1;

		if ((colour[i].val[1] > colour_max[i].val[1]) || (colour[i].val[1] < colour_min[i].val[1]))
			okfailflag[i] = 1;

		if ((colour[i].val[0] > colour_max[i].val[0]) || (colour[i].val[0] < colour_min[i].val[0]))
			okfailflag[i] = 1;
			
		if(okfailflag[i])
//			myText = "Fail  R:" + to_string(colour[i].val[2]) + " G:" + to_string(colour[i].val[1]) + " B:" + to_string(colour[i].val[0]);
			myText = "Fail";

			
#else	
		myText = "*Fail*  R:" + to_string(colour[i].val[2]) + " G:" + to_string(colour[i].val[1]) + " B:" + to_string(colour[i].val[0]);

		if( (colour[i].val[2] <= colour_max[i].val[2]) && (colour[i].val[2] >= colour_min[i].val[2]) )
			if ((colour[i].val[1] <= colour_max[i].val[1]) && (colour[i].val[1] >= colour_min[i].val[1]))
				if ((colour[i].val[0] <= colour_max[i].val[0]) && (colour[i].val[0] >= colour_min[i].val[0]))
					myText = "*OK* R:" + to_string(colour[i].val[2]) + " G:" + to_string(colour[i].val[1]) + " B:" + to_string(colour[i].val[0]);
					
#endif

		Scalar color = Scalar(0, 0, 0);
		circle(img, Point(x, y), 4, color, -1, 8, 0);
#define L_DIST 30
#define T_R 0
#define T_G 0
#define T_B 0
#define T_SCALE 1
#define T_THICK 1

		if(i==0)
			putText(img, myText, Point(x - L_DIST, y - 25), FONT_HERSHEY_DUPLEX, T_SCALE, Scalar(T_B, T_G, T_R), T_THICK);
		else if(i==1)
			putText(img, myText, Point(x - L_DIST, y + 40), FONT_HERSHEY_DUPLEX, T_SCALE, Scalar(T_B, T_G, T_R), T_THICK);
		else
			putText(img, myText, Point(x + L_DIST, y ), FONT_HERSHEY_DUPLEX, T_SCALE, Scalar(T_B, T_G, T_R), T_THICK);
	}


	if(okfailflag[0] || okfailflag[1] || okfailflag[2])
	{
		myText = "FAIL";
		putText(img, myText, Point(img.cols / 2 - 200, 200), FONT_HERSHEY_DUPLEX, T_SCALE+5, Scalar(0, 0, 255), T_THICK+3);
	}
	else
	{
		myText = "OK";
		putText(img, myText, Point(img.cols / 2 - 120, 200), FONT_HERSHEY_DUPLEX, T_SCALE+5, Scalar(0, 0, 0), T_THICK+3);
	}

	

	
	
	
	//namedWindow("output", WINDOW_NORMAL);
	resizeWindow("output", 600,600);
	imshow("output", img);
	waitKey(0);
	return 0;
}
