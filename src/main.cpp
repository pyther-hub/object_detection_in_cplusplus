#include <iostream>
#include <opencv2/opencv.hpp>

#include "cmdline.h"
#include "utils.h"
#include "detector.h"

cv::Mat detect_in_frame(cv::Mat image, std::string modelPath, std::vector<std::string> classNames, bool isGPU)
{
    const float confThreshold = 0.3f;
    const float iouThreshold = 0.4f;

    YOLODetector detector{nullptr};
    std::vector<Detection> result;

    detector = YOLODetector(modelPath, isGPU, cv::Size(640, 640));

    // Load image and perform object detection
    result = detector.detect(image, confThreshold, iouThreshold);

    utils::visualizeDetection(image, result, classNames);

;

    return image;
}

int main(int argc, char *argv[])
{


    bool isGPU = false;                                                                                      
    const std::string classNamesPath = "../models/coco.names"; 
    const std::vector<std::string> classNames = utils::loadNames(classNamesPath);
    const std::string videopath = "../videos/media01.mp4";     
    const std::string modelPath = "../models/yolov7s.onnx"; 
    if (classNames.empty())
    {
        std::cerr << "Error: Empty class names file." << std::endl;
        return -1;
    }
    cv::VideoCapture cap(videopath);
    if (!cap.isOpened())
    {
        std::cerr << "Error: Could not open video file." << std::endl;
        return -1;
    }
    int frameWidth = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int frameHeight = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    double fps = cap.get(cv::CAP_PROP_FPS);
    cv::VideoWriter outputVideo("../videos/media01_output.mp4", cv::VideoWriter::fourcc('X', 'V', 'I', 'D'), fps, cv::Size(frameWidth, frameHeight));
    cv::Mat frame;
    cv::Mat obj_detect_frame;

    while (cap.read(frame))
    {

        // Write the processed frame to the output video
        obj_detect_frame = detect_in_frame(frame, modelPath, classNames, isGPU);
        outputVideo.write(obj_detect_frame);
    }
    return 0;
}


