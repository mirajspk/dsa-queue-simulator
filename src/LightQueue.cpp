#include "header/LightQueue.hpp"
#include <algorithm>

void LightQueue::enqueue(RoadType road) {
    queue.push_back(road);
}

RoadType LightQueue::dequeue() {
    if (!queue.empty()) {
        RoadType road = queue.front();
        queue.erase(queue.begin());
        return road;
    }
    return RoadType::A; 
}

void LightQueue::sortQueue(float avgA, float avgB, float avgC, float avgD, int a2Size) {
    queue.clear();
    queue = {RoadType::A, RoadType::B, RoadType::C, RoadType::D};

    
    if (a2Size > 10) {
        std::sort(queue.begin(), queue.end(), [&](RoadType a, RoadType b) {
            if (a == RoadType::A) return true;
            if (b == RoadType::A) return false;
            return false; 
        });
    } else {
        
        std::sort(queue.begin(), queue.end(), [&](RoadType a, RoadType b) {
            float avgAVal = (a == RoadType::A) ? avgA : (a == RoadType::B) ? avgB : (a == RoadType::C) ? avgC : avgD;
            float avgBVal = (b == RoadType::A) ? avgA : (b == RoadType::B) ? avgB : (b == RoadType::C) ? avgC : avgD;
            return avgAVal > avgBVal; 
        });
    }
}

bool LightQueue::empty() {
    return queue.empty();
}

void LightQueue::clear() {
    queue.clear();
}