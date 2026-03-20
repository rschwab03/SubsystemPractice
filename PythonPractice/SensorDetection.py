# Implement a sensor subsystem that determines whether a drone 
# detects a target

#Inputs per timestep:
#distance_to_target
#dt

# Sensor paramters
#     max range
#     detection probability at zero rangedetection probability decays with distance
#     ie P(detection) = P0 * exp(-distance / decay_constant)

# Behavior:
# Each Timestep should
#     compute detection probability
#     sample a random number
#     determine if a detection occurs

# Requirements:
# subsystem should:
#     maintain detected / not detected state 
#     allow deterministic runs via random seed
#     expose a function:
#         sensor.update(distance,dt)
# Outputs:
#     sensor.is_detected()

import random
import math as np


class Sensor:
    def __init__(self, rng_seed, detection_probability, max_range, decay_const):
        # Object Params:
        self.P0 = detection_probability
        self.rng = random.Random()#.Random(rng_seed)
        self.decay_const = decay_const
        self.max_range = max_range
        self.P_detect = 0 #initialized to zero probability of detection

        # Object States:
        self.is_detected = False 

    def update(self, distance, dt):
        if self.is_detected:
            return
        elif (distance<self.max_range):
            self.P_detect = min(1,self.P0 * np.exp(-distance / self.decay_const))
        elif (self.P_detect != 0): # no need to update if already 0
            self.P_detect = 0 # not the most memory safe way to do this if we re-implement in C++

        if (self.P_detect > 0 and not self.is_detected):
            self.is_detected = (self.rng.random() <= self.P_detect)    #Triggers a detection based on randomly drawn number rel to detection likelyhood

    def get_detection_status(self):
        return self.is_detected


sensor = Sensor(rng_seed=1,detection_probability=0.015,max_range=500,decay_const=200)

dt = 1 # 1 second
sim_time = 0
end_sim_time = 2 *(60*60) # 2 hours
distance = 300 #start distance (m)
speed = 0.5 # m/s

while sim_time < end_sim_time and distance >= 0:
    distance -= speed*dt # assumes perfect trajectory
    sensor.update(distance=distance,dt=dt)
    if not sensor.get_detection_status():
        print("Detected: ",sensor.get_detection_status(),"; Time: ", sim_time, "; Distance: ", distance)
        print("P_Detect: ", sensor.P_detect)
    else:
        print("Detected: ",sensor.get_detection_status(),"; Time: ", sim_time, "; Distance: ", distance)
        print("P_Detect: ", sensor.P_detect)
        break
    sim_time += dt