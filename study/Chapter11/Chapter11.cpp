#pragma once
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


//스마트 포인터 (객체가 사라지면 스스로 사라지는 포인터)
static cv::Ptr<cv::ml::KNearest>train_knn() {
	cv::Mat digits = cv::imread("digits.png", cv::IMREAD_GRAYSCALE);
	if (digits.empty()) return nullptr;
	cv::Mat train_images;
	cv::Mat train_labels;

	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 100; j++) {
			cv::Mat roi = digits(cv::Rect(j * 20, i * 20, 20, 20));	//각 글자 하나의 사이즈는 20*20
			cv::Mat roi_float;
			roi.convertTo(roi_float, CV_32FC1); // openCV 데이터 타입으로 바꿔준다.
			cv::Mat roi_floatten = roi_float.reshape(1, 1); // 1차원 벡터로 만들어줌 20 * 20 --> 400개
			train_images.push_back(roi_floatten);
			train_labels.push_back(i / 5); // 정답을 넣어줌.
		}
	}
	cv::Ptr<cv::ml::KNearest>knn = cv::ml::KNearest::create(); // Singular 타입
	knn->train(train_images,cv::ml::ROW_SAMPLE,train_labels);
	return knn;
}

static cv::Point point_prev(-1, -1); // 마우스를 떼면 가운데 오게 한다.
static void on_mouse(int event, int x, int y, int flag, void* userdata) {		//마우스 동작 함수
	Mat src = *(static_cast<cv::Mat*>(userdata));
	if (event == cv::EVENT_LBUTTONDOWN) {// 왼쪽 버튼이 눌렸을 때
		point_prev = cv::Point(x, y);
	}
	else if (event == cv::EVENT_LBUTTONUP) {// 왼쪽 버튼이 눌려졌다가 떨어졌을 때
		point_prev = cv::Point(-1, -1);
	}
	else if (event == cv::EVENT_MOUSEMOVE && (flag & cv::EVENT_LBUTTONDOWN)) {	//마우스 버튼을 누른상태에서 움직였을때
		cv::line(src, point_prev, cv::Point(x, y), cv::Scalar(255, 255, 255), 30, cv::LINE_AA, 0);
		point_prev = cv::Point(x, y);
		cv::imshow("DISPLAY", src);

	}
}

//knn 머신러닝 함수
void do_knn_machine_learning() {
	cv::Ptr<cv::ml::KNearest>knn = train_knn();
	if (knn.empty()) {
		std::cerr << "Train 실패" << std::endl;
		return;
	} 
	std::cout << "학습을 성공적으로 하였습니다." << std::endl;
	cv::Mat input_display(200, 200, CV_8UC1);
	cv::namedWindow("DISPLAY", cv::WINDOW_NORMAL);
	cv::setMouseCallback("DISPLAY", on_mouse, (void*)&input_display);
	while (true) {
		int keyboard_key = cv::waitKey();
		if (keyboard_key == 27) break;
		else if (keyboard_key == ' ') //space입력
		{
			cv::Mat image_resize;
			cv::Mat image_float; // CV_32FC1으로 변환을 위한 행렬
			cv::Mat image_flatten; // 1 *400
			cv::Mat resource; // 결과를 저장할 행렬
			cv::resize(input_display, image_resize, cv::Size(20, 20), 0, 0, cv::INTER_AREA);
			image_resize.convertTo(image_float, CV_32FC1);
			image_flatten = image_float.reshape(1, 1);
			knn->findNearest(image_flatten, 5, resource);		// k =5, 선택가능 3,5,7,9 (짝수도 가능하지만 홀수가 더 용이)
			std::cout << cvRound(resource.at<float>(0, 0)) << std::endl;
			input_display.setTo(0); //다시 화면입력창을 검게 하기 위해서
			cv::imshow("DISPLAY", input_display);
		}
	}
}
