#include <unordered_map>
#include <vector>

struct Vec3{
    double x;
    double y;
    double z;
};

struct State{
    Vec3 pos;
    Vec3 vel;
};

enum class SensorType{
    RF,
    LIDAR,
    EO
};

enum class NoiseType{
    Gaussian,
    none
};

struct SensorConfigs{
    SensorType type;
    double update_rate; // timestep
    NoiseType noise;
};

struct SensorInput{
    State self;
    std::unordered_map<int, State> tgts; // define with target registry, tgts update truth state on their update loops
    //Consider adding hash map for more efficient passing of targets to sensor
};

struct SensorDetection{
    State detected_state;
    double timestamp;
    double snr;
};


struct SensorOutput{
    std::unordered_map<int, SensorDetection> current_detects; //start with id and state?
};

class ISenor{
    public:
    virtual ~ISenor() = default;
    virtual SensorOutput update(const SensorInput& input) = 0;
};



class RadarSensor : public ISenor{
    public:
    SensorOutput update(const SensorInput& input) override {/*add functionality here*/};
};


class LidarSensor : public ISenor{
    public:
    SensorOutput update(const SensorInput& input) override {/*add functionality here*/};
};