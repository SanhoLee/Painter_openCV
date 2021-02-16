#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;


int main(){
//   Creating videoCapture Object
//   카메라 id를 cap() 여기다가 입력하게됨.
//    1대면 0을 입력하면 된다고 함.
    VideoCapture cap(0);
    Mat img;

    while(true){

        cap.read(img);
        imshow("Image", img);
//        0 으로 딜레이를 설정하면 무한대로 정지상태로 표시될것임.
//        그래서 1 밀리세크 딜레이 되지만 거의 연속적으로 보여진다.
        waitKey(1);
    }
    return 0;
}

