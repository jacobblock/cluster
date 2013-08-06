#include "classifier.h"

#include <iostream>
#include <random>

void KMeans::start() {
    // init();

    unsigned int iterations = 0;
    while(update()) {
        ++iterations;
        if(iterations > 1000) {
            std::cout << "Reached max iterations" << std::endl;
            break;
        }
    }
}

// Forgy init method
void KMeans::init(unsigned int k, std::list<cv::Vec2i> data) {

    std::random_device rd;
    std::default_random_engine gen(rd());
    for(unsigned int i = 0; i < k; ++i) {
        std::uniform_int_distribution<int> dis(0, data.size()-1);
        auto it = data.begin();
        std::advance(it, dis(gen));
        means.push_back(*data.erase(it));
        std::cout << means.back() << std::endl;
    }
}

bool KMeans::update() {
    return false;
}

//std::vector<cv::Vec2i> means = init(k, data);
//std::vector<std::vector<cv::Vec2i>> clusters = assign(means, data);
/*std::vector<std::vector<cv::Vec2i>> assign(std::vector<cv::Vec2i> const means, std::vector<cv::Vec2i> const data) {
    std::vector<std::vector<cv::Vec2i>> sets;*/
