#include <iostream>
#include <cstdio>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

static double w = 100;

int main(int argc, char* argv[]) {


    if(3 != argc) {
        std::cout << "Program should be run as \"cluster -k[clusters] -i[input file]\"." << std::endl;
        return -1;
    }

    unsigned int k = 0;
    if(1 != std::sscanf(argv[1],"-k%u", &k)) {
        std::cout << "k argument should be an unsigned integer" << std::endl;
        return -1;
    } else {
        std::cout << "Number of clusters (k): " << std::to_string(k) << std::endl;
    }
    char window[] = "Clustering";
    cv::Mat image = cv::Mat::zeros(100, 100, CV_8UC3);
    MyEllipse(image, 90);
    MyEllipse(image, 0);
    MyEllipse(image, 45);
    MyEllipse(image, -45);

    cv::imshow(window, image);
    cv::waitKey(0);

    //	std::string inputfile(argv[2]);
    //	std::cout << "Input file path: " << inputfile << std::endl;

    return 0;
}

