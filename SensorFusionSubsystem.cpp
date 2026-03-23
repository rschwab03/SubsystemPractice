#include <unordered_map>
#include <vector>
#include <memory>

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
    State self; // platform state
    std::unordered_map<int, State> tgts; // define with target registry, tgts update truth state on their update loops
    //Consider adding hash map for more efficient passing of targets to sensor
};

struct SensorDetection{
    State detected_state;
    double timestamp;
    double snr;
};

struct SensorOutput{
    std::unordered_map<int, SensorDetection> current_detects; 
};








class ISensor{
    public:
    virtual ~ISensor() = default;
    virtual SensorOutput update(const SensorInput& input) = 0;
};

class IFusion{
    public:
    virtual ~IFusion() = default;

    virtual void assess(const SensorOutput&) = 0;
    virtual std::unordered_map<int, State> estimate() const =0;
};

class INoiseModel{
    public:
    virtual ~INoiseModel() = default;
    virtual Vec3 apply(const Vec3& truth) = 0;
};





class NoNoise : public INoiseModel{
    public:
    Vec3 apply(const Vec3& truth){
        return truth;
    }
};

class GaussianNoise : public INoiseModel{
    public:
    Vec3 apply(const Vec3& truth){
        return truth; // ADD GAUSSIAN NOISE LATER!!!!!
    }
};




class RadarSensor : public ISensor{
    private:
        SensorConfigs config_;
        std::unique_ptr<INoiseModel> noise_;
    public:
        RadarSensor(SensorConfigs& input_config, std::unique_ptr<INoiseModel> input_noise)
        : config_(input_config)
        , noise_(std::move(input_noise))
        {}

        SensorOutput update(const SensorInput& input) override {/*add functionality here*/};
};


class LidarSensor : public ISensor{
    public:
    SensorOutput update(const SensorInput& input) override {/*add functionality here*/};
};


