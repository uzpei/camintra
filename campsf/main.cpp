// MIT License
//
// Copyright (c) 2016 Emmanuel Piuze.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

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
    // Setup
    Mat dst;
    Mat kernel;
    Point anchor;
    double delta;
    int ddepth;
    int kernel_size;
    string window_name = "Convolution demo";
    char c;
    
    // Create window
    namedWindow( window_name, CV_WINDOW_AUTOSIZE );
    
    // Initialize arguments for the filter
    anchor = Point(-1, -1);
    delta = 0;
    ddepth = -1;
    
    int ind = 0;
    while( true )
    {
        // 'ESC' to exit
        c = waitKey(10);
        if (c == 27)
            break;
        
        // Normalized box filter kernel size
        kernel_size = 3 + 2*(ind%20);
        kernel = Mat::ones(kernel_size, kernel_size, CV_32F) / (float)(kernel_size*kernel_size);
        
        // Apply 2d filter
        filter2D(src, dst, ddepth , kernel, anchor, delta, BORDER_DEFAULT);
        imshow(window_name, dst);
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
    
    return 0;
}
