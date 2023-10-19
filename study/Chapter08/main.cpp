#include <opencv2/opencv.hpp>

using namespace std;

extern void sobel_edge();
extern void canny_edge();
extern void hough_lines();
extern void hough_circles();

int main() {
	//sobel_edge();
	//canny_edge();
	//hough_lines();
	hough_circles();
}
