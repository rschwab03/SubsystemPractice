#pragma once // maybe the same as the #ifndef thing?

#include "../Vehicles/VehicleBase.hpp" // Theoretically this is better handled through CMAKE than relative paths


// enum data type used to efficiently store allowable (aka possible) types of vehicles in the registry
enum class VehicleType{
    Drone,
    Target
};


//Define the struct used to fill the registry which holds the instanciated vehicle objects (book-keeping style)
struct RegistryEntry{
    VehicleType type;  // efficiently stores type from enum data type defined above
    VehicleBase* vehicle; // pointer to particular vehicle instanciation
};