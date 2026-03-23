#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

struct Vec3 {
    double x{0}, y{0}, z{0};

    Vec3 operator+(const Vec3& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    Vec3 operator-(const Vec3& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    Vec3 operator*(double scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }
};

double dist(Vec3 a, Vec3 b){
    Vec3 diff = a-b;
    return std::sqrt(diff.x*diff.x + diff.y*diff.y + diff.z*diff.z);
}

double mag(Vec3 a){
    return std::sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

Vec3 normalize(Vec3 a){
    double normalizer = 1/std::sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
    return a*normalizer;
}



// --------------------------------------------
// Base class for all simulation entities
// --------------------------------------------
class Entity {
public:
    virtual ~Entity() = default;

    virtual void update(double dt) = 0;
    virtual void serialize(std::ostream& os) const = 0;

    Vec3 position() const { return position_; }
    int id() const {return id_; }
    std::string type() const { return type_;}

protected:
    Vec3 position_;
    int id_;
    std::string type_;
};


class World{
    public:
    virtual std::vector<Entity*> get_entities() const = 0;
    virtual std::vector<Entity*> get_targets() const = 0;
};

// --------------------------------------------
// A simple moving entity (constant velocity)
// --------------------------------------------
class MovingEntity : public Entity {
public:
    MovingEntity(int id, const Vec3& pos, const Vec3& vel)
        : velocity_(vel)
    {
        id_ = id;
        position_ = pos;
        type_ = "Moving Target";
    }

    virtual void update(double dt) override {
        // TODO: implement motion
        position_ = position_ + velocity_*dt;
    }

    void serialize(std::ostream& os) const override {
        os << "id = " << id_ << ","
           << " type = " << type_ << ","
           << " pos = ("<< position_.x
                << ", " << position_.y
                << ", " << position_.z << ")";
    }

protected:
    Vec3 velocity_;
    
};


class Target : public MovingEntity{
    public:
    Target(int id, const Vec3& pos, const Vec3& vel) : MovingEntity(id, pos, vel){
        type_ = "Target";
    }
    protected:
    
};

class Drone : public MovingEntity{
    public:
    Drone(int id, const Vec3& pos, const Vec3& vel, World& world) 
    : MovingEntity(id, pos, vel)
    , world_(world)
    {
        type_ = "Drone";
    }

    void update(double dt) override {
        auto tgts = world_.get_targets();
        update_vel(tgts);
        // std::cout << "(Vx,Vy,Vz): ("
        //         <<velocity_.x << ", "
        //         <<velocity_.y << ", "
        //         <<velocity_.z << ")" << std::endl;
        MovingEntity::update(dt);

    }

    

    private:
    World& world_;
    Entity* my_target = nullptr;

    void update_vel(std::vector<Entity*> tgts){
        if (tgts.empty()){
            std::cout << "[Drone::update_vel]  No Targets!" << std::endl;
            return;
        }


        Vec3 dir = normalize(velocity_);
        if(my_target == nullptr){
            my_target = tgts.front();
            std::cout << "Updated tgt to Entity id: " << my_target->id() << std::endl;
        }
        
        for(const auto& tgt : tgts){ // This is probably pretty lame to find the current target...
           
            if (dist(tgt->position(),position_) < dist(my_target->position(),position_)){
                my_target = tgt;
                std::cout << "Updated tgt to Entity id: " << my_target->id() << std::endl;
                
            }
        }
        double current_speed = mag(velocity_);

        if (dist(my_target->position(),position_) > 0){
            // std::cout<<"HERE" <<std::endl;
            dir = (my_target->position()-position_)*(1/(dist(my_target->position(),position_)));
        }
        // std::cout << "SPEED: " << current_speed << std::endl;
        // std::cout << "(Dx,Dy,Dz): ("
        //         <<dir.x << ", "
        //         <<dir.y << ", "
        //         <<dir.z << ")" << std::endl;
        velocity_ = (dir)*(current_speed);

    }
    
};


// --------------------------------------------
// Simulation container
// --------------------------------------------
class Simulation : public World
{

private:
    std::vector<std::shared_ptr<Entity>> entities_;
    double time_{0.0};

public:
    void add_entity(std::shared_ptr<Entity> entity)
    {
        entities_.push_back(entity);
    }

    std::vector<Entity*> get_entities() const override {
        std::vector<Entity*> result;
        result.reserve(entities_.size());
        for(const auto& e : entities_){
            result.push_back(e.get());
        }
        return result;
    }
    std::vector<Entity*> get_targets() const override {
        std::vector<Entity*> result;
        for(const auto& e : entities_){
            if(e->type() == "Target"){
                result.push_back(e.get());
            }
        }
        return result;
    }

    void step(double dt)
    {
        // TODO: update all entities
        time_ += dt;
        for (auto &entity : entities_)
        {
            entity->update(dt);

            logger(time_, *entity, std::cout);
        }
    }

    void logger(double t, const Entity &entity, std::ostream &os)
    {
        os << "t=" << t << ", ";
        entity.serialize(os);
        os << std::endl;
    }

};

// --------------------------------------------
// Main
// --------------------------------------------
int main() {
    Simulation sim;

    //Hardcoding new entities for now...
    sim.add_entity(std::make_shared<Target>(
        int{1}, Vec3{50,10,30}, Vec3{1,0,0}
    ));
    sim.add_entity(std::make_shared<Target>(
        int{2}, Vec3{0,10,100}, Vec3{1,0,0}
    ));
    sim.add_entity(std::make_shared<Target>(
        int{4}, Vec3{40,10,25}, Vec3{1,0,0}
    ));
    sim.add_entity(std::make_shared<Drone>(
        int{3}, Vec3{0,0,0}, Vec3{3,0,0}, sim
    ));





    double dt = 1.0;

    for (int i = 0; i < 10; ++i) {
        sim.step(dt);
    }

    return 0;
}