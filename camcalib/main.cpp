//
//  main.cpp
//  camcalib
//
//  Created by Emmanuel Piuze on 2016-05-15.
//  Copyright © 2016 uzpei. All rights reserved.
//

// std includes
#include <iostream>
#include <string>

// cv includes
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

// product includes
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
