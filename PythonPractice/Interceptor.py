# You are modeling a guidance subsystem for a drone attempting to intercept a moving target.
# Each timestep the interceptor should compute a desired heading toward the predicted target position.

# Target State:
#     target_position (x, y)
#     target_velocity (vx, vy)

# Interceptor State:

#     interceptor_position (x, y)
#     interceptor_speed

# Requirement
# Your subsystem should compute a unit direction vector pointing toward the predicted intercept point.
# Use a constant velocity assumption for the target.
    
# Interface
#     guidance.update(target_state, interceptor_state)

# Outputs:
#     guidance.get_desired_heading()   Where heading is a unit vector (hx, hy).

import math as np


class Target:
    def __init__(self, initial_position, initial_velocity):
        self.position = initial_position
        self.velocity = initial_velocity
        pass

    def update_state(self,position,velocity,dt):
        self.position[0] = position[0] + velocity[0]*dt
        self.position[1] = position[1] + velocity[1]*dt
        pass

    def get_position(self):
        return self.position

class Interceptor:
    def __init__(self, initial_position, initial_speed):
        self.position = initial_position
        self.speed = initial_speed
        pass

    def update_state(self, position, heading, speed, dt):
        self.position[0] = position[0] + heading[0]*(speed*dt)
        self.position[1] = position[1] + heading[1]*(speed*dt)
        pass

    def get_position(self):
        return self.position


class Guidance:
    # intended to update interceptor heading given interceptor speed and position, and target velocity and position
    def __init__(self):
        self.hx = None
        self.hy = None
        self.t_to_intercept = np.inf
        self.target_reached = False
        pass

    def update(self,target_position, target_velocity, interceptor_position, interceptor_speed, sim_time):
        sim_time = sim_time
        
        x0_t = target_position[0]
        y0_t = target_position[1]

        vx_t = target_velocity[0]
        vy_t = target_velocity[1]

        x0_i = interceptor_position[0]
        y0_i = interceptor_position[1]

        speed_i = interceptor_speed

        dx = x0_t - x0_i
        dy = y0_t - y0_i

        # x2 = x1 + vx* t
        # xi2 = xi1 + (hx/(sqrt(hx^2 + hy^2)))*speed*t

        # y2 = y1 + vy* t
        # yi2 = yi1 + (hy/(sqrt(hx^2 + hy^2)))*speed*t

        # hx^2+hy^2=1

        # x1+vx*t = xi1+hx*speed*t
        # y1+vy*t = yi1+hy*speed*t
        # dx = x1-xi1
        # dy = y1-yi1

        # dx + vx*t = hx*S*t
        # dy + vy*t = hy*S*t

        # hx = (dx+vx*t)/(S*t)
        # hy = (dy+vy*t)/(S*t)

        # (dx^2 + 2*dx*vx*t + vx^2*t^2)/(S^2*t^2) + (dy^2 + 2*dy*vy*t + vy^2*t^2)/(S^2*t^2) = 1
        # (dx^2 + 2*dx*vx*t + vx^2*t^2) + (dy^2 + 2*dy*vy*t + vy^2*t^2) = (S^2*t^2)

        # t^2*(vx^2 + vy^2 - S^2) + 2*t*(dx*vx+dy*vy) + (dx^2 + dy^2) = 0
        # ^^^^ Solve this quadratic equation for t ^^^^ #
        a = (vx_t**2 + vy_t**2 - speed_i**2)
        b = 2*(dx*vx_t + dy*vy_t)
        c = (dx**2 + dy**2)
        
        if (b**2-4*a*c < 0) or a == 0:
            raise ValueError("Target can outrun interceptor")
        else:
            if (min(abs((-b - np.sqrt(b**2-(4*a*c)))/(2*a)), abs((-b + np.sqrt(b**2-(4*a*c)))/(2*a))) < self.t_to_intercept):
                temp_t = [(-b - np.sqrt(b**2-(4*a*c)))/(2*a), (-b + np.sqrt(b**2-(4*a*c)))/(2*a)]
                self.t_to_intercept = min(x for x in temp_t if x>0)
            else:
                self.target_reached = True
                pass
            self.hx = (dx+vx_t*self.t_to_intercept)/(speed_i*self.t_to_intercept)
            self.hy = (dy+vy_t*self.t_to_intercept)/(speed_i*self.t_to_intercept)
            self.intercept_time = sim_time + self.t_to_intercept

        pass

    def get_target_reached(self):
        return self.target_reached

    def get_desired_heading(self):
        return [self.hx,self.hy]
    
    def get_time_to_intercept(self):
        return self.t_to_intercept
    


#define a few sim variables:
sim_time = 0
end_sim_time = 1.1*(60*60)
dt = 1
interceptor_speed = 1.2 #m/s
interceptor_position_initial = [0,5]

target_position_initial = [155, 760]
target_velocity = [0,1]

#initialize the target and interceptor
target = Target(target_position_initial,target_velocity)
interceptor = Interceptor(interceptor_position_initial,interceptor_speed)
guide = Guidance()


while sim_time <= end_sim_time and not guide.get_target_reached():
    guide.update(target_position=target.get_position(),target_velocity=target.velocity,interceptor_position=interceptor.get_position(),interceptor_speed=interceptor.speed,sim_time=sim_time)

    target.update_state(target.get_position(),target.velocity,dt)
    interceptor.update_state(interceptor.get_position(),guide.get_desired_heading(),interceptor.speed,dt)


    if sim_time%1 == 0:
        print("heading: [",guide.get_desired_heading(),"] ;  Time to Impact: ", guide.get_time_to_intercept(),"s")
        # print("Target Position: ", target.get_position())
        pass

    sim_time += dt

print("Target Reached!")