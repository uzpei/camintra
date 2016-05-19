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
#include <string>

// cv includes
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

// prod includes
#include "utils.hpp"
#include "calibration.hpp"

// namespaces
using namespace cv;
using namespace std;
using namespace ci;

int main(int argc, const char * argv[]) {
    // Load some fake calibration data
    vector<Mat> imgs = ci::load_sequence("data/", "c%01db.jpg", 5, 1);
    
    // Display detection
    string wname = "Calibration board detection";
    namedWindow(wname, WINDOW_AUTOSIZE);
    for (vector<Mat>::iterator it = imgs.begin(); it != imgs.end(); ++it) {
        Mat current = *it;
        
        Calibration::detect(current);
        
        imshow(wname, current);
        waitKey();
    }
    
    return 0;
}
