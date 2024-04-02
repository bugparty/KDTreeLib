#ifndef KDTREELIB_KDTREELIB_HPP
#define KDTREELIB_KDTREELIB_HPP
#include <vector>
#include <memory>
#include <pcl/point_types.h>
#include "kdtree_lib/utils/VarTypeDict.hpp"
namespace NSKdTreeLib {
    namespace detail{
    }
    struct DELETE_PARAM {
    };
    struct BALANCE_PARAM {
    };
    struct BOX_LENGTH {
    };
    struct BucketSize {
    };
    struct CopyPoints {
    };
    struct MinExtent {
    };
    enum class KDTreeType {
        IKDTREE,
        iOCTREE
    };
///Define the parameters of the iKDTree
    struct IKDParameters : public NSVarTypeDict::VarTypeDict<NSKdTreeLib::DELETE_PARAM, NSKdTreeLib::BALANCE_PARAM, NSKdTreeLib::BOX_LENGTH> {
    };
///Define the parameters of the iOctree
    struct IOctreeParameters : public NSVarTypeDict::VarTypeDict<NSKdTreeLib::BucketSize, NSKdTreeLib::CopyPoints, NSKdTreeLib::MinExtent> {
    };
    struct KDLibBoxPointType {
        float vertex_min[3];
        float vertex_max[3];
    };

    struct KDTreeLib_PointType {
        float x, y, z;
        inline constexpr KDTreeLib_PointType(float px = 0.0f, float py = 0.0f, float pz = 0.0f) : x(px), y(py), z(pz) {}
    };
    /**
     * The KDTree Library
     * @param TParams: the  constructor parameters of the KDTree
     * @param PointType: the type of the cloud point in the KDTree
     */
    template<typename PointType>
    class KDTreeLib {
    public:
        /// 点云容器类型
        using PointVector = std::vector<PointType, Eigen::aligned_allocator<PointType>>;
        /// 本体智能指针类型
        using Ptr = std::shared_ptr<KDTreeLib<PointType>>;
        //Delete the default constructor and assignment operator
        //KDTreeLib() = delete;
        KDTreeLib()=default;
        KDTreeLib(KDTreeLib&) = delete;
        KDTreeLib(KDTreeLib&&) = delete;
        KDTreeLib &&operator=(const KDTreeLib &) = delete;
        KDTreeLib &&operator=(KDTreeLib &&) = delete;
        /**
         * Constructor, you don't need to pass the type of KDTree, it will be determined by the parameters type
         * By use specialization instead of virtual functions, the performance of the code will be greatly improved
         */
        template<class TParams>
        KDTreeLib(TParams &params) {};

        /**
         * Initialize the KDTree
         * @param TParams: the parameters of the KDTree
         */
        template<class TParams>
        void Initialize(TParams &params) {}

        virtual ~KDTreeLib() {}

        /**
         * Set the parameters of the KDTree
         * @param TTag: the type of the parameter
         * @param TVal: the value of the parameter
         * 可以任意设置参数
         */
        template<typename TTag, typename TVal>
        void SetParam(TVal &&val) ;

        size_t size();

        size_t validnum();

        void root_alpha(float &alpha_bal, float &alpha_del);

        void Build(const PointVector &point_cloud);

        void
        Nearest_Search(PointType point, int k_nearest, PointVector &Nearest_Points, std::vector<float> &Point_Distance,
                       double max_dist = INFINITY);

        void Box_Search(const KDLibBoxPointType &Box_of_Point, PointVector &Storage);

        void Radius_Search(PointType point, const float radius, PointVector &Storage);

        int Add_Points(PointVector &PointToAdd, bool downsample_on);

        void Add_Point_Boxes(std::vector<KDLibBoxPointType> &BoxPoints);

        void Delete_Points(PointVector &PointToDel);

        int Delete_Point_Boxes(std::vector<KDLibBoxPointType> &BoxPoints);

        void acquire_removed_points(PointVector &removed_points);

        auto* implPointer() const;
    protected:
        void* p_impl;
    private:

    };


}
#endif //KDTREELIB_KDTREELIB_HPP
