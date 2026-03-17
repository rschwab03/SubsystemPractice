/*
int main(){...}  is used to run and orchestrate the sim, it should not include a header/

As the sim builds, main.cpp should only include things like:
    simulation sim
    sim.initialize();
    sim.run();
    sim.post_process();

In this structure, a simulation class initializes and runs the models, allowing for 
more sofficsticated infrastructure to run scenarios, or sets of scenarios

/*
/*


Currently to compile (I'm using g++):
g++ mg++ main.cpp Vehicles/VehicleBase.cpp Vehicles/Drone.cpp Vehicles/Target.cpp

Better: implement a CMAKE infrastructure to build
*/

//Models & Such
#include "Common/Registry.hpp"
#include "Vehicles/Target.hpp"
#include "Vehicles/Drone.hpp"

//STLs
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <iostream>




int main(){
    std::srand(1); // ##TODO: this is an outdated RNG, would be way better to use something modern

    std::vector<Target> tgts;
    // Target tgt = Target(1, 2, 3, 4); // define individual target
    std::vector<Drone> drones;
    std::unordered_map<int, RegistryEntry> registry;
    int registry_id = 0;

    int num_tgts = 12;  // initialize 12 targets (flying)
    tgts.reserve(num_tgts);
    for(int i=0; i<num_tgts;i++){
        tgts.emplace_back(Target());
        registry[registry_id] = {VehicleType::Target, &tgts.back()};
        registry_id++;
    };

    int num_drones = 1; // initialize one ISR drone
    drones.reserve(num_drones);
    for(int i=0; i<num_drones; i++){
        drones.emplace_back(Drone(0,0,0,5));
        registry[registry_id] = {VehicleType::Drone, &drones.back()};
        registry_id++;
    }

    std::cout << tgts[11].get_pos_x() << std::endl;

    // int i=8;
    // std::cout << "Key: " << i << " value: " << registry[i].vehicle << std::endl;


    return 0;

}



/*
More notes:

This sim creates targets that move in 3-space.  Without any input variables, their 
initial position and speed is randomized.  
Drones (intended to be ISR or intercepter) are added next. 
Right now the drones don't really do anything.

Next step would be to build sensor subsystems to attach to the drones, then add noise
to their detections.

After this, a Kalman filter could be explored in the drones' GNC algorithms.
These algorithms should be models of their own to allow modularity in what each drone
is capable of.

*/