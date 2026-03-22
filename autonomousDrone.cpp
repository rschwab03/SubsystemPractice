#include "autonomousDrone.hpp"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>


struct Pos3{
    double x{};
    double y{};
    double z{};
};
struct Hed3{
    double x{};
    double y{};
    double z{};    
};


class Vehicle{
    private:
        Pos3 pos;
        double speed;
        Hed3 heading;
        double normalizer;
        

    public:
        //constructor
        Vehicle(double init_x,double init_y,double init_z,double speed)
            : pos{init_x,init_y,init_z}
            , speed(speed)
            {
            heading = {static_cast<double>(std::rand()%10),static_cast<double>(std::rand()%10),static_cast<double>(std::rand()%10)};
            normalize_heading(heading);
            
        }
        //Default Constructor (randomly assign posigion, speed, heading)
        Vehicle()
            : pos{static_cast<double>(std::rand()%100),static_cast<double>(std::rand()%100),static_cast<double>(std::rand()%100)}
            , speed(std::rand()%10)
            {
            heading = {static_cast<double>(std::rand()%10),static_cast<double>(std::rand()%10),static_cast<double>(std::rand()%10)};
            normalize_heading(heading);
        }


        virtual void update(double dt){
            move(dt);
        }

        virtual ~Vehicle() = default;

        void move(double dt){

            pos.x += heading.x*speed*dt;
            pos.y += heading.y*speed*dt;
            pos.z += heading.z*speed*dt;
            
            
        }

        void normalize_heading(Hed3& heading){
            normalizer = 1/std::sqrt(heading.x*heading.x + heading.y*heading.y + heading.z*heading.z);
            heading.x *= normalizer;
            heading.y *= normalizer;
            heading.z *= normalizer;
        }

        //getters
        const Pos3& get_pos() const {return pos;}
        const double& get_pos_x() const {return pos.x;}
        const double& get_pos_y() const {return pos.y;}
        const double& get_pos_z() const {return pos.z;}
        const double& get_speed() const {return speed;}

        double get_head_x(){return heading.x;}
        double get_head_y(){return heading.y;}
        double get_head_z(){return heading.z;}

        //setters
        void update_pos(Pos3 new_pos){pos = new_pos;}
        void update_heading(Hed3 new_heading){
            normalize_heading(new_heading);
            heading = new_heading;}


};



class Target : public Vehicle{
    private:

    public:
        //Constructor
        using Vehicle::Vehicle;

};

class Drone : public Vehicle{
    private:

    public:
        //Constructor
        using Vehicle::Vehicle;
        // Drone(double init_x,double init_y,double init_z,double speed) : Vehicle(init_x, init_y, init_z, speed){}

        void update(double dt) override {
            move(dt);

        }
        

};




enum class VehicleType{
    Drone,
    Target
};

struct RegistryEntry{
    VehicleType type;
    Vehicle* vehicle;
};




int main(){
    std::srand(1);

    std::vector<Target> tgts;
    // Target tgt = Target(1, 2, 3, 4); // define individual target
    std::vector<Drone> drones;
    std::unordered_map<int, RegistryEntry> registry;
    int registry_id = 0;

    int num_tgts = 12;
    tgts.reserve(num_tgts);
    for(int i=0; i<num_tgts;i++){
        tgts.emplace_back(Target());
        registry[registry_id] = {VehicleType::Target, &tgts.back()};
        registry_id++;
    }

    int num_drones = 1;
    drones.reserve(num_drones);
    for(int i=0; i<num_drones; i++){
        drones.emplace_back(Drone(0,0,0,5));
        registry[registry_id] = {VehicleType::Drone, &drones.back()};
        registry_id++;
    }



    float dt = 0.1;
    float sim_time = 0.0;
    float end_time = 3600.0;

    std::cout << tgts[11].get_pos_x() << std::endl;
    while(sim_time < end_time){
        // // Update Targets
        // for(auto& tgt : tgts){
        //     tgt.move(dt);
        // };

        // // Update Drones
        // for(auto& drone : drones){
        //     drone.update(dt);
        // };

        //Update all Vehicles
        for(auto& [id, entry]: registry){
            entry.vehicle->update(dt);
        }
        

        sim_time += dt;
    }
    std::cout << tgts[11].get_pos_x() << std::endl;
    std::cout << tgts[11].get_head_x() << " " << tgts[11].get_head_y() << " " << tgts[11].get_head_z() << std::endl;
    std::cout << tgts[11].get_speed() << std::endl;

    

    // std::cout << tgts[11].get_pos_x() << std::endl;

    // int i=8;
    // std::cout << "Key: " << i << " value: " << registry[i].vehicle << std::endl;


    return 0;
}