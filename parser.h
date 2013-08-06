#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <list>
#include <opencv2/core/core.hpp>

class Parser {
    public:
        Parser(std::string filepath);
        virtual std::list<cv::Vec2i> parse() = 0;

        std::string filepath = "";
};

class ParseByCSVPoints : public Parser {
    public:
        ParseByCSVPoints(std::string filepath);
        std::list<cv::Vec2i> parse();
};

#endif
