#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;


VideoCapture cap(0);
Mat camImg, camResize;
Mat imgHSV;
Mat mask, maskResize;
int rtnWaitkey=0;

int hmin = 0, smin = 0, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;


// Color Detection ------------------------------------
//
int main(){
    // window size는 WINDOW_NORMAL 보다는 WINDOW_AUTOSIZE가 관리하기 쉬운듯.
    // 트랙바를 배치시킬 윈도우를 생성!
    namedWindow("Trackbars", WINDOW_AUTOSIZE);
    
    
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
        
        // inRange를 써서 HSV space의 값으로 하한, 상한 범위를 정하고 범위 내 값을 마스킹함
        inRange(imgHSV, lower, upper, mask);
        cout << hmin << "," << smin << "," << vmin << "," ;
        cout << hmax << "," << smax << "," << vmax << "," << endl;
        
        resize(mask, maskResize, Size(), 0.5, 0.5);
        resize(camImg, camResize, Size(), 0.5, 0.5);
        imshow("ImageMask", maskResize);
        imshow("Image Origin", camResize);
        rtnWaitkey = waitKey(1);
        if(rtnWaitkey == 27){return 0;}
    }
//

    return 0;
}
