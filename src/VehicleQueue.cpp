#include "header/VehicleQueue.hpp"

void VehicleQueue::enqueue(Vehicle& vehicle) {
    queue.push_back(vehicle);
}

void VehicleQueue::dequeue() {
    queue.erase(queue.begin());
}

int VehicleQueue::size(){
    return queue.size();
}