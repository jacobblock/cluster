#include "classifier.h"

#include <iostream>
#include <random>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>

#define _USE_MATH_DEFINES

Classifier::Classifier(std::list<cv::Vec2i> data, unsigned int k, double convergence, unsigned int max_iterations)
    : data(data)
    , k(k)
    , convergence(convergence)
    , max_iterations(max_iterations) 
{}

void Classifier::start() {
    init();

    unsigned int iteration = 0;
    while(update()) {
        ++iteration;
        if(iteration > max_iterations) {
            std::cout << "Exiting: Reached max iterations" << std::endl;
            return;
        }
    }
}

KMeans::KMeans(std::list<cv::Vec2i> data, unsigned int k, double convergence, unsigned int max_iterations)
    : Classifier(data, k, convergence, max_iterations)
{
    cv::namedWindow(window, cv::WINDOW_AUTOSIZE);

    cv::Vec2i topright, bottomleft;
    topright = data.front();
    bottomleft = data.front();
    for(auto point : data) {
        if(point[0] > topright[0]) {
            topright[0] = point[0];
        }
        if(point[1] > topright[1]) {
            topright[1] = point[1];
        }
        if(point[0] < bottomleft[0]) {
            bottomleft[0] = point[0];
        }
        if(point[1] < bottomleft[1]) {
            bottomleft[1] = point[1];
        }
    }
    int width = (topright[0] - bottomleft[0])+circle_radius;
    int height = (topright[1] - bottomleft[1])+circle_radius;
    image = cv::Mat::zeros(width, height, CV_8UC3);
    colors = colormodel(k);
    std::cout << topright << std::endl;
    std::cout << bottomleft << std::endl;
}

// Forgy init method. Set k means to random points.
void KMeans::init() {
    std::list<cv::Vec2i> data(this->data);
    std::random_device rd;
    std::default_random_engine gen(rd());
    for(unsigned int i = 0; i < k; ++i) {
        std::uniform_int_distribution<int> dis(0, data.size()-1);
        auto it = data.begin();
        std::advance(it, dis(gen));
        this->means.push_back(*it);
        data.erase(it);
    }
}

std::vector<std::list<cv::Vec2i>> KMeans::assign_sets() const {
    std::vector<std::list<cv::Vec2i>> sets(this->means.size(), std::list<cv::Vec2i>());
    std::cout << "Number of sets: " << std::to_string(sets.size()) << std::endl;

    for(auto point : this->data) {
        int index = 0;
        cv::Vec2i dif;
        cv::pow(point - this->means[0], 2.0, dif);
        double dist;
        double min = dif[0] + dif[1];
        for(unsigned int i = 0; i < this->means.size(); ++i) {
            cv::pow(point - this->means[i], 2.0, dif);
            dist = dif[0] + dif[1];
            if (dist <= min) {
                min = dist;
                index = i;
            }
        }
        sets[index].push_back(point);
    }

    return sets;
}

std::vector<cv::Vec2i> KMeans::update_means() const {
    std::vector<cv::Vec2i> means;
    
    int i = 0;
    for(auto set : this->sets) {
        cv::Vec2i v;
        for(auto point : set) {
            v += point;
        }

        v = v / (double)set.size();

        means.push_back(v);
        std::cout << std::to_string(i) << " Old: " << this->means[i] << " New: " << means.back() << std::endl;
        ++i;
    }
//    means = this->means;
    
    return means;
}

bool KMeans::update() {
    this->sets = assign_sets();
    std::vector<cv::Vec2i> means2 = update_means();
    display();

/*    double dif = cv::norm(means2 - this->means);
    means = std::move(means2);

    return dif >= this->convergence; // Return false (stop condition) if convergence reached
    */

    return false;
}

void KMeans::display() {
    auto it = colors.cbegin();
    for(auto set : sets) {
        for(auto point : set) {
            circle(image, point, circle_radius, *it, -1, 8);
        }
        ++it;
    }

    cv::imshow(window, image);
    cv::waitKey(0);
}

//std::vector<std::vector<cv::Vec2i>> clusters = assign(means, data);
/*std::vector<std::vector<cv::Vec2i>> assign(std::vector<cv::Vec2i> const means, std::vector<cv::Vec2i> const data) {
    std::vector<std::vector<cv::Vec2i>> sets;*/

// Based off of http://stackoverflow.com/a/10731340/361707
std::vector<cv::Scalar> KMeans::colormodel(unsigned int k) const {
    std::vector<cv::Scalar> colors;
    for(int i = 0; i < k; ++i) {
        double angle = i*2*M_PI/k;

        double Y = 0.5;
        double U = std::cos(angle);
        double V = std::sin(angle);

        colors.push_back(cv::Scalar(255*(Y+V/0.88), 255*(Y-0.38*U-0.58*V), 255*(Y+U/0.49)));
    }

    return colors;
}
