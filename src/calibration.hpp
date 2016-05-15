//
//  calibration.hpp
//  camintra
//
//  Created by Emmanuel Piuze on 2016-05-15.
//  Copyright © 2016 uzpei. All rights reserved.
//

#ifndef calibration_hpp
#define calibration_hpp

#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <vector>

namespace ci {
    class Calibration {
        
    public:
        typedef std::shared_ptr<Calibration> ptr;
        static ptr create();
        static ptr create_from();
        
        static std::vector<cv::Point2f> detect(cv::Mat& frame);

    protected:
        Calibration();
        std::vector<cv::Mat> frames;
        
    };
}
#endif /* calibration_hpp */
