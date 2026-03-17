#ifndef DRONE_H
#define DRONE_H

#include "VehicleBase.hpp"


class Drone : public VehicleBase{
    private:

    public:
        //Constructor
        using VehicleBase::VehicleBase;
        // Drone(double init_x,double init_y,double init_z,double speed) : Vehicle(init_x, init_y, init_z, speed){}

        void update(double dt) override; // This initiallizes the overriden update function from the parent class
        

};

#endif //DRONE_H