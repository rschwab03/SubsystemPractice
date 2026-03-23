#include <iostream>
#include <vector>
#include <memory>
#include <functional>

// --------------------------------------------
// Base Event
// --------------------------------------------
struct Event {
    virtual ~Event() = default;
};

// Example event
struct DetectionEvent : public Event {
    int target_id;
    double x, y, z;
};

// --------------------------------------------
// EventBus
// --------------------------------------------
class EventBus {
public:
    template<typename EventType>
    using Callback = std::function<void(const EventType&)>;

    template<typename EventType>
    void subscribe(Callback<EventType> cb) {
        // TODO
    }

    template<typename EventType>
    void publish(const EventType& event) {
        // TODO
    }
};

// --------------------------------------------
// Base Entity
// --------------------------------------------
class Entity {
public:
    virtual ~Entity() = default;

    virtual void update(double dt) = 0;

    virtual void initialize(EventBus& bus) {}
};

// --------------------------------------------
// Radar
// --------------------------------------------
class Radar : public Entity {
public:
    void initialize(EventBus& bus) override {
        bus_ = &bus;
    }

    void update(double dt) override {
        // TODO: publish DetectionEvent
    }

private:
    EventBus* bus_{nullptr};
};

// --------------------------------------------
// Tracker
// --------------------------------------------
class Tracker : public Entity {
public:
    void initialize(EventBus& bus) override {
        // TODO: subscribe to DetectionEvent
    }

    void update(double dt) override {}

private:
    // store detections / tracks
};

// --------------------------------------------
// Simulation
// --------------------------------------------
class Simulation {
public:
    void add_entity(std::shared_ptr<Entity> e) {
        entities_.push_back(e);
    }

    void initialize() {
        for (auto& e : entities_) {
            e->initialize(bus_);
        }
    }

    void step(double dt) {
        for (auto& e : entities_) {
            e->update(dt);
        }
    }

private:
    std::vector<std::shared_ptr<Entity>> entities_;
    EventBus bus_;
};

// --------------------------------------------
// Main
// --------------------------------------------
int main() {
    Simulation sim;

    sim.add_entity(std::make_shared<Radar>());
    sim.add_entity(std::make_shared<Tracker>());

    sim.initialize();

    for (int i = 0; i < 5; ++i) {
        sim.step(1.0);
    }

    return 0;
}