#pragma once
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//affine 변환행렬 함수
void affine_transform() {
	Mat src = imread("tekapo.bmp");
	if (src.empty()) return;

	//처음 세점의 좌표와 해당 점들이 변환이동된 각각의 좌표를 가지고 affine행렬을 구한다.
	Point2f srcPts[3], dstPts[3];
	srcPts[0] = Point2f(0, 0);
	srcPts[1] = Point2f(src.cols - 1, 0);
	srcPts[2] = Point2f(src.cols - 1, src.rows - 1);
	dstPts[0] = Point2f(50, 50);
	dstPts[1] = Point2f(src.cols - 100, 100);
	dstPts[2] = Point2f(src.cols - 50, src.rows - 50);
	Mat M = getAffineTransform(srcPts, dstPts);
	cout << M << endl;

	Mat dst;
	//이미지에 affine행렬을 적용해 변경한다.
	warpAffine(src, dst, M, Size());
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}

//영상의 회전,대칭 변환 함수
void rotate_flip() {
	Mat src = imread("lenna.bmp");
	Mat dst1;
	Mat dst2;
	rotate(src, dst1, ROTATE_90_CLOCKWISE); // 반시계방향으로 90도 회전
	flip(src, dst2, -1);	// +1 : 좌우대칭, 0 : 상하대칭 , -1 :좌우&상하 대칭
	imshow("SRC", src);
	imshow("DST1", dst1);
	imshow("DST2", dst2);
	waitKey();
	destroyAllWindows();
}

//영상의 투시변환 함수(영상을 임의의 위치로 옮기는 함수- 마우스로 옮길위치를 선택)
static void on_mouse(int, int, int, int, void*);  // 마우스가 움직일 때 이 함수를 callback
static int count1 = 0;		//마우스 클릭 횟수
static Point2f srcQuad[4];  //마우스 클릭 시 찍히는 점의 좌표(카드의 모서리 포인트 값)
static Point2f dstQuad[4];  //카드를 옮길 위치의 좌표값 
static Mat src;
void on_mouse(int event, int x, int y, int flags, void* userdata) {
	if (event == EVENT_LBUTTONDOWN) {
		if (count1 < 4) {
			srcQuad[count1++] = Point2f(x, y);
			circle(src, Point(x, y), 5, Scalar(0, 0, 255), -1);
			imshow("SRC", src);
		}
		if (count1 == 4) {
			int w = 200, h = 300;
			dstQuad[0] = Point2f(0, 0);
			dstQuad[1] = Point2f(w - 1, 0);
			dstQuad[2] = Point2f(w - 1, h - 1);
			dstQuad[3] = Point2f(0, h - 1);

			Mat pers = getPerspectiveTransform(srcQuad, dstQuad);
			Mat dst;
			warpPerspective(src, dst, pers, Size(w, h));
			imshow("DST", dst);
		}
	}
}
void perspective() {
	src = imread("card.bmp");
	if (src.empty()) return;
	namedWindow("SRC", WINDOW_NORMAL);
	imshow("SRC", src);
	setMouseCallback("SRC", on_mouse);
	waitKey();
	destroyAllWindows();
}
