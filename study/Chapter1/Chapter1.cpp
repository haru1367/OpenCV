#pragma once
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

//이미지를 출력하는 함수
void show_images() {
    //Mat img = cv::imread("lenna.bmp",IMREAD_COLOR);    // 컬러로 사진을 읽어와 img라는 행렬로 바꿔줌
    Mat img = cv::imread("lenna.bmp", IMREAD_GRAYSCALE); // 그레이스케일로 사진을 읽어와 img라는 행렬로 바꿔줌
    Mat img2 = cv::imread("dog.bmp", IMREAD_COLOR);      // 창을 여러개 띄울 수 있음
    if (img.empty() || img2.empty()) {                   // 파일이 없을 때
        cout << "Image file does not exist" << endl;
    }
    namedWindow("LENNA", WINDOW_NORMAL);             // LENNA라는 제목의 창을 생성, 창 확대시 사진도 같이 확대
    namedWindow("DOG");                              // WINDOW_NORMAL 없을시 window_auto
    imshow("LENNA", img);                            // LENNA라는 창에 img를 보여줌
    imshow("DOG", img2);
    waitKey();                                       // 다른 키를 누르기 전까지 화면이 멈춰있음 (괄호안에 1000을 입력시 1초후 창이 닫힘)
    //cv::destroyWindow("LENNA");                    // 객체 파괴
    destroyAllWindows();                             // 모든 객체 파괴
}

