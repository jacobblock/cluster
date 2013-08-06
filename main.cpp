#include "parser.h"
#include "classifier.h"

#include <iostream>
#include <string>
#include <memory>
#include <list>
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


bool parseArgs(int argc, char* argv[], unsigned int &k, std::string &filepath); 

int main(int argc, char* argv[]) {
    unsigned int k = 0;
    std::string filepath = "";

    if(!parseArgs(argc, argv, k, filepath)) {
        return -1;
    }

    //std::unique_ptr<Parser> parser(new ParseByCSVPoints(filepath));
    //std::list<cv::Vec2i> data = parser->parse();

    ParseByCSVPoints parser(filepath);
    std::list<cv::Vec2i> data = parser.parse();

    if(k > data.size()) {
        std::cout << "Number of classes is larger than the data set." << std::endl;
        return -1;
    }

    //ClusterByKMeans kmeans(k, data);
    //kmean.start();

    //    std::unique_ptr<Cluster> cluster(new ClusterByLloyd());
/*    char window[] = "Clustering";
    cv::Mat image = cv::Mat::zeros(100, 100, CV_8UC3);
    
    MyEllipse(image, 90);
    MyEllipse(image, 0);
    MyEllipse(image, 45);
    MyEllipse(image, -45);

    cv::imshow(window, image);
    cv::waitKey(0);
    */

    return 0;
}

bool parseArgs(int argc, char* argv[], unsigned int &k, std::string &filepath) {
    // Check for correct number of arguments
    if(3 != argc) {
        std::cout << "Program should be run as \"cluster -k[clusters] -i[input file]\"." << std::endl;
        return false; 
    }

    // Parse cluster value
    boost::regex clusters_regex("-k([[:digit:]]+)");
    boost::smatch clusters_regex_result;
    if(boost::regex_match(std::string(argv[1]), clusters_regex_result, clusters_regex)) {
        k = std::stoul(clusters_regex_result[1].str());
        std::cout << "Number of clusters: "  << std::to_string(k) << std::endl;
    } else {
        std::cout << "k argument should be an unsigned integer: \"-k[unsigned int]\"" << std::endl;
        return false;
    }

    // Parse filepath
    boost::regex filepath_regex("-i(.+)");
    boost::smatch filepath_regex_result;
    if(boost::regex_match(std::string(argv[2]), filepath_regex_result, filepath_regex)) {
        filepath = filepath_regex_result[1].str();
        std::cout << "Input filepath: " << filepath << std::endl; 
    } else {
        std::cout << "i argument should be a filepath: \"-i[filepath]\"" << std::endl;
        return false;
    }

    return true;
}
