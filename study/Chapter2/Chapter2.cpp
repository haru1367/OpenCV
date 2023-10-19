#pragma once
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//Point 클래스와 Rec클래스, Size클래스 함수
void show_code_3() { 
	Point pt1;                 // default 생성자
	pt1.x = 5;
	pt1.y = 10;
	Point pt2(pt1);            // 복사 생성자
	Point p3 = pt1 + pt2;	   // 연산자 오버로드
	int dot1 = pt1.dot(pt2);   // 벡터 내적
	cout << pt2 << endl;

	Size sz1(10, 20);          // 가로가 10 세로가 20
	Size sz2;
	Size sz3 = sz1 + sz2;
	int sz4 = sz1.area();      // 넓이(10 * 20)

	cout << sz1 << endl;

	Rect rc1(0, 10, 60, 40);    // (0,10),(60,40)이 양 끝점인 사각형 생성
	Rect rc2 = rc1 + Size(50, 40);   // rc1의 가로 세로크기가 각각 50, 40씩 증가
	Rect rc3 = rc2 + Point(60, 60);  // rc2의 위치가 (60,60)만큼 이동

	Range r1(0, 10);            // int i = 0; i<10; ++i;
	
	String str1 = "Hello";
	String str2 = "World";
	String str3 = str1 + str2;  // 연산자 overloading

	for (int i = 0; i < 10; ++i) {
		String str = format("Test %d", i);
		cout << str << endl;
	}

	//Mat mat1(800, 800, CV_8UC1, Scalar(127));  // mat1(행,열,unsigned_char,색깔), CV_8UC1은 openCV에서만 쓰는 타입
	//Mat mat2(800, 800, CV_8UC3, Scalar(255,0,0)); // RGB방식의 매트릭스 (B,G,R)순서로 입력받는다
	//Mat mat3(Mat::zeros(900, 900, CV_8UC1)); // matrix를 0으로 초기화
	//Mat mat4(Mat::ones(900, 900, CV_8UC1)); // matrix를 1로 초기화
	//cout << "[ 10, 20 ] : " << static_cast<int>(mat1.at<uchar>(10, 20)) << endl;   // [10,20]에 해당하는 행렬값 출력
	Mat mat5(255* Mat::eye(900, 900, CV_8UC1));  // 항등행렬에 255를 곱한 행렬
	//imshow("Mat", mat1);
	//imshow("Mat2", mat2);
	//imshow("Mat3", mat3);
	//imshow("Mat4", mat4);
	imshow("Mat5", mat5);
	waitKey();
	destroyAllWindows();

}

//이미지를 복사,수정하는 함수
void show_code_3_8() {
	Mat img1{ imread("dog.bmp") };  // uniform initializer (초기화를 1번만가능, 다른이미지를 불러올 수 없다)
	if (img1.empty()) {
		cout << "파일이 없습니다." << endl;
		return;
	}
	cout << img1.size << endl;  // 이미지의 크기 출력
	
	Mat img2 = img1;			// shallow copy
	Mat img3 = img1.clone();	// deep copy

	imshow("IMG1", img1);
	imshow("IMG2", img2);
	imshow("IMG3", img3);
	waitKey();
	
	// 원본 이미지 수정
	img1.setTo(Scalar(0, 255, 255));
	
	imshow("IMG1", img1);
	imshow("IMG2", img2);       
	imshow("IMG3", img3);      // deep copy 했기 때문에 원본이 바뀌지 않는다.
	waitKey();

	destroyAllWindows();
}

//이미지를 추출하고 반전시키는 함수
void show_code_3_9() {
	Mat img1 = imread("cat.bmp");
	if (img1.empty()) {
		cout << "파일이 없습니다." << endl;
		return;
	}
	Mat img2 = img1(Rect(270,120,340,240)); //(270,120)부터 340*240크기의 사각형 영상 추출
	Mat img3 = img1(Rect(270, 120, 340, 240)).clone(); // deep copy
	img2 = ~img2;    // 비트 반전
	imshow("IMG1",img1);
	imshow("IMG2", img2);
	imshow("IMG3", img3);
	waitKey();
	destroyAllWindows();

}

//이미지의 정보를 matrix로 출력하고 변경하는 함수
void show_code_3_10() {
	Mat mat1(Mat::zeros(10, 10, CV_8UC1));
	for (int i = 0; i < mat1.rows; i++) {
		for (int j = 0; j < mat1.cols; j++) {
			cout << static_cast<int>(mat1.at<uchar>(i, j)) << " ";
		}
		cout << endl;
	}
	cout << "=================================================" << endl;
	uchar value{ 0u };
	for (int i = 0; i < mat1.rows; i++) {
		for (int j = 0; j < mat1.cols; j++) {
			mat1.at<uchar>(i, j) = ++value;                  //set
		}
	}
	for (int i = 0; i < mat1.rows; i++) {
		for (int j = 0; j < mat1.cols; j++) {
			cout << static_cast<int>(mat1.at<uchar>(i, j)) << " ";        //get
		}
		cout << endl;
	}

}

//이미지의 정보를 조회하는 함수
void show_code_3_11() {
	Mat img1 = imread("coins.png",IMREAD_UNCHANGED);
	if (img1.empty()) {
		return;
	}
	cout << "PNG channel : " << img1.channels() << endl;     // 채널의 개수 출력(png파일은 4채널)
	cout << "PNG column : " << img1.cols << endl;
	cout << "PNG row : " << img1.rows << endl;
	cout << "PNG size : " << img1.size << endl;
	if (img1.channels() == CV_8UC1) {
		cout << "Grayscale" << endl;
	}
	else if (img1.channels() == CV_8UC3) {
		cout << "Color" << endl;
	}
	else {
		cout << "PNG image" << endl;
	}
}

//matrix를 연산하는 함수
void show_code_3_12() {
	float data[] = { 1.0f, 2.0f, 3.0f, 4.0f };

	Mat mat1(2, 2, CV_32FC1, data);
	cout << mat1 << endl;

	Mat mat2 = mat1.inv();  // 역행렬
	cout << mat2 << endl;

	Mat mat3 = mat1 * mat2;
	cout << mat3 << endl;

	Mat mat4 = mat1.t();    // 전치행렬
	cout << mat4 << endl;

	Mat mat5 = mat1 + mat4;
	cout << mat5 << endl;

	Mat img1 = imread("lenna.bmp", IMREAD_GRAYSCALE);
	imshow("IMG", img1);
	Mat img2 = img1.t();
	imshow("IMG2", img2);
	Mat img3 = img1 - 50;
	imshow("IMG3", img3);
	waitKey();
	destroyAllWindows();
}

//matrix를 연산하는 함수2
void show_code_3_13() {
	Mat img1 = imread("lenna.bmp", IMREAD_GRAYSCALE);
	Mat img2;
	img1.convertTo(img2, CV_32FC1);				// img1을 float타입으로 바꿔준다.
	uchar data1[] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	
	Mat mat1(3, 4, CV_8UC1, data1);
	cout << mat1 << endl << endl;
	Mat mat2 = mat1.reshape(0,1);				//0은 채널, 1은 row의 개수
	cout << mat2 << endl << endl;

	Mat mat3 = Mat::ones(1, 4, CV_8UC1) * 255;
	mat1.push_back(mat3);						//mat1에 mat3추가하기
	cout << mat1 << endl << endl;

	/*imshow("IMG2", img2);
	waitKey();
	destroyAllWindows();*/
}

//3차원 픽셀값으로 색깔을 나타내는 함수
void show_code_3_16() {
	Scalar blue = 128;
	cout << "blue : " << blue << endl;

	Scalar yellow(0, 255, 255);
	cout << "yellow : " << yellow << endl;

	Mat img1(800, 800, CV_8UC3, yellow);
	imshow("IMG1", img1);
	waitKey();
	destroyAllWindows();
}
