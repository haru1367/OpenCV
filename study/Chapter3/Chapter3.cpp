#pragma once
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

static void on_mouse(int, int, int, int, void*);	//함수의 원형
static void on_level_changed(int, void*); // 함수의 원형

static Mat img;
Point pt_old;

//카메라 연결 함수
void show_camera() {
	VideoCapture cap(0); // index 0 = 첫번째, 1 -> 두번째 (컴퓨터는 0, 노트북은 1)
	if (cap.isOpened()) {   // 카메라가 연결되었는지 체크
		cout << "연결이 되었습니다." << endl;
	}
	else {
		cout << "카메라 연결 문제 발생." << endl;
		return;
	}
	cout << "Frame width : " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;   // 사진의 width를 소수점을 제거하고 출력
	cout << "Frame height : " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;	// 사진의 height를 소수점을 제거하고 출력

	Mat frame;
	Mat inversed_frame;
	namedWindow("FRAME", WINDOW_NORMAL);
	namedWindow("INVERSE", WINDOW_NORMAL);
	while (true) {
		cap >> frame;
		if (frame.empty()) break;
		inversed_frame = ~frame;
		imshow("FRAME", frame);
		imshow("INVERSE", inversed_frame);
		if (waitKey(10) == 27) {
			break;   // 0.01초 단위, 27  --> ESC
		}
	}
	destroyAllWindows();
}

//동영상 재생 함수
void show_movie() {
	VideoCapture cap("stopwatch.avi");
	if (cap.isOpened()) {
		cout << "동영상이 연결 되었습니다." << endl;
	}
	else {
		cout << "동영상 파일이 없습니다." << endl;
		return;
	}
	cout << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;
	double fps = cap.get(CAP_PROP_FPS);  // 이 영상의 프레임 
	cout << "FPS : " << fps << endl;
	int delay = cvRound(1000 / fps);
	namedWindow("STOPWATCH", WINDOW_NORMAL);
	namedWindow("INVERSE", WINDOW_NORMAL);
	Mat frame;
	while (true) {
		cap >> frame;

		if (frame.empty()) {
			break;
		}
		imshow("STOPWATCH", frame);
		imshow("INVERSE", ~frame);
		waitKey(delay);
	}
	destroyAllWindows();
}

//동영상 녹화 함수
void show_video_record() {
	VideoCapture cap(0);
	if (cap.isOpened()) {
		cout << "카메라가 정상적으로 연결 되었습니다." << endl;
	}
	else {
		cout << "카메라 문제 발생" << endl;
		return;
	}
	double fps = cvRound(cap.get(CAP_PROP_FPS));           // 안되면 제품에 있는 FPS를 사용
	int delay = cvRound(1000 / fps);
	int fourcc = VideoWriter::fourcc('X', '2', '6', '4');  // 동영상 코덱 파일 사용
	Mat frame;
	VideoWriter output("recording.mp4", fourcc, 30, Size(cap.get(CAP_PROP_FRAME_WIDTH), cap.get(CAP_PROP_FRAME_HEIGHT))); //영상을 저장할 곳

	if (output.isOpened()) {
		cout << "녹화 준비가 되었습니다." << endl;
	}
	else {
		cout << "녹화 문제 발생" << endl;
		return;
	}
	while (true) {
		cap >> frame;
		if (frame.empty()) {
			break;
		}
		output << frame; // 영상을 저장

		imshow("RECORDING", frame);
		if (waitKey(30) == 27) {
			break;
		}
	}
	destroyAllWindows();
}

//선 그리기 함수
void show_draw_lines() {
	Mat canvas(800, 800, CV_8UC3, Scalar(255, 255, 255));   // 800*800 흰색바탕의 canvas생성
	line(canvas, Point(50, 50), Point(200, 50), Scalar(0, 0, 255), 10);  // (50,50)에서 (200,50)으로 가는 두께 10의 빨간색 선 생성
	line(canvas, Point(50, 50), Point(200, 100), Scalar(255, 0, 255));

	arrowedLine(canvas, Point(50, 200), Point(150, 200), Scalar(0, 255, 0), 2); // (50,200)에서 (150,200)으로 가는 화살표 생성
	drawMarker(canvas, Point(30, 250), Scalar(0, 0, 255), MARKER_CROSS); // 십자가 모양 생성
	namedWindow("CANVAS", WINDOW_NORMAL);
	imshow("CANVAS", canvas);
	waitKey();
	destroyWindow("CANVAS");
}

//도형 그리기 함수
void show_draw_polygons() {
	Mat canvas = Mat(500, 500, CV_8UC3, Scalar(255, 255, 255));
	rectangle(canvas, Rect(50, 50, 150, 50), Scalar(0, 0, 255), 3);
	rectangle(canvas, Rect(50, 150, 100, 50), Scalar(0, 0, 255), -1);
	circle(canvas, Point(300, 120), 60, Scalar(255, 255, 0), -1, LINE_AA);
	ellipse(canvas, Point(120, 300), Size(60, 30), 20, 0, 270, Scalar(0, 255, 0),-1,LINE_AA);   // 타원 0도에서 270도까지 그리기
	vector<Point>points;
	points.push_back(Point(250, 250));
	points.push_back(Point(300, 250));
	points.push_back(Point(300, 300));
	points.push_back(Point(350, 300));
	points.push_back(Point(350, 350));
	points.push_back(Point(250, 350));
	polylines(canvas, points, true, Scalar(255, 0, 255), 5, -1); // 시작점과 끝점을 이을 땐 true 아닐 땐 false

	namedWindow("CANVAS",WINDOW_NORMAL);
	imshow("CANVAS", canvas);
	waitKey();
	destroyAllWindows();

}

//텍스트 그리기 함수
void show_draw_text() {
	Mat canvas = imread("lenna.bmp");
	putText(canvas, "LENNA", Point(250, 500), FONT_HERSHEY_TRIPLEX | FONT_ITALIC, 2 /*글자 크기*/, Scalar(255, 0, 0), 5/*폰트 두께*/, -1 /*라인타입*/); // |FONT_ITALIC을 하면 글씨체가 꺾인다.
	namedWindow("LENNA", WINDOW_NORMAL);
	imshow("LENNA", canvas);
	waitKey();
	destroyAllWindows();
}

//키보드 값 입력받는 함수
void keyboard_event() {
	Mat img = imread("lenna.bmp");
	if (img.empty()) return;
	imshow("LENNA", img);
	while (true) {
		int key_value = waitKey(0);
		if (key_value == 'I' or key_value == 'i') {   // i키를 누르면 반전
			img = ~img;
			imshow("LENNA", img);
		}
		else {
			if (key_value == 27 or key_value == 'Q' or key_value == 'q') break;    //q키를 누르면 반전
		}
	}
	destroyAllWindows();
}

//마우스로 그림그리는 함수
void mouse_event() {
	img = imread("lenna.bmp");
	if (img.empty()) return;
	namedWindow("LENNA", WINDOW_NORMAL);
	setMouseCallback("LENNA", on_mouse);
	imshow("LENNA", img);
	waitKey();
	destroyAllWindows();

}
static void on_mouse(int mouse_event, int mouse_x, int mouse_y, int flag, void*) {
	switch (mouse_event) {
	case EVENT_LBUTTONDOWN:
		pt_old = Point(mouse_x, mouse_y);
		cout << "x : " << mouse_x << " , " << "y : " << mouse_y << endl;
		break;
	case EVENT_LBUTTONUP:
		cout << "EVENT_LBUTTONUP" << mouse_x << " , " << mouse_y << endl;
		break;
	case EVENT_MOUSEMOVE:
		if (flag && EVENT_FLAG_LBUTTON) {   //왼쪽버튼을 누르고 이동하면 선 그리기
			line(img, pt_old, Point(mouse_x, mouse_y), Scalar(255, 0, 0), 2);
			imshow("LENNA", img);
			pt_old = Point(mouse_x, mouse_y);
		}
		break;
	}
	
}

//트랙바로 화면 조정하기
void trackbar_event() {
	Mat canvas(800, 800, CV_8UC1);
	namedWindow("CANVAS");
	createTrackbar("Level", "CANVAS", nullptr, 16, on_level_changed, (void*)&canvas);
	imshow("CANVAS", canvas);
	waitKey();
	destroyAllWindows();
}
void on_level_changed(int position, void* userdata) {
	Mat img = *(static_cast<Mat*>(userdata));
	img.setTo(position * 16);
	imshow("CANVAS", img);   // updating
}

//사진 일부분을 다른 사진과 합치는 함수
void mask_setTo() {
	Mat src = imread("lenna.bmp");
	Mat mask = imread("mask_smile.bmp", IMREAD_GRAYSCALE);
	if (src.empty() || mask.empty()) return;
	src.setTo(Scalar(0, 255, 0), mask); //마스크가 통과한 영역만 바뀜 (단, 행렬에 의한 계산이기에 두 이미지의 사이즈가 맞아야한다)
	imshow("SRC", src);
	imshow("MASK", mask);
	waitKey();
	destroyAllWindows();
}
void mask_copyTo() {
	Mat src = imread("airplane.bmp");
	Mat mask = imread("mask_plane.bmp",IMREAD_GRAYSCALE);
	Mat dst = imread("field.bmp");
	if (src.empty() || mask.empty() || dst.empty()) return;
	imshow("ORIGINAL", dst);
	imshow("SRC", src);
	imshow("MASK", mask);
	
	src.copyTo(dst, mask);
	imshow("CHANGED", dst);
	waitKey();
	destroyAllWindows();
}					//*

//프로그램이 실행되는 시간을 측정하는 함수
void time_inverse() {
	Mat img = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (img.empty()) return;
	Mat dst(img.rows, img.cols, img.type());  // img와 똑같은 크기의 matrix 생성
	TickMeter tick;
	tick.start(); // 실행시간 체크 시작
	for (int i = 0; i < img.rows; ++i) {
		for (int j = 0; j < img.cols; ++j) {
			dst.at<uchar>(i, j) = 255 - img.at<uchar>(i, j); //반전시킨 값을 저장
		}
	}
	tick.stop(); //실행시간 체크 종료
	cout << "걸린 시간 : " << tick.getTimeSec() << "초." << endl;
	imshow("IMG", img);
	imshow("DST", dst);
	waitKey();
	destroyAllWindows();
}

//여러가지 수치를 측정하는 함수(최대,최소,평균 등)
void useful_function() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	cout << static_cast<int>(sum(src)[0]) << endl;    // 픽셀 값들의 합
	cout << static_cast<int>(mean(src)[0]) << endl;	  // 픽셀 값들의 평균

	double min_value = 0.0;
	double max_value = 0.0;
	Point min_point;
	Point max_point;
	cout << "Min : " << min_value << " , " << "Max : " << max_value << endl;
	minMaxLoc(src, &min_value, &max_value, &min_point, &max_point);
	cout << "Min : " << min_value << " , " << "Max : " << max_value << endl;
	cout << "Min Position X : " << min_point.x << " , " << "Min Position Y : " << min_point.y << endl;
	cout << "Max Position X : " << max_point.x << " , " << "Max Position Y : " << max_point.y << endl;
	
}
