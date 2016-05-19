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


#include "utils.hpp"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

namespace ci {
    // load an entire image sequence in memory
    // dir: path in os-specific suffix-ready closed format, e.g., '/opt/data/'
    // format: sprintf-parsable string of the type 'img_%04.png'
    vector<cv::Mat> load_sequence(string dir, string format, int n, int zero) {
        
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
    
    void qshow(Mat img) {
        string wname = "Image display";
        namedWindow(wname, WINDOW_AUTOSIZE);
        imshow(wname, img);
        waitKey();
    }
    
    string type2str(int type) {
        string r;
        
        uchar depth = type & CV_MAT_DEPTH_MASK;
        uchar chans = 1 + (type >> CV_CN_SHIFT);
        
        switch ( depth ) {
            case CV_8U:  r = "8U"; break;
            case CV_8S:  r = "8S"; break;
            case CV_16U: r = "16U"; break;
            case CV_16S: r = "16S"; break;
            case CV_32S: r = "32S"; break;
            case CV_32F: r = "32F"; break;
            case CV_64F: r = "64F"; break;
            default:     r = "User"; break;
        }
        
        r += "C";
        r += (chans+'0');
        
        return r;
    }

}


