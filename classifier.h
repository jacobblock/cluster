#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <list>
#include <vector>
#include <opencv2/core/core.hpp>

class Classifier {
public:
    Classifier(std::list<cv::Vec2i> data, unsigned int k, double convergence = 0, unsigned int max_iterations = 1000);
    virtual void start();

protected:
    virtual void init() = 0;
    virtual bool update() = 0;

    std::list<cv::Vec2i> data;
    unsigned int k;
    double convergence;
    unsigned int max_iterations;
};

class KMeans: public Classifier {
public:
    KMeans(std::list<cv::Vec2i> data, unsigned int k, double convergence = 0, unsigned int max_iterations = 1000);

private:
    void init(); // Forgy init method
    bool update();

    std::vector<std::list<cv::Vec2i>> assign_sets() const;
    std::vector<cv::Vec2i> update_means() const;
    void display();
    std::vector<cv::Scalar> colormodel(unsigned int k) const;

    std::vector<cv::Vec2i> means;
    std::vector<std::list<cv::Vec2i>> sets;
    std::string window = "KMeans Classification";
    cv::Mat image;
    std::vector<cv::Scalar> colors;
    unsigned int circle_radius = 5;
};

#endif
