//
//  utils.hpp
//  camintra
//
//  Created by Emmanuel Piuze on 2016-05-15.
//  Copyright © 2016 uzpei. All rights reserved.
//

#ifndef utils_hpp
#define utils_hpp

#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <vector>
#include <string>

using namespace std;

namespace ci {
    vector<cv::Mat> load_sequence(string dir, string format, int n, int zero=0);
}

#endif /* utils_hpp */
