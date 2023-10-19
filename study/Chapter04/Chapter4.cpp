#pragma once
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void on_brightness(int pos, void* userdata);
static Mat calcGrayHist(const Mat&);
static Mat getGrayHistImage(const Mat&);

//이미지를 BGR -> GRAYSCALE 또는 GRAYSCALE을 BGR로 바꾸는 함수
void example() {
	Mat img1 = imread("lenna.bmp");
	Mat img2;
	cvtColor(img1, img2, COLOR_BGR2GRAY); // BGR->GRAYSCALE로 바꾸는 함수
	imshow("IMG1", img1);
	imshow("IMG2", img2);
	waitKey();
	destroyAllWindows();
}

//영상의 밝기 조절 함수
void brightness() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) return;
	Mat dst(src.rows, src.cols, src.type());

	for (int i = 0; i < src.rows; ++i) {
		for (int j = 0; j < src.cols; ++j) {
			dst.at<uchar>(i, j) = saturate_cast<uchar>(src.at<uchar>(i, j) + 100); 
			//255를 넘어가는 값을 자동으로 255로 설정해주는 함수
			/*
			int temp = src.at<uchar>(i,j_) + 100;
			dst.at<uchar>(i,j) = temp > 255 ? 255: temp<0 ? 0 : temp;
			*/
		}
	}
	
	imshow("SRC", src);
	imshow("DST", dst);
	waitKey();
	destroyAllWindows();
}

//트랙바를 활용한 영상의 밝기 조절 함수
void brightness4() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	namedWindow("dst");
	createTrackbar("Brightness", "dst", 0, 100, on_brightness, (void*)&src);
	on_brightness(0, (void*)&src);
	waitKey();
	destroyAllWindows();
}
void on_brightness(int pos, void* userdata) {
	Mat src = *(Mat*)userdata;
	Mat dst = src + pos;
	imshow("dst", dst);
}

//영상의 명암조절(또렷하게 하기) 함수
void contrast() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	float alpha = 1.0f;
	Mat dst = (1 + alpha) * src - 128 * alpha;
	imshow("SRC", src);
	imshow("DST", dst);
	waitKey();
	destroyAllWindows();
}

//이미지의 픽셀값을 히스토그램으로 출력하는 함수
void show_hist() {
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) return;
	Mat hist1 = calcGrayHist(src);
	Mat hist_img = getGrayHistImage(hist1);
	imshow("HISTOGRAM", hist_img);
	imshow("SRC", src);
	waitKey();
	destroyAllWindows();
}
Mat calcGrayHist(const Mat& img) {
	Mat hist;
	int channels[] = { 0 };
	int dims = 1;
	int histsize[] = { 256 };
	float graylevel[] = { 0,256 };
	const float* ranges[] = { graylevel };
	calcHist(&img, 1, channels, noArray(), hist, dims, histsize, ranges);
	//가로가 256픽셀, 세로가 최대 100픽셀인 그래프 생성
	return hist;
}
Mat getGrayHistImage(const Mat& hist) {
	double histMax;
	minMaxLoc(hist, 0, &histMax);
	Mat imgHist(100, 256, CV_8UC1, Scalar(255)); // 100 * 256크기의 히스토그램을 생성
	for (int i = 0; i < 256; ++i) {
		line(imgHist, Point(i, 100), Point(i, 100 - cvRound(hist.at<float>(i,0) * 100/histMax)),Scalar(0));	
	}
	return imgHist;
}

//이미지의 히스토그램을 보고 명암비를 조절하는 함수
void histogram_streching() {
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) return;
	double min = 0.0;
	double max = 0.0;
	minMaxLoc(src, &min, &max);
	Mat dst = ((src - min) / (max-min)) * 255; 
	Mat hist1 = calcGrayHist(src);
	Mat hist_img = getGrayHistImage(hist1);
	imshow("SRC", src);
	imshow("SRC_HISTOGRAM", hist_img);
	imshow("DST", dst);
	imshow("DST_HISTOGRAM", getGrayHistImage(calcGrayHist(dst)));
	waitKey();
	destroyAllWindows();
}
