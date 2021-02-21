#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// hsv space에서 아래와 같은 범위를 찾기위해서, 트랙바를 만들고,
// 하한, 상한 값을 트랙 바를 움직여 가면서 하한 상한 값을 찾을 수 있다.
// hue(색조)값은 최대가 179 이고, 나머지는 모두 255가 최대이다.
// 초기값 설정


// Color Detection ------------------------------------
//
int main(){
    
    VideoCapture cap(0);
    Mat img, camImg, imgHSV, mask;
    int rtnWaitkey=0;
    
    int hmin = 0, smin = 0, vmin = 0;
    int hmax = 179, smax = 255, vmax = 255;
    // window size는 WINDOW_NORMAL 보다는 WINDOW_AUTOSIZE가 관리하기 쉬운듯.
    // 트랙바를 배치시킬 윈도우를 생성!
    namedWindow("Trackbars", WINDOW_AUTOSIZE);
    
    // 윈도우를 특정사이즈로 변경할 경우 아래 사용.
     resizeWindow("Trackbars", 640, 200);
    
    // 6개의 트랙바 생성, 먼저 생성한 Trackbars라는 윈도우에 붙여준다.
    // &변수 , 각각 트랙바를 움직이면 이 변수의 값이 그에 맞게 변경된다.
    createTrackbar("Hue Min", "Trackbars", &hmin, 179);
    createTrackbar("Hue Max", "Trackbars", &hmax, 179);
    createTrackbar("Sat Min", "Trackbars", &smin, 255);
    createTrackbar("Sat Max", "Trackbars", &smax, 255);
    createTrackbar("Val Min", "Trackbars", &vmin, 255);
    createTrackbar("Val Max", "Trackbars", &vmax, 255);
    

    
    if(cap.isOpened()){
        cout << "\n Camera is On NOW. \n" << endl;
    } else{
        cout << "\n Something wrong with your CAMERA. \n" << endl;
    }

    while (true) {
        cap.read(camImg);
        
        cvtColor(camImg, imgHSV, COLOR_BGR2HSV);
        
        Scalar lower(hmin,smin,vmin);
        Scalar upper(hmax,smax,vmax);

        // inRange를 써서 하한, 상한 값 내의 색정보를 마스킹함?
        inRange(imgHSV, lower, upper, mask);

        imshow("Image", camImg);
        imshow("ImageHSV", imgHSV);
        rtnWaitkey = waitKey(1);
        if(rtnWaitkey == 27){return 0;}
    }


    return 0;
}
