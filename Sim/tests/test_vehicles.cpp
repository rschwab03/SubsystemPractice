#include <gtest/gtest.h>
#include <cmath>
#include "Vehicles/Target.hpp"
#include "Vehicles/Drone.hpp"

// Test Target construction with explicit values
TEST(TargetTest, ConstructWithValues) {
    Target target(1.0, 2.0, 3.0, 5.0);

    EXPECT_DOUBLE_EQ(target.get_pos_x(), 1.0);
    EXPECT_DOUBLE_EQ(target.get_pos_y(), 2.0);
    EXPECT_DOUBLE_EQ(target.get_pos_z(), 3.0);
    EXPECT_DOUBLE_EQ(target.get_speed(), 5.0);
}

// Test Drone construction with explicit values
TEST(DroneTest, ConstructWithValues) {
    Drone drone(0.0, 0.0, 0.0, 10.0);

    EXPECT_DOUBLE_EQ(drone.get_pos_x(), 0.0);
    EXPECT_DOUBLE_EQ(drone.get_pos_y(), 0.0);
    EXPECT_DOUBLE_EQ(drone.get_pos_z(), 0.0);
    EXPECT_DOUBLE_EQ(drone.get_speed(), 10.0);
}

// Test Target default constructor creates valid object
TEST(TargetTest, DefaultConstruction) {
    std::srand(42); // Seed for reproducibility
    Target target;

    // Default constructor should create a target with some position
    // Just verify it doesn't crash and values are accessible
    EXPECT_NO_THROW(target.get_pos_x());
    EXPECT_NO_THROW(target.get_pos_y());
    EXPECT_NO_THROW(target.get_pos_z());
}

// Test Target movement
TEST(TargetTest, MoveUpdatesPositionCorectly){
    Target v(0,0,0,10);
    //Force Deterministic heading
    Hed3 h{1,0,0,};
    v.update_heading(h);

    double dt = 2.0;
    v.move(dt);

    EXPECT_DOUBLE_EQ(v.get_pos_x(), 20.0);
    EXPECT_DOUBLE_EQ(v.get_pos_y(), 0.0);
    EXPECT_DOUBLE_EQ(v.get_pos_z(), 0.0);
}


// Test Target normalization function
TEST(TargetTest,HeadingIsNormalized){
    Target v(0,0,0,1); // initialize target at zero with rand heading

    //Grab randomly generated heading (should already be normalized. Probably not repeatable without seeding RNG)
    double hx = v.get_head_x();
    double hy = v.get_head_y();
    double hz = v.get_head_z();

    //Calculate magnitude of heading vector
    double mag = std::sqrt(hx*hx + hy*hy + hz*hz);

    EXPECT_NEAR(mag, 1.0, 1e-6); // magnitude should be 1 since vector is normalized
}

// Test position update
TEST(TargetTest, UpdatePosition) {
    Target target(0.0, 0.0, 0.0, 1.0);

    Pos3 new_pos = {5.0, 5.0, 5.0};
    target.update_pos(new_pos);

    EXPECT_DOUBLE_EQ(target.get_pos_x(), 5.0);
    EXPECT_DOUBLE_EQ(target.get_pos_y(), 5.0);
    EXPECT_DOUBLE_EQ(target.get_pos_z(), 5.0);
}
