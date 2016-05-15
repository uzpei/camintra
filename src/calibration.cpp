//
//  calibration.cpp
//  camintra
//
//  Created by Emmanuel Piuze on 2016-05-15.
//  Copyright © 2016 uzpei. All rights reserved.
//

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