#ifndef KDTREELIB_KDTREELIB_HPP
#define KDTREELIB_KDTREELIB_HPP
#include <vector>
#include <memory>
#include <random>
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
        union {
            struct {
                float x;
                float y;
                float z;
            }point;
            float vertex[3];
        }min;
        union {
            struct {
                float x;
                float y;
                float z;
            }point;
            float vertex[3];
        }max;
    };

    struct Point3 {
        float x, y, z;
        inline constexpr Point3(float px = 0.0f, float py = 0.0f, float pz = 0.0f) : x(px), y(py), z(pz) {}
    };
    ///Random Point3 Generator
    struct RandomPoint3Generator {
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_real_distribution<float> dist;
        ///Random Point3 Generator
        /// param min: the min value of the point
        /// param max: the max value of the point
        RandomPoint3Generator(float min,float max):gen(rd()),dist(min,max){}
        Point3 next(){
            return Point3(dist(gen), dist(gen), dist(gen));
        }
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
        //using Ptr = std::shared_ptr<KDTreeLib<PointType>>;
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

        virtual  inline size_t size()=0;

        virtual inline size_t validnum()=0;

        void root_alpha(float &alpha_bal, float &alpha_del);

        virtual inline void Build( PointVector &point_cloud)=0;

        void
        Nearest_Search(PointType point, int k_nearest, PointVector &Nearest_Points, std::vector<float> &Point_Distance,
                       double max_dist = INFINITY);

        inline void Box_Search(const KDLibBoxPointType &Box_of_Point, PointVector &Storage);

        void Radius_Search(PointType point, const float radius, PointVector &Storage);

        inline int Add_Points(PointVector &PointToAdd, bool downsample_on);

        void Add_Point_Boxes(std::vector<KDLibBoxPointType> &BoxPoints);

        void Delete_Points(PointVector &PointToDel);

        int Delete_Point_Boxes(std::vector<KDLibBoxPointType> &BoxPoints);

        void acquire_removed_points(PointVector &removed_points);

        inline auto* implPointer() const;
    protected:
        void* p_impl;
    private:

    };


}
#endif //KDTREELIB_KDTREELIB_HPP
