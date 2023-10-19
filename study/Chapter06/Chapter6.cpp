#pragma once
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//엠보싱 필터링 함수(객체의 윤곽을 올록볼록한 형태로 만들기)
void filter_embossing() {
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) return;
	float filter_data[] = { -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f };
	Mat emboss_kernel(3, 3, CV_32FC1, filter_data);

	Mat dst;
	filter2D(src, dst, -1, emboss_kernel, Point(-1, -1), 128/*좀 더 밝게*/);
	imshow("SRC", src);
	imshow("DST", dst);
	waitKey();
	destroyAllWindows();
}

//블러 필터링 함수
void filter_blurring() {
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) return;
	Mat dst;
	float blur_filter[] = { 1 / 9.f, 1 / 9.f, 1 / 9.f,1 / 9.f, 1 / 9.f, 1 / 9.f, 1 / 9.f, 1 / 9.f, 1 / 9.f };
	Mat dst2(3, 3, CV_32FC1, blur_filter);  // 3 * 3 평균값 필터
	filter2D(src, dst, -1, dst2, Point(-1, -1), 0);
	imshow("SRC", src);
	imshow("DST", dst);
	waitKey();

	for (int ksize = 3; ksize <= 7; ksize += 2) {   // 마스크의 크기가 커질수록 부드러워진다.
		blur(src, dst, Size(ksize, ksize));
		String desc = format("Blur : %d X %d", ksize, ksize);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);
		imshow("DST", dst);
		waitKey();
	}
	destroyAllWindows();
}

//가우시안 필터링 함수(표준 정규분포)
void filter_gaussian() {
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) return;
	Mat dst;
	for (int sigma = 1; sigma <= 5; sigma++) {
		GaussianBlur(src, dst, Size(), static_cast<double>(sigma));
		String text = format("sigma = %d", sigma);
		putText(dst, text, Point(0, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);
		imshow("DST", dst);
		waitKey();
	}
	destroyAllWindows();
}

//언샤프 마스크 필터링 함수
void filter_unsharp_mask() {
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) return;

	imshow("SRC", src);
	Mat blurred;
	float alpha = 1.0f;
	for (int sigma = 1; sigma <= 50; ++sigma) {
		GaussianBlur(src, blurred, Size(), sigma);
		Mat dst = (1 + alpha)* src - (alpha * blurred);
		String text = format("Sigma : %d", sigma);
		putText(dst, text, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255),1, LINE_AA);
		imshow("DST", dst);
		waitKey();

	}

	destroyAllWindows();
}

//가우시안 잡음 추가 함수
void noise_gaussian() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) return;
	Mat dst;
	for (int stddev = 10; stddev <= 30; stddev += 10) {
		Mat noise(src.size(), CV_32FC1);
		randn(noise, 0, stddev); //평균이 0이고 표준편차는 10부터 30이하의 값
		add(src, noise, dst, noArray(), CV_8UC1);
		String text = format("stddev = %d", stddev);
		putText(dst, text, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);
		imshow("DST", dst);
		waitKey();
	}
	destroyAllWindows();
}

//양방향 필터 함수
void filter_bilateral() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) return;
	Mat noise(src.size(), CV_32SC1);
	randn(noise, 0, 5);                  //평균 0, 표준편차 5
	add(src, noise, src, Mat(), CV_8U);
	
	Mat dst1;
	GaussianBlur(src, dst1, Size(), 5);    //gaussian blur를 사용하면 주로엣지부분이 필터링된다. (sigma5)

	Mat dst2;
	bilateralFilter(src, dst2, -1 /* 이웃 픽셀과의 거리를 자동으로 잡아준다. */, 10, 5);  //bilateral Filter을 사용하면 엣지를 제외한 나머지부분이 주로 필터링된다.

	imshow("SRC", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	waitKey();
	destroyAllWindows();
}

//미디언 필터 함수
void filter_median() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) return;
	//salt & pepper 노이즈 방식
	int num = (int)(src.total() * 0.1);
	for (int i = 0; i < num; i++) {
		int x = rand() % src.cols;
		int y = rand() % src.rows;
		src.at<uchar>(y, x) = (i % 2) * 255;   // 짝수이면 검은점, 홀수이면 흰점
	}
	Mat dst1;
	GaussianBlur(src, dst1, Size(), 1);

	Mat dst2;
	medianBlur(src, dst2, 3);

	imshow("SRC", src);    // 원본에 salt & pepper이 추가된 이미지
	imshow("dst1", dst1);	// gaussian blur 가 적용된 이미지
	imshow("dst2", dst2);   // median blur가 적용된 이미지
	waitKey();
	destroyAllWindows();
}
