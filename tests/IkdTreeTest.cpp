#include <gtest/gtest.h>
#include "kdtree_lib/IkdTree.hpp"

using namespace NSKdTreeLib::Traits;
using namespace NSKdTreeLib;
using PointType = Point3;
constexpr float X_MAX = 5.0f;
constexpr float X_MIN = -5.0f;


constexpr int Point_Num = 20000;
/// Test the constructor of the IKDTree
TEST(IkdTreeTest, TestConstructor) {
    auto params = IKDParameters::Create().Set<DELETE_PARAM>(0.3f)
            .Set<BALANCE_PARAM>(0.6f).Set<BOX_LENGTH>(0.2f);
    auto tree = IKDTree<PointType>(params);
    EXPECT_NE(tree.implPointer(), nullptr);

}
TEST(IkdTreeTest, TestConstructor2) {
    auto tree = IKDTree<PointType>(IKDParameters::Create().Set<DELETE_PARAM>(0.3f)
                                           .Set<BALANCE_PARAM>(0.6f).Set<BOX_LENGTH>(0.2f));
    EXPECT_NE(tree.implPointer(), nullptr);

}
TEST(IKdTreeTest, TestSetParams){
    auto tree = IKDTree<PointType>();
    tree.SetParam<DELETE_PARAM>(0.5f);
    tree.SetParam<BALANCE_PARAM>(0.7f);
    tree.SetParam<BOX_LENGTH>(0.3f);
    //no way to check the value because the ikdTree don't expose the value

}
TEST(IkdTreeTest, TestSize) {
    auto tree = IKDTree<PointType>(IKDParameters::Create().Set<DELETE_PARAM>(0.3f)
                                           .Set<BALANCE_PARAM>(0.6).Set<BOX_LENGTH>(0.2f));
    EXPECT_NE(tree.implPointer(), nullptr);
    tree.SetParam<DELETE_PARAM>(0.5f);
    EXPECT_EQ(tree.size(), 0);
}
TEST(IkdTreeTest, TestBuild) {
    auto tree = IKDTree<PointType>(IKDParameters::Create().Set<DELETE_PARAM>(0.3)
                                           .Set<BALANCE_PARAM>(0.6).Set<BOX_LENGTH>(0.2));
    IKDTree<PointType>::PointVector points;
    RandomPoint3Generator gen(X_MIN, X_MAX);
    for (int i = 0; i < Point_Num; i++) {
        points.push_back(std::move(gen.next()));
    }
    tree.Build(points);
}