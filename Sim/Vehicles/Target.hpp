#ifndef TARGET_H
#define TARGET_H

#include "VehicleBase.hpp"


class Target : public VehicleBase{
    private:

    public:
        //Constructor
        using VehicleBase::VehicleBase; // inheret and use the parent constructor
        
        
        void update(double dt) override; // This initiallizes the overriden update function from the parent class
        
};

#endif //TARGET_H