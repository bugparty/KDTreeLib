//
// Created by bowman han on 4/2/24.
//
#include <gtest/gtest.h>
#include "kdtree_lib/IkdTree.hpp"

using namespace NSKdTreeLib::Traits;
using namespace NSKdTreeLib;
using PointType = Point3;
/// Test the constructor of the IKDTree
TEST(RandomPoint3GeneratorTest, Test1) {
    float fmin=0.1f;
    float fmax=0.8f;
    RandomPoint3Generator gen(fmin,fmax);
    for(size_t i=0;i<100;i++){
        auto p = gen.next();
        EXPECT_GE(p.x,fmin);
        EXPECT_LE(p.x,fmax);
        EXPECT_GE(p.y,fmin);
        EXPECT_LE(p.y,fmax);
        EXPECT_GE(p.z,fmin);
        EXPECT_LE(p.z,fmax);
    }
}