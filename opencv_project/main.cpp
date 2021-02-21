//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//#include <iostream>
//
//using namespace std;
//using namespace cv;


//void findColor(Mat img){
//
//    Mat imgHSV;
//
//    int hmin = 0, smin = 0, vmin = 0;
//    int hmax = 179, smax = 255, vmax = 255;
//
//    cvtColor(img, imgHSV, COLOR_BGR2HSV);
//
//    Scalar lower(hmin,smin,vmin);
//    Scalar upper(hmax,smax,vmax);
//    // inRange를 써서 하한, 상한 값 내의 색정보를 마스킹함?
//    inRange(imgHSV, lower, upper, mask);
//
//}

//int main(){
////   Creating videoCapture Object
////   카메라 id를 cap() 여기다가 입력하게됨.
////    1대면 0을 입력하면 된다고 함.
//    VideoCapture cap(0);
//    Mat img;
//
//    while(true){
//
//        cap.read(img);
////        findColor(img);
//        imshow("Image", img);
////        0 으로 딜레이를 설정하면 무한대로 정지상태로 표시될것임.
////        그래서 1 밀리세크 딜레이 되지만 거의 연속적으로 보여진다.
//        waitKey(1);
//    }
//    return 0;
//}

