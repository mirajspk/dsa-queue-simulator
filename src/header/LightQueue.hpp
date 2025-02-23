#ifndef LIGHT_QUEUE_HPP
#define LIGHT_QUEUE_HPP

#include "RoadType.hpp"
#include <vector>

class LightQueue {
private:
    std::vector<RoadType> queue;

public:
    void enqueue(RoadType road);
    RoadType dequeue();
    void sortQueue(float avgA, float avgB, float avgC, float avgD, int a2Size);
    bool empty();
    void clear();
};

#endif