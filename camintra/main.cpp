#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/photo.hpp>

#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

//hide the local functions in an anon namespace
namespace {
    
    int state_sharpen = 0;
    int state_denoise_chroma = 0;
    int state_denoise_luma = 0;
    int state_prefilter = 1;

    void postproc(Mat &frame) {
        
        // Work on central region
        const int p = min(frame.cols, frame.rows) / 2;
        Rect roi(frame.cols / 2-p/2, frame.rows / 2-p/2, p, p);
        Mat working;
        frame(roi).copyTo(working);
        
        // First denoising pass
        if (state_prefilter) {
//            Mat rgb[3];
//            split(working, rgb);
//            for (int i = 0; i <= 2; i++) {
//                Mat out;
//                cv::bilateralFilter(rgb[i], out, 5, 0.5*255, 2);
//                rgb[i] = out;
//            }
//            merge(rgb, 3, working);
            const float h = 3;
            const float hColor = 3;
            int tsize = 3;
            int ssize = 15;
            fastNlMeansDenoisingColored(working, working, h, hColor, tsize, ssize);
        }
        
        if ((state_sharpen || state_denoise_chroma || state_denoise_luma)) {
            // Convert to YUV
            Mat yuv;
            cvtColor(working, yuv, CV_BGR2YUV);
            
            Mat yuv_c[3];
            split(yuv, yuv_c);
            
            // Denoise luma
            if (state_denoise_luma) {
                Mat yd;
                cv::bilateralFilter(yuv_c[0], yd, 10, 0.03*255, 3);
                yuv_c[0] = yd;
            }
            
            // Denoise chroma
            if (state_denoise_chroma) {
                for (int i = 1; i <= 2; i++) {
                    Mat out;
                    cv::bilateralFilter(yuv_c[i], out, 25, 0.6*255, 5);
                    yuv_c[i] = out;
                }
            }
            
            if (state_sharpen) {
                // Sharpen luma
                Mat y_base;
                cv::bilateralFilter(yuv_c[0], y_base, 9, 0.1*255, 5);
                
                Mat y_basef;
                y_base.convertTo(y_basef, CV_32FC1, 1.0/255.0);
                
                Mat yf;
                yuv_c[0].convertTo(yf, CV_32FC1, 1.0/255.0);
                
                double mag = 1.5;
                Mat y_details = yf - y_basef;
                
                Mat sharp = yf + mag * y_details;
                sharp = max(0.0, min(sharp, 1.0));
                sharp.convertTo(yuv_c[0], CV_8UC1, 255);
            }
            
            // Go back to RGB
            merge(yuv_c, 3, yuv);
//            Mat out;
            cvtColor(yuv, working, CV_YUV2BGR);
//            out.copyTo(frame(roi));
        }
        working.copyTo(frame(roi));
        
        ostringstream s0,s1,s2,s3;
        int y = 1;
        s0 << "prefilter  = " << state_prefilter;
        cv::putText(frame, s0.str(), cv::Point(25,25*y++), cv::FONT_HERSHEY_PLAIN, 1.0,cv::Scalar(0,255,0), 1, CV_AA); // Anti-alias

        s1 << "luma denoise = " << state_denoise_luma;
        cv::putText(frame, s1.str(), cv::Point(25,25*y++), cv::FONT_HERSHEY_PLAIN, 1.0,cv::Scalar(0,255,0), 1, CV_AA); // Anti-alias
        
        s2 << "chroma denoise = " << state_denoise_chroma;
        cv::putText(frame, s2.str(), cv::Point(25,25*y++), cv::FONT_HERSHEY_PLAIN, 1.0,cv::Scalar(0,255,0), 1, CV_AA); // Anti-alias

        s3 << "sharpen = " << state_sharpen;
        cv::putText(frame, s3.str(), cv::Point(25,25*y++), cv::FONT_HERSHEY_PLAIN, 1.0,cv::Scalar(0,255,0), 1, CV_AA); // Anti-alias
        
    }
    
    void help(char** av) {
        cout << "NEW VERSION" << endl;
        
        cout << "The program captures frames from a video file, image sequence (01.jpg, 02.jpg ... 10.jpg) or camera connected to your computer." << endl
        << "Usage:\n" << av[0] << " <video file, image sequence or device number>" << endl
        << "q,Q,esc -- quit" << endl
        << "space   -- save frame" << endl << endl
        << "\tTo capture from a camera pass the device number. To find the device number, try ls /dev/video*" << endl
        << "\texample: " << av[0] << " 0" << endl
        << "\tYou may also pass a video file instead of a device number" << endl
        << "\texample: " << av[0] << " video.avi" << endl
        << "\tYou can also pass the path to an image sequence and OpenCV will treat the sequence just like a video." << endl
        << "\texample: " << av[0] << " right%%02d.jpg" << endl;
    }
    
    int process(VideoCapture& capture) {
        int n = 0;
        char filename[200];
        string window_name = "video | q or esc to quit";
        cout << "press space to save a picture. q or esc to quit" << endl;
        namedWindow(window_name, WINDOW_KEEPRATIO); //resizable window;
        Mat frame;
        
        for (;;) {
            capture >> frame;
            if (frame.empty())
                break;
            
            postproc(frame);
            
            imshow(window_name, frame);
            char key = (char)waitKey(30); //delay N millis, usually long enough to display and capture input
            
            switch (key) {
                case 'p':
                    state_prefilter = !state_prefilter;
                    break;
                case 'c':
                    state_denoise_chroma = !state_denoise_chroma;
                    break;
                case 's':
                    state_sharpen = !state_sharpen;
                    break;
                case 'l':
                    state_denoise_luma = !state_denoise_luma;
                    break;
                    
                case 'q':
                case 'Q':
                case 27: //escape key
                    return 0;
                case ' ': //Save an image
                    sprintf(filename,"filename%.3d.jpg",n++);
                    imwrite(filename,frame);
                    cout << "Saved " << filename << endl;
                    break;
                default:
                    break;
            }
        }
        return 0;
    }
}

int main(int ac, char** av) {
    
    if (ac != 2) {
        help(av);
        return 1;
    }
    std::string arg = av[1];
    VideoCapture capture(arg); //try to open string, this will attempt to open it as a video file or image sequence
    if (!capture.isOpened()) //if this fails, try to open as a video camera, through the use of an integer param
        capture.open(atoi(arg.c_str()));
    if (!capture.isOpened()) {
        cerr << "Failed to open the video device, video file or image sequence!\n" << endl;
        help(av);
        return 1;
    }
    return process(capture);
}