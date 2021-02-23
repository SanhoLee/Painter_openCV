#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat img;
Mat imgResize;

// vector newPoints ->> {x,y,color_index}
vector<vector<int>> newPoints;

int rtnKey=0;

// (colorPicker 사용) mask에 사용할 색을 HSV space에서 성분값을 찾아둔다.
// hmin,smin,vmin,hmax,smax,vmax
vector<vector<int>> myColors
{
    {0,139,190,8,221,255}, // red
    {88,210,218,111,255,255}, // blue
};

// myColors에서 검출된 객체에 대해서, BGR space 상의 색상 정보를 준비함. 추후, 이 데이터로 화면에 출력시킴.
vector<Scalar> myColorValues {{0,0,255}, // red
                             {255,0,0},}; // blue
  
Point getContours(Mat imgDil){
    
    // Description  : 입력된 이미지에서 외곽 테두리를 찾습니다.
    // input        : mask 처리된 이미지 소스
    // return       : 검출된 윤곽을 둘러싸는 직사각형에서 상단 센터 좌표를 반환함
    //
    // contours     : 각 도형의 윤관석을 표현하는 포인트 요소를 벡터로 표현해서 가지고 있게 된다.
    // hierarchy    : 4개 정수를 그 요소로 하는 벡터를 정의해줬다.
    
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    
    // 소스 이미지로 부터 윤곽선을 찾고, contour 벡터 안에 Point정보를 저장한다.
    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    
    // conPoly      : 윤곽선을 구성하는 데이터를 다각형 형태로 담기 위한 변수 선언.
    // boundRect    : 검출한 윤곽선을 감싸는 직사각형 도형을 생성할건데, 직사각형 데이터를 담아주기 위한 준비.
    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundRect(contours.size());
    
    Point myPoint(0,0);
    
    for(int i = 0 ; i < contours.size(); i++)
    {
        int area = contourArea(contours[i]);
        if(area > 500){
            
            // contours요소의 아크 길이를 리턴. 두번째 요소는 아크가 닫혀있으면(boolean true) 그 값을 리턴하는 듯.
            float peri = arcLength(contours[i], true);
            // 감지한 윤곽에 대해서, 해당 윤곽이 사각형인지 삼각형인지를 파악한다. 선분 갯수를 계산해서 아웃풋 어레이로 반환한다.
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
            
            // 검출된 객체를 표시하는 윤곽선 갯수를 출력한다.
            cout << conPoly[i].size() << endl;
            
            // 이렇게 하면 rectangle 메소드를 이용해서 사각형을 그릴수 있다.
            boundRect[i] = boundingRect(conPoly[i]);
            myPoint.x = boundRect[i].x + boundRect[i].width/2;
            myPoint.y = boundRect[i].y;
            
            
            // 도형의 윤곽선을 그려준다. 다각형 형태의 윤곽선을 뿌려줬기 때문에, 원일 경우 매끄럽지않은 각이 있는 원 형태를 볼수 있다.
             drawContours(imgResize, conPoly, i, Scalar(255,0,255), 2);
            // rectangle(imgResize, boundRect[i].tl(), boundRect[i].br(), Scalar(0,255,0),5);
        }
    }
    return myPoint;
}

vector<vector<int>> findColor(Mat img){

    Mat imgHSV;
    
    for(int i=0;i<myColors.size();i++){
        
        cvtColor(img, imgHSV, COLOR_BGR2HSV);
        
        Scalar lower(myColors[i][0],myColors[i][1],myColors[i][2]);
        Scalar upper(myColors[i][3],myColors[i][4],myColors[i][5]);
        
        Mat mask;
        
        inRange(imgHSV, lower, upper, mask);
        Point myPoint = getContours(mask);
        
        if(myPoint.x != 0 && myPoint.y != 0){
            newPoints.push_back({myPoint.x,myPoint.y,i});
        }
    }
    return newPoints;
}

void drawCanvas(vector<vector<int>> newPoints, vector<Scalar> myColorValues){
    
    for(int i=0;i<newPoints.size();i++){
        circle(
               imgResize,
               Point(newPoints[i][0], newPoints[i][1]),
               19,
               myColorValues[newPoints[i][2]],
               FILLED
               );
    }
}

int main(){
    VideoCapture cap(0);

    
    if(cap.isOpened()){
        cout << "\n Camera is On NOW. \n" << endl;
    }else{
        cout << "\n Sth Wrong with your CAMERA ACCESS. \n" << endl;
        return -1;
    }

    while(true){
        cap.read(img);
        resize(img, imgResize, Size(), 0.5,0.5);
        
        newPoints = findColor(imgResize);
        drawCanvas(newPoints, myColorValues);
        
        
        imshow("Image", imgResize);
        rtnKey = waitKey(1);
        if(rtnKey == 27) {return 0;}
    }
    return 0;
}

