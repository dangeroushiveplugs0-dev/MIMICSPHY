#include "spenclmx/secondary_motion.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
static void check(bool ok,const char* msg){if(!ok){std::cerr<<"FAIL: "<<msg<<'\n';std::exit(1);}}
int main(){using namespace spenclmx; BoneChain c; check(c.initialize({{0,0,0},{0,0,1},{0,0,2}}),"initialize chain"); SecondaryMotionSolver solver; for(int i=0;i<120;++i) check(solver.step(c,1.0F/60.0F),"step succeeds"); for(std::size_t i=1;i<c.positions.size();++i) check(std::fabs((c.positions[i]-c.positions[i-1]).length()-c.rest_lengths[i-1])<1e-3F,"segment length preserved"); check(!solver.step(c,0),"reject zero dt"); check(!solver.step(c,-1),"reject negative dt"); BoneChain bad; check(!bad.initialize({{0,0,0}}),"reject short chain"); check(!bad.initialize({{0,0,0},{0,0,0}}),"reject zero segment"); std::cout<<"SPENCLMX tests passed\n"; }
