
#include <stdio.h>
#include <stdlib.h>
#include <cv.h>
#include <highgui.h>

IplImage* image = 0;
IplImage* dst = 0;

IplImage* erode = 0;
IplImage* dilate = 0;

int min_rad = 1;
int max_rad = 10;

int min_iter = 1;
int max_iter = 10;


void MyTrackbarRadius(int pos)
{
	min_rad = pos;
}
void MyTrackbarIter(int pos)
{
	min_iter = pos;
}

int main(int argc, char* argv[]) 
{
	char* filename = argc == 2 ? argv[1] : "Image0.jpg";
	image = cvLoadImage(filename, 1);
	dst = cvCloneImage(image);
	erode = cvCloneImage(image);
	dilate = cvCloneImage(image);

	printf("[i] image %s\n", filename);
	assert(image != 0);

	cvNamedWindow("original", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("erode", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("dilate", CV_WINDOW_AUTOSIZE);


	cvCreateTrackbar("Radius", "original", &min_rad, max_rad, MyTrackbarRadius);
	cvCreateTrackbar("Iterations", "original", &min_iter, max_iter, MyTrackbarIter);

	while (true)
	{
		cvShowImage("original", image);

		IplCornKernel* kernel = cvCreateStructuringElementEx(min_rad * 2 + 1, min_rad * 2 + 1, min_rad, min_rad, CV_SHAPE_ELLIPSE);

		cvErode(image, erode, kernel, min_iter);
		cvDilate(image, dilate, kernel, min_iter);

		cvShowImage("erode", erode);
		cvShowImage("dilate", dilate);

		cvReleaseStructuringElement(&kernel);

		char c = cvWaitKey(33);
		if (c == 27) break;
	}

	cvReleaseImage(&image);
	cvReleaseImage(&dst);
	cvReleaseImage(&erode);
	cvReleaseImage(&dilate);

	cvDestroyWindow("original");
	cvDestroyWindow("erode");
	cvDestroyWindow("dilate");
	return 0;
}