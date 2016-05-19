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

#include "calibration.hpp"

#include <iostream>

#include "opencv2/core.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"

using namespace ci;
using namespace cv;
using namespace std;

Calibration::ptr Calibration::create() {
    return ptr(new Calibration());
}

Calibration::Calibration() {
    
}

vector<Point2f> Calibration::detect(cv::Mat& frame) {
    vector<Point2f> pts;
    int flags = CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE;

    // TODO: fast check erroneously fails with high distortions like fisheye
    flags |= CALIB_CB_FAST_CHECK;
    Size board(7, 9);
    
    bool found = findChessboardCorners(frame, board, pts, flags);
    
    cout << (found ? "Checkerboard detected!" : "Checkerboard not detected!") << endl;

    Mat viewGray;
    cvtColor(frame, viewGray, COLOR_BGR2GRAY);
    cornerSubPix( viewGray, pts, Size(11,11),
                 Size(-1,-1), TermCriteria( TermCriteria::EPS+TermCriteria::COUNT, 30, 0.1 ));

    drawChessboardCorners(frame, board, Mat(pts), found);
    
    return pts;
}