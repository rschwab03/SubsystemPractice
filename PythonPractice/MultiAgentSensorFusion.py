# multiple sensors report:
#     measured_position(x,y)
#     measurement_noise_std
#     timestamp

# Task:
#     Design a subsystem that produces the best estimate of the target position from all available sensor measurements
# Requirement:
#     handle multiple sensors
#     handle noisy measurements
#     produce a single fused estimate
# Interface concept:
#     fusion.update(sensor_measurements)
#     fusion.get_estimated_position()

I'm going to assume that the measurement noise can be represented as normally distributed uncertainty in both x and y. I'm thinking I'll have the subsystem overlay each sensor's area of uncertainty and weight those regions in x and y according to their normally distributed noise_std.  superposition of these distributions should result in ideally 1, but as many as n, regions of likely target position, where n is the number of sensors.   I would like to add time-history to the algorithm, affectively allowing regions to take in a "likelyhood" score based on measured position and measurement noise std, which slowly diminishes over time, but is also added to by consecutive measurements. 

I would 