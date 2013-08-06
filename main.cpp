#include <iostream>
#include <cstdio>
#include <string>
#include <regex>
#include <memory>
#include <fstream>
#include <boost/regex.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

static double w = 100;

void MyEllipse(cv::Mat img, double angle) {
    int thickness = 2;
    int lineType = 8;

    cv::ellipse(img,
                cv::Point(w/2.0, w/2.0),
                cv::Size(w/4.0, w/16.0),
                angle,
                0,
                360,
                cv::Scalar(255, 0, 0),
                thickness,
                lineType);
}


int main(int argc, char* argv[]) {
    // Check for correct number of arguments
    if(3 != argc) {
        std::cout << "Program should be run as \"cluster -k[clusters] -i[input file]\"." << std::endl;
        return -1;
    }

    // Parse cluster value
    boost::regex clusters_regex("-k([[:digit:]]+)");
    boost::smatch clusters_regex_result;
    unsigned int k = 0;
    if(boost::regex_match(std::string(argv[1]), clusters_regex_result, clusters_regex)) {
        k = std::stoul(clusters_regex_result[1].str());
        std::cout << "Number of clusters: "  << std::to_string(k) << std::endl;
    } else {
        std::cout << "k argument should be an unsigned integer: \"-k[unsigned int]\"" << std::endl;
        return -1;
    }

    // Parse filepath
    boost::regex filepath_regex("-i(.+)");
    boost::smatch filepath_regex_result;
    std::string filepath = "";
    if(boost::regex_match(std::string(argv[2]), filepath_regex_result, filepath_regex)) {
        filepath = filepath_regex_result[1].str();
        std::cout << "Input filepath: " << filepath << std::endl; 
    } else {
        std::cout << "i argument should be a filepath: \"-i[filepath]\"" << std::endl;
        return -1;
    }
  
    std::ifstream input(filepath);

    if(!input.is_open()) {
        std::cout << "Couldn't open file " << filepath << std::endl;
        return -1;
    }
    std::vector<cv::Vec2i> data;
    boost::regex point_regex("(.+),(.+)");
    boost::smatch point_regex_result;
    for(std::string line; std::getline(input, line); ) {
       if(boost::regex_match(line, point_regex_result, point_regex)) {
           int x = std::stoul(point_regex_result[1].str());
           int y = std::stoul(point_regex_result[2].str());
           data.push_back(cv::Vec2i(x,y));
           std::cout << data.back() << std::endl;
        } else {
            std::cout << "Regex format doesn't match line style" << std::endl;
            return -1;
        }
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

