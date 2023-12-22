#include <opencv2/opencv.hpp>
#include <iostream>


int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " </home/the/Desktop/mpmc/dsa> " << std::endl;
        return -1;
    }

    cv::Mat image1 = cv::imread(argv[1]);
    cv::Mat image2 = cv::imread(argv[2]);

    if (image1.empty() || image2.empty()) {
        std::cerr << "Error: Could not open one or both of the images." << std::endl;
        return -1;
    }

    if (image1.size() != image2.size()) {
        std::cerr << "Error: Images have different dimensions." << std::endl;
        return -1;
    }

    cv::Mat diff;
    cv::absdiff(image1, image2, diff);

    cv::Mat squared_diff;
    cv::multiply(diff, diff, squared_diff);

    cv::Scalar mse = cv::mean(squared_diff);
    double mse_value = mse[0] + mse[1] + mse[2];

    std::cout << "Mean Squared Error (MSE): " << mse_value << std::endl;

    if (mse_value == 0) {
        // Images match, send a signal to hardware component here.
        std::cout << "Authentication is successful" << std::endl;
        //hardware code
    } else {
        std::cerr << "Images do not match. Exiting program." << std::endl;
        return -1;
    }

    return 0;
}

