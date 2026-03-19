#ifndef VEHICLE_H
#define VEHICLE_H

#include "../Common/Types.hpp" // relative paths, generally not great, would be stitched together with CMAKE normally.

class VehicleBase{
    private:
        Pos3 pos;
        double speed;
        Hed3 heading;
        double normalizer;

        void normalize_heading(Hed3& heading);
        

    public:
        //constructor
        VehicleBase(double init_x,double init_y,double init_z,double speed);

        //Default Constructor (randomly assign posigion, speed, heading)
        VehicleBase();


        virtual void update(double dt) = 0;  // defining as 0 makes this pure virtual (Base Classes MUST define update()).  Making VehicleBase interface-like

        virtual ~VehicleBase(); // Needs to be defined in cpp

        void move(double dt);

        //getters
        const Pos3& get_pos() const {return pos;}
        const double& get_pos_x() const {return pos.x;}
        const double& get_pos_y() const {return pos.y;}
        const double& get_pos_z() const {return pos.z;}
        const double& get_speed() const {return speed;}

        const double& get_head_x() const {return heading.x;}
        const double& get_head_y() const {return heading.y;}
        const double& get_head_z() const {return heading.z;}

        //setters
        void update_pos(Pos3 new_pos){pos = new_pos;}
        void update_heading(Hed3 new_heading){
            normalize_heading(new_heading); // ensures new heading is normalized
            heading = new_heading;}


};




#endif //VEHICLE_H