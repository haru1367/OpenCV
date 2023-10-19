#pragma once
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


//영상을 합성하는 함수 (사이즈가 같아야함)
void arithmetic1() {
	Mat src1 = imread("lenna256.bmp",IMREAD_GRAYSCALE);
	Mat src2 = imread("square.bmp", IMREAD_GRAYSCALE);
	if (src1.empty() || src2.empty()) return;
	cout << src1.size << endl;
	cout << src2.size << endl;

	Mat dst1;
	add(src1,src2,dst1);   // src1 + src2를  dst1에 저장

	Mat dst2;
	subtract(src2, src1, dst2);  // src2 - src1을 dst2에 저장

	Mat dst3;
	absdiff(src1, src2, dst3);  // 절댓값차이 (src1 - src2)를 dst3에 저장  -> 주로 움직이는 물체를 찾을 때 사용한다.

	Mat dst4;
	namedWindow("ADDWEIGHTED");
	for (double i = 0; i <= 1.0; i+=0.2) {
		addWeighted(src1, i, src2, 1.0 - i, 0.0, dst4); // src1과 src2를 i : 1-i 비율로 합성
		imshow("ADDWEIGHTED", dst4);
		waitKey(1000);
	}

	imshow("SRC1", src1);
	imshow("SRC2", src2);
	imshow("DST1", dst1);
	imshow("DST2", dst2);
	imshow("DST3", dst3);
	waitKey();
	destroyAllWindows();
}
void logical() {
	Mat src1 = imread("lenna256.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("square.bmp", IMREAD_GRAYSCALE);
	if (src1.empty() or src2.empty()) return;
	Mat dst(256, 256, CV_8UC1);

	//각 픽셀값을 2진수로 나타낸뒤 연산한다.

	bitwise_and(src1, src2, dst);   
	imshow("SRC1", src1);
	imshow("SRC2", src2);
	imshow("DST", dst);
	waitKey();

	bitwise_or(src1, src2, dst);  
	imshow("SRC1", src1);
	imshow("SRC2", src2);
	imshow("DST", dst);
	waitKey();

	bitwise_xor(src1, src2, dst);   
	imshow("SRC1", src1);
	imshow("SRC2", src2);
	imshow("DST", dst);
	waitKey();

	bitwise_not(src1,dst);   
	imshow("SRC1", src1);
	imshow("DST", dst);
	waitKey();

	destroyAllWindows();
}
