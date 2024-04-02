#include <gtest/gtest.h>
#include "kdtree_lib/IkdTree.hpp"
#include "kdtree_lib/KdTreeLib.hpp"

using namespace NSKdTreeLib::Traits;
using namespace NSKdTreeLib;
using PointType = PointType3;
using PointVector = KD_TREE<PointType>::PointVector;
/// Test the constructor of the IKDTree
TEST(IkdTreeTest, TestConstructor) {
    auto params = IKDParameters::Create().Set<DELETE_PARAM>(0.3)
            .Set<BALANCE_PARAM>(0.6).Set<BOX_LENGTH>(0.2);
    auto tree = IKDTree<PointType>(params);
    EXPECT_NE(tree.implPointer(), nullptr);

}
TEST(IkdTreeTest, TestConstructor2) {
    auto tree = IKDTree<PointType>(IKDParameters::Create().Set<DELETE_PARAM>(0.3)
                                           .Set<BALANCE_PARAM>(0.6).Set<BOX_LENGTH>(0.2));
    EXPECT_NE(tree.implPointer(), nullptr);

}
TEST(IKdTreeTest, TestSetParams){
    auto tree = IKDTree<PointType>();
    tree.SetParam<DELETE_PARAM>(0.5);
    tree.SetParam<BALANCE_PARAM>(0.7);
    tree.SetParam<BOX_LENGTH>(0.3);
    //no way to check the value because the ikdTree don't expose the value

}