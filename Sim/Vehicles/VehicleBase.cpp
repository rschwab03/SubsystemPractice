#include "VehicleBase.hpp"
#include <cmath>
#include <cstdlib> 

//##TODO:  Update Random Number Generator.  Ideally, pass this in from an RNG class or something

    //constructor Implementations
    VehicleBase::VehicleBase(double init_x,double init_y,double init_z,double speed)
        : pos{init_x,init_y,init_z}
        , speed(speed)
        {
        heading = {static_cast<double>(std::rand()%10),static_cast<double>(std::rand()%10),static_cast<double>(std::rand()%10)};
        normalize_heading(heading);
        
    }
    
    //Default Constructor (randomly assign posigion, speed, heading)
    VehicleBase::VehicleBase()
        : pos{static_cast<double>(std::rand()%100),static_cast<double>(std::rand()%100),static_cast<double>(std::rand()%100)}
        , speed(std::rand()%10)
        {
        heading = {static_cast<double>(std::rand()%10),static_cast<double>(std::rand()%10),static_cast<double>(std::rand()%10)};
        normalize_heading(heading);
    }
    VehicleBase::~VehicleBase() = default;




    void VehicleBase::update(double dt){
        move(dt);
    }


    void VehicleBase::move(double dt){
        pos.x += heading.x*speed*dt;
        pos.y += heading.y*speed*dt;
        pos.z += heading.z*speed*dt;
    }

    void VehicleBase::normalize_heading(Hed3& heading){
            normalizer = 1/std::sqrt(heading.x*heading.x + heading.y*heading.y + heading.z*heading.z);
            heading.x *= normalizer;
            heading.y *= normalizer;
            heading.z *= normalizer;
        }
