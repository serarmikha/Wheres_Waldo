#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>

using namespace cv;

const std::string TRACKBARWINDOWNAME = "Trackbars";

//changed values for trackbars
int H_MIN = 160;
int H_MAX = 179;
int S_MIN = 100;
int S_MAX = 255;
int V_MIN = 100;
int V_MAX = 255;

void on_trackbar(int, void*)
{//This function gets called whenever a
 // trackbar position is changed
}

//from: https://raw.githubusercontent.com/kylehounslow/opencv-tuts/master/object-tracking-tut/objectTrackingTut.cpp
void createTrackbars() 
{
	//create window for trackbars


	namedWindow(TRACKBARWINDOWNAME, 0);
	//create memory to store trackbar name on window
	char TrackbarName[50];
	sprintf(TrackbarName, "H_MIN", H_MIN);
	sprintf(TrackbarName, "H_MAX", H_MAX);
	sprintf(TrackbarName, "S_MIN", S_MIN);
	sprintf(TrackbarName, "S_MAX", S_MAX);
	sprintf(TrackbarName, "V_MIN", V_MIN);
	sprintf(TrackbarName, "V_MAX", V_MAX);
	//create trackbars and insert them into window
	//3 parameters are: the address of the variable that is changing when the trackbar is moved(eg.H_LOW),
	//the max value the trackbar can move (eg. H_HIGH), 
	//and the function that is called whenever the trackbar is moved(eg. on_trackbar)
	//                                  ---->    ---->     ---->      
	createTrackbar("H_MIN", TRACKBARWINDOWNAME, &H_MIN, H_MAX, on_trackbar);
	createTrackbar("H_MAX", TRACKBARWINDOWNAME, &H_MAX, H_MAX, on_trackbar);
	createTrackbar("S_MIN", TRACKBARWINDOWNAME, &S_MIN, S_MAX, on_trackbar);
	createTrackbar("S_MAX", TRACKBARWINDOWNAME, &S_MAX, S_MAX, on_trackbar);
	createTrackbar("V_MIN", TRACKBARWINDOWNAME, &V_MIN, V_MAX, on_trackbar);
	createTrackbar("V_MAX", TRACKBARWINDOWNAME, &V_MAX, V_MAX, on_trackbar);


}

int main(void)
{

	Mat imgOriginal;	//input image
	Mat imgCopy;		//copy of image
	Mat	imgFiltered;	//filtered image
	Mat imgTemplate;			//template image
	Mat imgTemplateFiltered	//filtered template

	createTrackbars();
	while (1)
	{
		//open image
		imgOriginal = imread("waldo.jpg");
		imgTemplate = imread("template.jpg");

		if (imgOriginal.empty())
		{
			std::cout << "ERROR: Image not found" << std::endl;

		}
	
		if (imgTemplate.empty())
		{
			std::cout << "ERROR: Template not found" << std::endl;

		}

		cvtColor(imgOriginal, imgCopy, CV_BGR2HSV);
		cvtColor(imgTemplate, imgTemplateFiltered, CV_BGR2HSV);

		inRange(imgCopy, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), imgFiltered);
		inRange(imgTemplateFiltered, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), imgTemplateFiltered);

		namedWindow("imgOriginal", CV_WINDOW_NORMAL);
		namedWindow("imgFiltered", CV_WINDOW_NORMAL);

		imshow("imgOriginal", imgOriginal);
		imshow("imgFiltered", imgFiltered);

		waitKey(30);
	}

	int cols = imgFiltered.cols - imgTemplateFiltered.cols - 1;
	int rows = imgFiltered.rows - imgTemplateFiltered.rows - 1;

	matchTemplate(imgFiltered,imgTemplateFiltered,  )

	return 0;
}