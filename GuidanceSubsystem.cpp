#include <cmath>
#include <iostream>
#include <stdexcept>

struct Vec3{
    double x;
    double y;
    double z;
};
// Vec3 Helpers
Vec3 subtract(const Vec3& a, const Vec3& b){
    return Vec3{a.x-b.x,a.y-b.y,a.z-b.z};
}
Vec3 scale(const Vec3& v, double s){
    return Vec3{v.x*s,v.y*s,v.z*s};
}
double dot(const Vec3& a, const Vec3& b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}
Vec3 cross(const Vec3& a, const Vec3& b){
    return Vec3{a.y*b.z - a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x};
}
double norm(const Vec3& v){
    return std::sqrt(dot(v,v));
}
Vec3 normalize(const Vec3& v){
    double n = norm(v);
    if (n<1e-6){
        return Vec3{0.0,0.0,0.0};
    }
    return scale(v,1/n);
}

struct State{
    Vec3 pos;
    Vec3 vel;
};

struct GuidanceInput{
    State self;
    State tgt;
    double dt;
};

struct GuidanceOutput{
    Vec3 accel;

};


//Interface
class IGuidance{
    public:
    virtual ~IGuidance() = default;
    virtual GuidanceOutput update(const GuidanceInput& input) = 0; //pure virtual
};


// Old Chase Guidance algorithm which output heading instead of acceleration
// class ChaseGuidance : public IGuidance{
//     private:

//     public:

//         GuidanceOutput update(const GuidanceInput& input) override {
//             Vec3 dir = subtract(input.tgt.pos, input.self.pos);
//             Vec3 unit_dir = normalize(dir);
//             if(norm(unit_dir)<1e-6){
//                 throw std::runtime_error ("normalization error!");
//             }
//             return GuidanceOutput{};
//         }
// };


// Proportianl Navigation Guidance
class PNGuidance : public IGuidance {
    private:
    double N;

    public:
    PNGuidance(double N) : N(N){}

    GuidanceOutput update(const GuidanceInput& input) override{
        Vec3 rel_pos = subtract(input.self.pos,input.tgt.pos);
        Vec3 rel_vel = subtract(input.self.vel,input.tgt.vel);

        Vec3 los = normalize(rel_pos); //line of sight
        Vec3 los_rate = scale(cross(rel_pos,rel_vel), 1/dot(rel_pos,rel_pos));
        double closing_vel = -dot(rel_pos,rel_vel)/norm(rel_pos);

        Vec3 accel = scale(cross(los_rate,los),(N*closing_vel));

        return GuidanceOutput{accel};

    }
};