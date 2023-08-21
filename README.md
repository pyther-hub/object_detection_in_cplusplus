# yolov7

C++ YOLO v7 ONNX Runtime inference code for object detection in a Video.

## Dependecies:

* OpenCV 4.x
* ONNXRuntime 1.11+
* OS: Tested on MacOS
* CUDA 11+ [Optional]

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

Before running the executable you should convert your PyTorch model to ONNX if you haven't done it yet [tutorial](https://medium.com/deci-ai/tutorial-converting-a-pytorch-model-to-onnx-format-f1bbce156d2a).
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

## Output

* [ ] ![img](output.gif)

## References

- YOLOv7 repo: https://github.com/WongKinYiu/yolov7
- ONNXRuntime Inference examples: https://github.com/microsoft/onnxruntime-inference-examples
