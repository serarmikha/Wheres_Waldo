#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>

using namespace cv;



int main(void)
{

	Mat imgOriginal;	//input image
	Mat imgCopy;		//copy of image
	Mat	imgFiltered;	//filtered image
	Mat imgTemplate;			//template image
	Mat imgTemplateFiltered;	//filtered templat

	//Values for image filtering 
	int H_MIN = 160;
	int H_MAX = 179;
	int S_MIN = 100;
	int S_MAX = 255;
	int V_MIN = 100;
	int V_MAX = 255;

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

	//Convert image to HSV for easier filtering
	cvtColor(imgOriginal, imgCopy, CV_BGR2HSV);
	cvtColor(imgTemplate, imgTemplateFiltered, CV_BGR2HSV);

	//filter out anything that is not red on both images
	inRange(imgCopy, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), imgFiltered);
	inRange(imgTemplateFiltered, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), imgTemplateFiltered);

	//create a matrix to hold the results of the matching template
	int cols = imgFiltered.cols - imgTemplateFiltered.cols - 1;
	int rows = imgFiltered.rows - imgTemplateFiltered.rows - 1;

	Point matchedLocation;
	double minVal; double maxVal; Point minLoc; Point maxLoc;
	Mat result;
	result.create(rows, cols, CV_32FC1);	

	//match template to "Where's Waldo" image
	matchTemplate(imgFiltered, imgTemplateFiltered, result, CV_TM_SQDIFF);
	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());
	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

	matchedLocation = minLoc;

	//show the results
	rectangle(imgOriginal, matchedLocation, Point(matchedLocation.x + imgTemplateFiltered.cols+30, matchedLocation.y + imgTemplateFiltered.rows+30), Scalar::all(0), 2, 8, 0);

	imshow("original", imgOriginal);

	waitKey(0);
	return 0;
}