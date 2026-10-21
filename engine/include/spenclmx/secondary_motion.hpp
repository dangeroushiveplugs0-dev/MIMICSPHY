#pragma once
#include <vector>
namespace spenclmx {
struct Vec3 {
 float x{0}, y{0}, z{0};
 Vec3 operator+(const Vec3&) const noexcept;
 Vec3 operator-(const Vec3&) const noexcept;
 Vec3 operator*(float) const noexcept;
 Vec3& operator+=(const Vec3&) noexcept;
 float length() const noexcept;
 bool is_finite() const noexcept;
};
struct SecondaryMotionSettings {
 Vec3 gravity{0,0,-9.81F};
 Vec3 external_acceleration{0,0,0};
 float damping{0.08F};
 float stiffness{8.0F};
 float max_delta_time{1.0F/30.0F};
 unsigned constraint_iterations{4};
};
struct BoneChain {
 std::vector<Vec3> positions, targets, velocities;
 std::vector<float> rest_lengths;
 bool initialize(const std::vector<Vec3>& initial_positions);
 bool valid() const noexcept;
};
class SecondaryMotionSolver {
public:
 explicit SecondaryMotionSolver(SecondaryMotionSettings settings = {});
 bool step(BoneChain& chain, float delta_time) const noexcept;
private: SecondaryMotionSettings settings_;
};
}
