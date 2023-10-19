#pragma once
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//trackbar를 사용한 영상의 이진화 함수(threshold방식)
static void on_threshold(int position, void* userdata) {
	Mat src = *(static_cast<Mat*>(userdata));
	Mat dst;
	threshold(src, dst, position, 255.0, THRESH_BINARY); //THRESH_BINARY 방식을 사용
	imshow("DST", dst);
}
static void on_trackbar(int position, void* userdata) {
	Mat src = *(static_cast<Mat*>(userdata));
	int block_size = position;
	if (block_size % 2 == 0) block_size--;   
	if (block_size < 3) block_size = 3;			//블록사이즈가 3보다 작으면 3으로 설정
	Mat dst;
	adaptiveThreshold(src, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, block_size, 5.0/*기본값*/);
	imshow("DST", dst);
}

void using_threshold() {
	//Mat src = imread("neutrophils.png", IMREAD_GRAYSCALE);
	Mat src = imread("sudoku.jpg", IMREAD_GRAYSCALE);
	if (src.empty()) return;
	namedWindow("SRC", WINDOW_NORMAL);
	namedWindow("DST", WINDOW_NORMAL);
	imshow("SRC", src);
	createTrackbar("Threshold", "DST", 0, 255, on_threshold, (void*)&src);	//트랙바의 최대값은 255로 설정
	setTrackbarPos("Threshold", "DST", 128);		//트랙바의 처음 위치를 128로 설정
	waitKey();
	destroyAllWindows();
}

//적응형이진화 - 불균일한 조명성분을 가지고 있는 영상에 대해 객체와 배경을 구분할때 쓰는 함수 (adaptive)
void adaptive_threshold() {
	Mat src = imread("sudoku.jpg", IMREAD_GRAYSCALE);
	if (src.empty()) return;
	namedWindow("SRC", WINDOW_NORMAL);
	imshow("SRC", src);
	namedWindow("DST",WINDOW_NORMAL);
	createTrackbar("Block Size", "DST", 0, 200, on_trackbar, (void*)&src); // 최소가 0, 최대가 200인 트랙바 생성
	setTrackbarPos("Block Size", "DST", 11);
	waitKey();
	destroyAllWindows();
}

//모폴로지함수(영상을 전처리 또는 후처리 할때 사용) - image processing (객체의 형태 및 구조에 대해 분석하고 처리)
void erode_dilate() {
	Mat src = imread("milkdrop.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) return;
	imshow("SRC", src);
	Mat binary_image;
	threshold(src, binary_image, 0.0/* OTSU를 쓰기위해 0을 사용*/, 255.0, THRESH_BINARY | THRESH_OTSU);
	Mat dst_erode;
	erode(binary_image, dst_erode, Mat()/*3*3*/);
	for (int i = 0; i < 5; i++) {
		erode(dst_erode, dst_erode, Mat());    // 침식
		imshow("Erode", dst_erode);
		waitKey();
	}

	Mat dst_dilate;
	dilate(binary_image, dst_dilate, Mat()); // 3*3
	for (int i = 0; i < 5; i++) {						//팽창
		dilate(dst_dilate, dst_dilate, Mat());
		imshow("Dilate", dst_dilate);
		waitKey();
	}
	destroyAllWindows();
}	

//이진 영상의 열기와 닫기(열기 - 침식연산후 팽창, 닫기 - 팽창연산후 침식)
// -> 열기 : 이진 영상에 존재하는 작은 크기의 객체가 효과적으로 제거
// -> 팽창 : 객체 내부의 작은 구멍을 제거
void open_close() {
	Mat src = imread("milkdrop.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) return;
	imshow("SRC", src);
	Mat binary_image;
	threshold(src, binary_image, 0.0, 255.0, THRESH_BINARY | THRESH_OTSU);
	Mat dst_open;
	Mat dst_close;
	imshow("BINARY_IMAGE", binary_image);
	morphologyEx(binary_image, dst_open, MORPH_OPEN, Mat()/*3 *3 */, Point(-1, -1)/*기본값*/, 5/*기본값*/);
	morphologyEx(binary_image, dst_close, MORPH_CLOSE, Mat(), Point(-1, -1), 5);
	imshow("DST_OPEN", dst_open);
	imshow("DST_CLOSE", dst_close);
	waitKey();
	destroyAllWindows();

}
