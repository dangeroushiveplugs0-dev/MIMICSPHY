#include "spenclmx/secondary_motion.hpp"
#include <algorithm>
#include <cmath>
namespace spenclmx {
Vec3 Vec3::operator+(const Vec3& r) const noexcept { return {x+r.x,y+r.y,z+r.z}; }
Vec3 Vec3::operator-(const Vec3& r) const noexcept { return {x-r.x,y-r.y,z-r.z}; }
Vec3 Vec3::operator*(float s) const noexcept { return {x*s,y*s,z*s}; }
Vec3& Vec3::operator+=(const Vec3& r) noexcept { x+=r.x; y+=r.y; z+=r.z; return *this; }
float Vec3::length() const noexcept { return std::sqrt(x*x+y*y+z*z); }
bool Vec3::is_finite() const noexcept { return std::isfinite(x)&&std::isfinite(y)&&std::isfinite(z); }
bool BoneChain::initialize(const std::vector<Vec3>& input) {
 if(input.size()<2) return false;
 for(const auto& p:input) if(!p.is_finite()) return false;
 positions=input; targets=input; velocities.assign(input.size(),{}); rest_lengths.clear();
 for(std::size_t i=1;i<input.size();++i) { float d=(input[i]-input[i-1]).length(); if(!std::isfinite(d)||d<=1e-6F) { positions.clear(); targets.clear(); velocities.clear(); rest_lengths.clear(); return false; } rest_lengths.push_back(d); }
 return true;
}
bool BoneChain::valid() const noexcept {
 if(positions.size()<2||targets.size()!=positions.size()||velocities.size()!=positions.size()||rest_lengths.size()+1!=positions.size()) return false;
 for(const auto& p:positions) if(!p.is_finite()) return false;
 for(const auto& p:targets) if(!p.is_finite()) return false;
 for(const auto& v:velocities) if(!v.is_finite()) return false;
 for(float d:rest_lengths) if(!std::isfinite(d)||d<=0) return false;
 return true;
}
SecondaryMotionSolver::SecondaryMotionSolver(SecondaryMotionSettings settings):settings_(settings){}
bool SecondaryMotionSolver::step(BoneChain& c,float delta_time) const noexcept {
 if(!c.valid()||!std::isfinite(delta_time)||delta_time<=0||!settings_.gravity.is_finite()||!settings_.external_acceleration.is_finite()||!std::isfinite(settings_.damping)||!std::isfinite(settings_.stiffness)||!std::isfinite(settings_.max_delta_time)||settings_.max_delta_time<=0) return false;
 const float dt=std::min(delta_time,settings_.max_delta_time), damp=std::clamp(settings_.damping,0.0F,1.0F), stiff=std::max(0.0F,settings_.stiffness);
 const Vec3 acceleration=settings_.gravity+settings_.external_acceleration;
 c.positions[0]=c.targets[0]; c.velocities[0]={};
 for(std::size_t i=1;i<c.positions.size();++i) { c.velocities[i]+=(acceleration+(c.targets[i]-c.positions[i])*stiff)*dt; c.velocities[i]=c.velocities[i]*(1.0F-damp); c.positions[i]+=c.velocities[i]*dt; }
 for(unsigned it=0;it<std::clamp(settings_.constraint_iterations,1U,32U);++it) {
  c.positions[0]=c.targets[0];
  for(std::size_t i=1;i<c.positions.size();++i) { Vec3 d=c.positions[i]-c.positions[i-1]; float len=d.length(); if(!std::isfinite(len)) return false; if(len>1e-6F) c.positions[i]=c.positions[i-1]+d*(c.rest_lengths[i-1]/len); }
 }
 for(const auto& p:c.positions) if(!p.is_finite()) return false;
 return true;
}
}
