#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include "opencv2/highgui/highgui.hpp"
 
using namespace cv;

int p1, p2;
Mat dice, canny;

void on_trackbar(int, void*) {
    Canny(dice, canny, p1, p2);
    imshow("canny", canny);
}

int main(int argc, const char** argv)
{
    dice = imread("dice.jpg", 0);
    p1 = 100;
    p2 = 200;

    Canny(dice, canny, 375, 820);
    imshow("canny", canny);
    createTrackbar("p1","canny",&p1,1000,on_trackbar);
    createTrackbar("p2","canny",&p2,1000,on_trackbar);
    waitKey();

    int num = 0;
    for(int y=0;y<canny.size().height;y++)
    {
        uchar *row = canny.ptr(y);
        for(int x=0;x<canny.size().width;x++)
        {
            if(row[x] <= 128)
            {
                int area = floodFill(canny, Point(x,y), CV_RGB(0,0,160));
                printf("filling %d, %d gray, area is %d\n", x, y, area);
                if(area>10 && area < 50) num++;
            }
        }
    }
    printf("number is %d\n", num);
    imshow("dice", dice);
    waitKey();

    return 0;
}
