//
//  utils.cpp
//  camintra
//
//  Created by Emmanuel Piuze on 2016-05-15.
//  Copyright © 2016 uzpei. All rights reserved.
//

#include "utils.hpp"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

// load an entire image sequence in memory
// dir: path in os-specific suffix-ready closed format, e.g., '/opt/data/'
// format: sprintf-parsable string of the type 'img_%04.png'
vector<cv::Mat> ci::load_sequence(string dir, string format, int n, int zero) {
    
    vector<cv::Mat> loaded;
    
    for (int i = 0; i < n; ++i)
    {
        // Assign filename
        char sb[1000];
        sprintf(sb, format.c_str(), zero + i);
        string fpath = dir + string(sb);
        
        cout << "Attempt load from " << fpath << endl;
        Mat img;
        img = imread(fpath.c_str(), IMREAD_COLOR);
        cout << "Loaded image of size" << img.cols << "x" << img.rows << endl;
        loaded.push_back(img);
    }
    
    return loaded;
}