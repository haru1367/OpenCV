#pragma once
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//소벨마스크 기준 에지 검출 함수
void sobel_edge() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) return;
	Mat dx;
	Mat dy;
	Sobel(src, dx, CV_32FC1, 1, 0); // X로 미분
	Sobel(src, dy, CV_32FC1, 0, 1); // Y로 미분

	imshow("SRC", src);
	imshow("DX", dx);
	imshow("DY", dy);

	Mat mag;
	magnitude(dx, dy, mag);
	// c++ float -> imshow (opencv data)
	mag.convertTo(mag, CV_8UC1);
	imshow("MAG", mag);
	Mat real_edge = mag > 150;
	imshow("REALEDGE", real_edge);

	waitKey();
	destroyAllWindows();
}

//캐니 에지 검출 함수
void canny_edge() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) return;
	Mat dst1;
	Mat dst2;
	Canny(src, dst1, 50, 150, 3/*기본값*/, true);
	Canny(src, dst2, 50, 100, 3/*기본값*/, true);

	imshow("SRC", src);
	imshow("DST1", dst1);
	imshow("DST2", dst2);
	waitKey();
	destroyAllWindows();
}

//허프 변환 직선 검출함수
void hough_lines() {
	Mat src = imread("building.jpg", IMREAD_GRAYSCALE);
	if (src.empty()) return;
	Mat edge;
	Canny(src, edge, 50, 150);   // 캐니 에지 통과
	vector<Vec2f>lines;
	HoughLines(edge, lines, 1.0, CV_PI / 180, 250/*기본값*/);  //검출을 자세히 하려면 250에서 값을 더 줄이면 된다.
	
	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR); // channel -> 3channel (칼라는 아님)
	
	for (int i = 0; i < lines.size(); ++i) {
		float r = lines[i][0];
		float t = lines[i][1];
		double cos_t = cos(t);
		double sin_t = sin(t);
		double x0 = r * cos_t;
		double y0 = r * sin_t;
		double alpha = 1000;
		
		Point pt1(cvRound(x0 + alpha * (-sin_t)), cvRound(y0 + alpha * cos_t));
		Point pt2(cvRound(x0 - alpha * (-sin_t)), cvRound(y0 - alpha * cos_t));
		line(dst, pt1, pt2, Scalar(0, 0, 255), 2, LINE_AA);
	}
	imshow("SRC", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}

//허프변환 - 원검출 함수
void hough_circles() {
	Mat src = imread("coins.png", IMREAD_GRAYSCALE);
	if (src.empty()) return;
	Mat blurred; // 노이즈 제거 용도 (미세한 픽셀 -> 원으로 인식할 수 있기 때문에)
	blur(src, blurred, Size(3, 3));
	
	vector<Vec3f>circles;
	HoughCircles(blurred, circles, HOUGH_GRADIENT, 1, 50, 150, 125); 
	//두 원의 중심점 거리가 50픽셀보다 작으면 검출 x, 캐니 에지 검출기의 높은 임계값은 150으로 지정. 축적 배열 원소 값이 125보다 크면 원의 중심점으로 선택
	//검출된 원의 중심좌표와 반지름 정보는 circles 변수에 저장

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);
	for (Vec3f c : circles) {
		Point center(cvRound(c[0]), cvRound(c[1]));
		int radius = cvRound(c[2]);
		circle(dst, center, radius, Scalar(0, 0, 255), 2, LINE_AA);
	}	
	imshow("SRC", src);
	imshow("DST", dst);
	waitKey();
	destroyAllWindows();

}
