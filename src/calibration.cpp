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

double Calibration::calibrate(std::vector<cv::Point2f> image_points, cv::Size board_size, Size image_size, Mat& camera_matrix) {
    vector<Mat> rvecs, tvecs;
    vector<float> reprojErrs;
    vector<Point3f> corners;
    float squareSizeX = 1.0f;
    float squareSizeY = 1.0f;
    
    for( int i = 0; i < board_size.height; ++i )
        for( int j = 0; j < board_size.width; ++j )
            corners.push_back(Point3f(float(j*squareSizeX), float(i*squareSizeY), 0));

    vector<vector<Point3f> > points3d;
    points3d.resize(1, corners);

    vector<vector<Point2f> > points2d;
    points2d.resize(1, image_points);

    int flags = /*CALIB_FIX_K3|*/CALIB_FIX_K4|CALIB_FIX_K5|CALIB_FIX_K6; //CALIB_FIX_K3; //CALIB_FIX_ASPECT_RATIO |  | CALIB_ZERO_TANGENT_DIST;
    TermCriteria criteria = TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 100, DBL_EPSILON);
    Mat distCoeffs = Mat::zeros(1, 5, CV_64F);
    double rms = calibrateCamera(points3d, points2d, image_size, camera_matrix, distCoeffs, rvecs, tvecs, flags, criteria);
    
    return rms;
}

vector<Point2f> Calibration::detect(cv::Mat& frame, Size board_size) {
    // Detection flags
    int flags = CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE;
    
    // TODO: fast check can fail with lenses with high distoration
    flags |= CALIB_CB_FAST_CHECK;
    vector<Point2f> pts;
    bool found = findChessboardCorners(frame, board_size, pts, flags);
    
    cout << (found ? "Checkerboard detected!" : "Checkerboard not detected!") << endl;
    
    if (!found)
        return pts;

    Mat viewGray;
    cvtColor(frame, viewGray, COLOR_BGR2GRAY);
    cornerSubPix( viewGray, pts, Size(11,11), Size(-1,-1), TermCriteria(TermCriteria::EPS+TermCriteria::COUNT, 100, 0.01 ));

    drawChessboardCorners(frame, board_size, Mat(pts), true);
    
    return pts;
}