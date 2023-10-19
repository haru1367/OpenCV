#include <opencv2/opencv.hpp>

extern void filter_embossing();
extern void filter_blurring();
extern void filter_gaussian();
extern void filter_unsharp_mask();
extern void noise_gaussian();
extern void filter_bilateral();
extern void filter_median();

using namespace std;

int main() {
	//filter_embossing();
	//filter_blurring();
	//filter_gaussian();
	//filter_unsharp_mask();
	//noise_gaussian();
	//filter_bilateral();
	filter_median();
}
