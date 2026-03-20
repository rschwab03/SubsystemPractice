# Requirements
# The battery subsystem should:
# Track remaining energy
#   Battery has a maximum capacity (Wh)
# Consume power each timestep
#   Power draw (W) will be provided by other subsystems
# Update state each simulation step
#   The simulation provides dt (seconds)
# Provide outputs
#   remaining energy
#   state of charge (0–1)
#   a flag indicating whether the battery is depleted
# Be usable inside a larger simulation
#   Assume a scheduler will call an update function each step

sim_time = 0
dt = 0.1
end_time = 1000

max_Capacity = 10 # Wh


class Battery:
    def __init__(self,max_Capacity):
        self.energy = max_Capacity
        self.max_Capacity = max_Capacity
        self.depleted = False

    def update(self, power_draw, dt):
        if self.depleted is False:
            self.energy -= power_draw*dt
            if(self.energy<=0): 
                self.energy = 0
                self.depleted = True
        else:
            print("Battery Depleted!! Attempting to draw from dead battery!")

    def get_state_of_charge(self):
        return(self.energy/self.max_Capacity)
    
    def get_energy(self):
        return(self.energy)
    
    


battery = Battery(max_Capacity)

while sim_time < end_time:
    power_draw = sim_time * (0.001-(0.001*(sim_time/end_time)))
    battery.update(power_draw, dt)
    print(battery.get_state_of_charge())
    sim_time += dt