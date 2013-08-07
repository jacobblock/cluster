#include "parser.h"
#include "classifier.h"

#include <iostream>
#include <string>
#include <memory>
#include <list>
#include <boost/regex.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

bool parseArgs(int argc, char* argv[], unsigned int &k, std::string &inputfile, std::string &outputfile); 

int main(int argc, char* argv[]) {
    unsigned int k = 0;
    std::string inputfile = "";
    std::string outputfile = "default.png";

    if(!parseArgs(argc, argv, k, inputfile, outputfile)) {
        return -1;
    }

    std::unique_ptr<Parser> parser(new ParseByCSVPoints(inputfile));
    std::list<cv::Vec2i> data = parser->parse();

    if(k > data.size()) {
        std::cout << "Number of classes is larger than the data set." << std::endl;
        return -1;
    }

    std::unique_ptr<Classifier> classifier(new KMeans(data, k, outputfile));
    classifier->start();

    return 0;
}

// Parse input arguments
bool parseArgs(int argc, char* argv[], unsigned int &k, std::string &inputfile, std::string &outputfile) {
    for(int i = 1; i < argc; ++i) {
        boost::regex command_regex("^-(.)(.+)");
        boost::smatch command_result;
        boost::regex_match(std::string(argv[i]), command_result, command_regex);
        char command = *command_result[1].str().c_str();
        std::string arg = command_result[2].str();

        switch(command) {
        case 'k':
            k = std::stoul(arg);
            break;
        case 'i':
            inputfile = arg;
            break;
        case 'o':
            outputfile = arg;
            break;
        default:
            std::cout << "Unrecognized argument -" << command_result[1].str() << std::endl;
            break;
        }
    }

    if(inputfile.empty()) {
        std::cout << "i argument should be a inputfile: \"-i[inputfile]\"" << std::endl;
        return false;
    }

    std::cout << "Number of clusters: "  << std::to_string(k) << std::endl;
    std::cout << "Input file: " << inputfile << std::endl;
    std::cout << "Output file: " << outputfile << std::endl;

    return true;
}
