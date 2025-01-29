#ifndef VEHICLE_H
#define VEHICLE_H

#include "Route.h" 
#include "Lane.h"
#include <string>

class Vehicle {

private:
    Lane lane;                           
    Route route;                
    int id;                             
                    
    Vehicle(Lane lane, Route route, int id); 

    Lane getLane() const;                
    Route getRoute() const;      
    int getID() const;                   

};

#endif 
