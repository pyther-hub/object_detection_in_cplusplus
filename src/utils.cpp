#include "utils.h"

// Calculate the product of elements in a vector
size_t utils::vectorProduct(const std::vector<int64_t> &vector)
{
    if (vector.empty())
        return 0;

    size_t product = 1;
    for (const auto &element : vector)
        product *= element;

    return product;
}

// Convert a C-style string (char*) to a wide string (wstring)
std::wstring utils::charToWstring(const char *str)
{
    typedef std::codecvt_utf8<wchar_t> convert_type;
    std::wstring_convert<convert_type, wchar_t> converter;

    return converter.from_bytes(str);
}

// Load class names from a file and return as a vector of strings
std::vector<std::string> utils::loadNames(const std::string &path)
{
    // Load class names
    std::vector<std::string> classNames;
    std::ifstream infile(path);
    if (infile.good())
    {
        std::string line;
        while (getline(infile, line))
        {
            // Remove carriage return character if present
            if (line.back() == '\r')
                line.pop_back();

            classNames.emplace_back(line);
        }
        infile.close();
    }
    else
    {
        std::cerr << "ERROR: Failed to access class name path: " << path << std::endl;
    }

    return classNames;
}

// Visualize detected objects on an image
void utils::visualizeDetection(cv::Mat &image, std::vector<Detection> &detections,
                               const std::vector<std::string> &classNames)
{
    for (const Detection &detection : detections)
    {
        // Draw bounding box
        cv::rectangle(image, detection.box, cv::Scalar(229, 160, 21), 2);

        // Prepare label for the detected object
        int x = detection.box.x;
        int y = detection.box.y;
        int conf = static_cast<int>(std::round(detection.conf * 100));
        int classId = detection.classId;
        std::string label = classNames[classId] + " 0." + std::to_string(conf);

        // Draw label background
        int baseline = 0;
        cv::Size size = cv::getTextSize(label, cv::FONT_ITALIC, 0.8, 2, &baseline);
        cv::rectangle(image,
                      cv::Point(x, y - 25), cv::Point(x + size.width, y),
                      cv::Scalar(229, 160, 21), -1);

        // Put text label on the image
        cv::putText(image, label,
                    cv::Point(x, y - 3), cv::FONT_ITALIC,
                    0.8, cv::Scalar(255, 255, 255), 2);
    }
}

// Perform letterboxing on an image
void utils::letterbox(const cv::Mat &image, cv::Mat &outImage,
                      const cv::Size &newShape /*= cv::Size(640, 640)*/,
                      const cv::Scalar &color /*= cv::Scalar(114, 114, 114)*/,
                      bool auto_ /*= true*/,
                      bool scaleFill /*= false*/,
                      bool scaleUp /*= true*/,
                      int stride /*= 32*/)
{
    cv::Size shape = image.size();
    float r = std::min(static_cast<float>(newShape.height) / static_cast<float>(shape.height),
                       static_cast<float>(newShape.width) / static_cast<float>(shape.width));
    if (!scaleUp)
        r = std::min(r, 1.0f);

    float ratio[2]{r, r};
    int newUnpad[2]{static_cast<int>(std::round(static_cast<float>(shape.width) * r)),
                    static_cast<int>(std::round(static_cast<float>(shape.height) * r))};

    auto dw = static_cast<float>(newShape.width - newUnpad[0]);
    auto dh = static_cast<float>(newShape.height - newUnpad[1]);

    if (auto_)
    {
        dw = static_cast<float>((static_cast<int>(dw) % stride));
        dh = static_cast<float>((static_cast<int>(dh) % stride));
    }
    else if (scaleFill)
    {
        dw = 0.0f;
        dh = 0.0f;
        newUnpad[0] = newShape.width;
        newUnpad[1] = newShape.height;
        ratio[0] = static_cast<float>(newShape.width) / static_cast<float>(shape.width);
        ratio[1] = static_cast<float>(newShape.height) / static_cast<float>(shape.height);
    }

    dw /= 2.0f;
    dh /= 2.0f;

    if (shape.width != newUnpad[0] && shape.height != newUnpad[1])
    {
        cv::resize(image, outImage, cv::Size(newUnpad[0], newUnpad[1]));
    }

    int top = static_cast<int>(std::round(dh - 0.1f));
    int bottom = static_cast<int>(std::round(dh + 0.1f));
    int left = static_cast<int>(std::round(dw - 0.1f));
    int right = static_cast<int>(std::round(dw + 0.1f));
    cv::copyMakeBorder(outImage, outImage, top, bottom, left, right, cv::BORDER_CONSTANT, color);
}

// Scale bounding box coordinates based on image shapes
void utils::scaleCoords(const cv::Size &imageShape, cv::Rect &coords, const cv::Size &imageOriginalShape)
{
    float gain = std::min(static_cast<float>(imageShape.height) / static_cast<float>(imageOriginalShape.height),
                          static_cast<float>(imageShape.width) / static_cast<float>(imageOriginalShape.width));

    int pad[2] = {static_cast<int>((static_cast<float>(imageShape.width) - static_cast<float>(imageOriginalShape.width) * gain) / 2.0f),
                  static_cast<int>((static_cast<float>(imageShape.height) - static_cast<float>(imageOriginalShape.height) * gain) / 2.0f)};

    coords.x = static_cast<int>(std::round((static_cast<float>(coords.x - pad[0]) / gain)));
    coords.y = static_cast<int>(std::round((static_cast<float>(coords.y - pad[1]) / gain)));

    coords.width = static_cast<int>(std::round((static_cast<float>(coords.width) / gain)));
    coords.height = static_cast<int>(std::round((static_cast<float>(coords.height) / gain)));
}

// Clip a value within a specified range
template <typename T>
T utils::clip(const T &n, const T &lower, const T &upper)
{
    return std::max(lower, std::min(n, upper));
}
