# yolov7

C++ YOLO v7 ONNX Runtime inference code for object detection in a Video.

## Dependecies:
- OpenCV 4.x
- ONNXRuntime 1.11+
- OS: Tested on MacOS
- CUDA 11+ [Optional]

## Install:
```bash
brew install onnxruntime
brew install opencv
```


## Build:
To build the project you should run the following commands.

```bash
mkdir build
cd build
cmake .. 
make
```

## Run
Before running the executable you should convert your PyTorch model to ONNX if you haven't done it yet.
`On MacOS`: to run the executable you should add OpenCV and ONNX Runtime libraries which we did using `Homebrew`

Change file path and names.
```c++
    const std::string classNamesPath = "../models/coco.names"; 
    const std::vector<std::string> classNames = utils::loadNames(classNamesPath);
    const std::string videopath = "../videos/media01.mp4";     
    const std::string modelPath = "../models/yolov7s.onnx";
```
Note:- current directory should be the build.

Run from CLI:
```bash
./yolo_ort
```

## Demo

YOLOv7s onnx:

<p align="center">
  <a href="images/bus_result.jpg"><img src="images/bus_result.jpg" style="width:60%; height:60%;"/></a>
</p>
<p align="center">
  <a href="images/zidane_result.jpg"><img src="images/zidane_result.jpg" style="width:60%; height:60%;"/></a>
</p>


## References

- YOLO v5 repo: https://github.com/ultralytics/yolov5
- YOLOv5 Runtime Stack repo: https://github.com/zhiqwang/yolov5-rt-stack
- ONNXRuntime Inference examples: https://github.com/microsoft/onnxruntime-inference-examples
