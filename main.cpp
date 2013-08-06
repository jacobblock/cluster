#include <iostream>
#include <cstdio>
#include <string>
#include <regex>
#include <memory>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

static double w = 100;



int main(int argc, char* argv[]) {
    // Check for correct number of arguments
    if(3 != argc) {
        std::cout << "Program should be run as \"cluster -k[clusters] -i[input file]\"." << std::endl;
        return -1;
    }

    // Parse cluster value
/*    unsigned int k = 0;
    if(std::sscanf(argv[1],"-k%u", &k)) {
        std::cout << "Number of clusters (k): " << std::to_string(k) << std::endl;
    } else {
        std::cout << "k argument should be an unsigned integer: \"-k<unsinged int>\"" << std::endl;
        return -1;
    }*/

    
    /*if(std::sscanf(argv[1], "-i%s", &filepath)) {
        
    } else {
        std::cout << "i argument should be a filepath: \"-i[filepath]\"" << std::endl;
        return -1;
    }*/

    unsigned int k = 0;
    if(1 != std::sscanf(argv[1],"-k%u", &k)) {
        std::cout << "k argument should be an unsigned integer" << std::endl;
        return -1;
    } else {
        std::cout << "Number of clusters (k): " << std::to_string(k) << std::endl;
    }
    std::ifstream input(filepath);

    if(!input.is_open()) {
        std::cout << "Couldn't open file " << filepath << std::endl;
        return -1;
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

