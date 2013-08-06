#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <string>
#include <list>
#include <vector>
#include <opencv2/core/core.hpp>

class Classifier {
    public:
        unsigned int k;
        std::list<cv::Vec2i> data;
        virtual void start() = 0;
};

class KMeans : public Classifier {
    std::vector<cv::Vec2i> means;

    void start();

    // Forgy init method
    void init(unsigned int k, std::list<cv::Vec2i> data);
    void assign();
    bool update();

    //std::vector<cv::Vec2i> means = init(k, data);
    //std::vector<std::vector<cv::Vec2i>> clusters = assign(means, data);
    
};

#endif
