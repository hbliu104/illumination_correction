#include <iostream>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{

     Mat src, bkg, dst;

     src = imread(argv[1], CV_LOAD_IMAGE_COLOR);

     if (src.empty())
         return -1;

//     namedWindow("src", WINDOW_NORMAL);
//     resizeWindow("src", 600, 600);

//     namedWindow("bkg", WINDOW_NORMAL);
//     resizeWindow("bkg", 600, 600);

//     namedWindow("dst", WINDOW_NORMAL);
//     resizeWindow("dst", 600, 600);

//     imshow("src", src);
     imwrite("src.jpg", src);

     Mat z;

     /*
     Mat hls;
     cvtColor(src, hls, COLOR_RGB2HLS );
     vector<Mat> chs;
     split(hls, chs);

     chs[1].convertTo(z, CV_64F, 1.0/255);
     */

     src.convertTo(z, CV_64F, 1.0/255);

     double r = z.rows;
     double c = z.cols;

     vector<double> x(c), y(r);

     for (int i = 0; i < c; ++i)
         x[i] = i;

     for (int i = 0; i < r; ++i)
         y[i] = i;

     Mat x1(x), y1(y);

     Mat xmat = repeat(x1.t() / (c-1), r, 1).reshape(0, r*c);
     Mat ymat = repeat(y1 / (r-1), 1, c).reshape(0, r*c);

     int order = 7;
     Mat A(Mat::ones(c*r, (order+1)*(order+2)/2, CV_64F));

     int item = 1;

     for (int layer = 2; layer <= order+1; ++layer)
     {
         multiply(A.col(item-layer+1), xmat, A.col(item));

         for (int idx = item+1; idx < item+layer-1; ++idx)
             multiply(A.col(idx-layer), A.col(idx-layer+1), A.col(idx));

         multiply(A.col(item-1), ymat, A.col(item+layer-1));

         item += layer;
     }

     Mat m, d;
     for (int i = 1; i < A.cols; ++i)
     {
         meanStdDev(A.col(i), m, d);
         A.col(i) = (A.col(i) - m.at<double>(0,0)) / d.at<double>(0,0);
     }

     Mat B = z.reshape(1, r*c);

     Mat w = ( A.t() * A ).inv(DECOMP_SVD) * ( A.t() * B );

     cout << w << endl;

     bkg = Mat(A * w).reshape(z.channels(), r);

     dst = z - bkg + Scalar::all(0.3);

     bkg.convertTo(bkg, CV_8U, 255);
     dst.convertTo(dst, CV_8U, 255);

     imwrite("bkg.jpg", bkg);
     imwrite("dst.jpg", dst);

     /*
     dst.copyTo(chs[1]);
     merge(chs, hls);
     cvtColor(hls, hls, COLOR_HLS2RGB);
     imshow("dst2", hls);
     */

     waitKey();

     return 0;
}
