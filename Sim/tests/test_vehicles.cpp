#include <gtest/gtest.h>
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

// Test position update
TEST(TargetTest, UpdatePosition) {
    Target target(0.0, 0.0, 0.0, 1.0);

    Pos3 new_pos = {5.0, 5.0, 5.0};
    target.update_pos(new_pos);

    EXPECT_DOUBLE_EQ(target.get_pos_x(), 5.0);
    EXPECT_DOUBLE_EQ(target.get_pos_y(), 5.0);
    EXPECT_DOUBLE_EQ(target.get_pos_z(), 5.0);
}
