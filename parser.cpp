#include "parser.h"

#include <fstream>
#include <iostream>
#include <boost/regex.hpp>

Parser::Parser(std::string filepath)
    : filepath(filepath)
{}

ParseByCSVPoints::ParseByCSVPoints(std::string filepath)
    : Parser(filepath)
{}

std::list<cv::Vec2i> ParseByCSVPoints::parse() {
    std::cout << "Parsing by CSV Points" << std::endl;

    std::list<cv::Vec2i> data;

    // Open file for reading
    std::ifstream input(filepath);
    if(!input.is_open()) {
        std::cout << "Couldn't open file " << filepath << std::endl;
        return data;
    }

    boost::regex point_regex("(.+),(.+)");
    boost::smatch point_regex_result;
    for(std::string line; std::getline(input, line); ) {
        if(boost::regex_match(line, point_regex_result, point_regex)) {

#ifdef __MINGW32__
            int x = std::atoi(point_regex_result[1].str().c_str());
            int y = std::atoi(point_regex_result[2].str().c_str());
#else
            int x = std::stoul(point_regex_result[1].str());
            int y = std::stoul(point_regex_result[2].str());
#endif
            data.push_back(cv::Vec2i(x,y));
        } else {
            std::cout << "Regex format doesn't match line style" << std::endl;
            return data;
        }
    }

    return data;
}
