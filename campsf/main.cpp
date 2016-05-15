//
//  main.cpp
//  campsf
//
//  Created by Emmanuel Piuze on 2016-05-15.
//  Copyright © 2016 uzpei. All rights reserved.
//

// std includes
#include <iostream>

// cv includes
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>

// prototype
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

// prod includes
#include "utils.hpp"

// namespaces
using namespace cv;
using namespace std;
using namespace ci;

void process(Mat& src) {
    /// Declare variables
    Mat dst;
    
    Mat kernel;
    Point anchor;
    double delta;
    int ddepth;
    int kernel_size;
    string window_name = "filter2D Demo";
    int c;
    
    /// Create window
    namedWindow( window_name, CV_WINDOW_AUTOSIZE );
    
    /// Initialize arguments for the filter
    anchor = Point( -1, -1 );
    delta = 0;
    ddepth = -1;
    
    /// Loop - Will filter the image with different kernel sizes each 0.5 seconds
    int ind = 0;
    while( true )
    {
        c = waitKey(10);
        /// Press 'ESC' to exit the program
        if( (char)c == 27 )
        { break; }
        
        /// Update kernel size for a normalized box filter
        kernel_size = 3 + 2*( ind%20 );
        kernel = Mat::ones( kernel_size, kernel_size, CV_32F )/ (float)(kernel_size*kernel_size);
        
        /// Apply filter
        filter2D(src, dst, ddepth , kernel, anchor, delta, BORDER_DEFAULT );
        imshow( window_name, dst );
        ind++;
    }
}

int main(int argc, const char * argv[]) {
    // TODO:
    // - load in data
    // - create forward convolution
    // - create deconvolution solver
    
    Mat img = imread("data/c1b.jpg", IMREAD_COLOR);
    
    cout << "Input image type: " << ci::type2str(img.type()) << endl;
    
    process(img);
    
//    ci::qshow(img);
    
    return 0;
}
