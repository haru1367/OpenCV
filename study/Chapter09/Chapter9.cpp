#pragma once
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//이미지에서 Red, Blue, Green 성분만 불러 grayscale로 읽기
void show_BGR_channels() {
	Mat src = imread("candies.png", IMREAD_COLOR);  // 356 * 493

	Mat B(src.size(), CV_8UC1);  // Blue 색상만 가져오기 때문에 채널이 1개
	Mat G(src.size(), CV_8UC1);
	Mat R(src.size(), CV_8UC1);

	for (int i = 0; i < src.rows; ++i) {
		for (int j = 0; j < src.cols; ++j) {
			Vec3b& p1 = src.at<Vec3b>(i, j); 
			B.at<uchar>(i, j) = p1[0];
			G.at<uchar>(i, j) = p1[1];
			R.at<uchar>(i, j) = p1[2];
		}
	}
	imshow("SRC", src);
	imshow("B", B);
	imshow("G", G);
	imshow("R", R);
	waitKey();
	destroyAllWindows();
}

//split함수를 이용해 HSV성분으로 분리해 grayscale로 읽기
void color_split() {
	Mat src = imread("candies.png");
	Mat dst(src.size(), src.type());
	vector<Mat>hsv_planes;
	cvtColor(src, dst, COLOR_BGR2HSV);
	split(dst, hsv_planes);
	imshow("src", src);
	imshow("DST", dst);
	imshow("H", hsv_planes[0]);
	imshow("S", hsv_planes[1]);
	imshow("V", hsv_planes[2]);
	waitKey();
	destroyAllWindows();
}

//피부색을 검출하는 방법 -> 히스토그램 역투영
