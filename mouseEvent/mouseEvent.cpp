#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Mat img, B;

int mx1, my1, mx2, my2;	// 마우스로 지정한 사각형의 좌표

bool cropping = false;		// 사각형 선택 중임을 나타내는 플래그 변수

void onMouse(int event, int x, int y, int flags, void* param)
{
	img.copyTo(B); //깊은 복사
	Mat image = imread("C:/OpenCV_File/images/contrast.jpg");
	int beta = 100;바
	if (event == EVENT_LBUTTONDOWN) {	// 마우스의 왼쪽 버튼을 누르면
		cropping = true;
		mx1 = x;		// 사각형의 좌측 상단 좌표 저장
		my1 = y;
	}
	else if (event == EVENT_MOUSEMOVE) {	//마우스가 움직이면 
		if (cropping == true) {
			mx2 = x;	// 사각형의 우측 하단 좌표 저장
			my2 = y;
			for (int y = my1; y < my2; y++) {
				for (int x = mx1; x < mx2; x++) {
					for (int c = 0; c < 3; c++) {
						B.at<Vec3b>(y, x)[c] =
							saturate_cast<uchar>(image.at<Vec3b>(y, x)[c] + beta);
						// 화면의 밝기가 밝아지는 부분  
					}
				}
			}
			imshow("image", B);
		}
	}
	else if (event == EVENT_LBUTTONUP) {	// 마우스의 왼쪽 버튼에서 손을 떼면
		cropping = false;
	}
}

int main()
{
	img = imread("C:/OpenCV_File/images/contrast.jpg");
	imshow("image", img);
	setMouseCallback("image", onMouse);
	while (1) {
		int key = waitKey(100);
		if (key == 'q') break;	// 사용자가 ‘q’를 누르면 종료
	}
	return 0;
}
