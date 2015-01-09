#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    //if( argc != 2)
    //{
    // cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
    // return -1;
    //}

	VideoCapture cap(0);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 320); //I don't know what this does
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240); //or this
	if(!cap.isOpened())
		return -1;

	Mat edges;
	HOGDescriptor hog;
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector()); //may want to use Daimler instead

	namedWindow("edges",1);
	for(;;){
		Mat frame;
		//cap >> frame; //get a new frame from camera
		//cvtColor(frame, edges, CV_BGR2GRAY);
		//GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
		//Canny(edges, edges, 0, 30, 3);
		//imshow("edges", edges);
		//if(waitKey(30) >=0) break;

		cap >> frame;
		if(!frame.data)
			continue;
		vector<Rect> found, found_filtered;
		hog.detectMultiScale(frame, found, 0, Size(8,8), Size(32,32), 1.05, 2);

		size_t i, j;
		for(i=0; i < found.size(); i++)
		{
			Rect r = found[i];
			for(j=0; j < found.size(); j++)
				if(j!=1 && (r & found[j])==r)
					break;
			if(j==found.size())
				found_filtered.push_back(r);
		}
		for(i=0; i < found_filtered.size(); i++)
		{
			Rect r = found_filtered[i];
			r.x += cvRound(r.width*0.1);
			r.width = cvRound(r.width*0.8);
			r.y += cvRound(r.height*0.06);
			r.height = cvRound(r.height*0.9);
			rectangle(frame, r.tl(), r.br(), cv::Scalar(0,255,0), 2);
		}
		imshow("edges", frame);
		if(waitKey(20) >= 0)
			break;
	}
	//the camera will be deinitialized automatically in VideoCapture destructor
	
 //   Mat image;
 //   image = imread("C:/Users/limbird/Documents/Visual Studio 2012/Projects/Test Application 2/Test Application 2/opencv-logo.png", CV_LOAD_IMAGE_COLOR);   // Read the file
	//
	//if(! image.data )                              // Check for invalid input
 //   {
 //       cout <<  "Could not open or find the image" << std::endl ;
 //       return -1;
 //   }

	//int rows = image.rows;
	//int cols = image.cols;
	//cout << "The rows is " << rows << " the cols is " << cols << endl;

	//for(int i = 0; i < rows; i++){
	//	for(int j = 0; j < cols; j++){
	//		if(image.at<uchar>(i,j*3+2) == 255 && image.at<uchar>(i,j*3+0) == 0 && image.at<uchar>(i,j*3+1) == 0)
	//			image.at<uchar>(i,j*3+2) = 0;
	//		//image.at<uchar>(i,j*3+0) = 0; //blue channel
	//		//image.at<uchar>(i,j*3+1) = 0; //green channel
	//		//image.at<uchar>(i,j*3+2) = 0; //red channel
	//	}
	//}

 //   namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
 //   imshow( "Display window", image );                   // Show our image inside it.

/*    waitKey(0); */                                         // Wait for a keystroke in the window
    return 0;
}