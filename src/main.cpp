#include <iostream>
#include <opencv2/opencv.hpp>

#include "cmdline.h"
#include "utils.h"
#include "detector.h"
// cv::Mat flipImage(const cv::Mat inputImage)
// {
//     cv::Mat flippedImage;
//     cv::flip(inputImage, flippedImage, 1); // Flip along the vertical axis (horizontal flip)
//     return flippedImage;
// }
cv::Mat detect_in_frame(cv::Mat image, std::string modelPath, std::vector<std::string> classNames, bool isGPU)
{
    const float confThreshold = 0.3f;
    const float iouThreshold = 0.4f;

    YOLODetector detector{nullptr};
    std::vector<Detection> result;
    // obj_detect_frame = detect_in_frame(frame, modelPath, classNames, isGPU);
    detector = YOLODetector(modelPath, isGPU, cv::Size(640, 640));
    // std::cout << "Model was initialized." << std::endl;
    // Load image and perform object detection
    result = detector.detect(image, confThreshold, iouThreshold);
    // std::cout << "Detection completed." << std::endl;
    // try
    // {
    //     // Initialize YOLO detector

    // }
    // catch (const std::exception &e)
    // {
    //     std::cerr << e.what() << std::endl;
    //     return -1;
    // }

    // Visualize detected objects
    utils::visualizeDetection(image, result, classNames);

    // Display and optionally save the result
    // cv::imshow("Result", image);
    // cv::imwrite("result.jpg", image);  // Uncomment this line to save the result image
    // cv::waitKey(0);

    return image;
}

int main(int argc, char *argv[])
{


    // Parse command-line arguments
    // cmdline::parser cmd;
    // cmd.add<std::string>("model_path", 'm', "Path to ONNX model.", true, "yolov5.onnx");
    // cmd.add<std::string>("image", 'i', "Image source to be detected.", true, "bus.jpg");
    // cmd.add<std::string>("class_names", 'c', "Path to class names file.", true, "coco.names");
    // cmd.add("gpu", '\0', "Inference on CUDA device.");
    // cmd.parse_check(argc, argv);

    bool isGPU = false;                                                                                      // cmd.exist("gpu");
    const std::string classNamesPath = "/Users/sudhanshu/Desktop/work/yolov5-onnxruntime/models/coco.names"; // cmd.get<std::string>("class_names");
    const std::vector<std::string> classNames = utils::loadNames(classNamesPath);
    const std::string videopath = "/Users/sudhanshu/Desktop/work/yolov5-onnxruntime/videos/video01.mp4";     // cmd.get<std::string>("image");
    const std::string modelPath = "/Users/sudhanshu/Desktop/work/yolov5-onnxruntime/models/yolov7s.onnx"; // cmd.get<std::string>("model_path");
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
    cv::VideoWriter outputVideo("/Users/sudhanshu/Desktop/work/yolov5-onnxruntime/videos/video01_output.mp4", cv::VideoWriter::fourcc('X', 'V', 'I', 'D'), fps, cv::Size(frameWidth, frameHeight));
    cv::Mat frame;
    cv::Mat obj_detect_frame;

    while (cap.read(frame))
    {
        // Call your custom processing function
        // cv::Mat processedFrame = detect_in_frame(frame);

        // Write the processed frame to the output video
        obj_detect_frame = detect_in_frame(frame, modelPath, classNames, isGPU);
        outputVideo.write(obj_detect_frame);

        // Display the processed frame (optional)
        // cv::imshow("Processed Frame", processedFrame);

        // // Break the loop if the 'q' key is pressed
        // if (cv::waitKey(1) == 'q')
        // {
        //     break;
        // }
    }
    return 0;
}


