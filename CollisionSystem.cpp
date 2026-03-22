#include <unordered_map>
#include <vector>
struct Vec3{
    double x;
    double y;
    double z;
};

using EntityId = int;

struct EntityState{
    EntityId id;
    Vec3 position;
    Vec3 velocity;
    double radius; // for sphere
};

struct CollisionEvent{
    EntityId a;
    EntityId b;
    Vec3 contact_point;
    double timestamp;
};


class Entity{
    private:
    Vec3 position;
    Vec3 velocity;

    public:
    Entity(Vec3 position, Vec3 velocity)
    : position(position)
    , velocity(velocity)
    {

    }
};


class CollisionSystem {
public:
    void update(const std::vector<EntityState>& entities, double time);

    const std::vector<CollisionEvent>& get_collisions() const;

private:
    std::vector<CollisionEvent> collisions_;

    void detect_collisions(const std::vector<EntityState>& entities){
        
    };
};