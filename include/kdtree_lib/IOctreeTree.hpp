//
// Created by bowman han on 4/2/24.
//
#include "KdTreeLib.hpp"
#include "../../thirdparty/i-octree/octree2/Octree.h"
#ifndef KDTREELIB_IOCTREE_HPP
namespace NSKdTreeLib::IOctree{
    namespace detail{
        template<typename PointType, typename TTag, typename TVal>
        struct Specialized;
        template<typename PointType, typename TVal>
        struct Specialized<PointType, BUCKET_SIZE,TVal>{
            static void Set(thuni::Octree *tree, TVal &&val){
                tree->set_bucket_size(static_cast<float>(val));
            }
        };
        template<typename PointType, typename TVal>
        struct Specialized<PointType, MIN_EXTENT,TVal>{
            static void Set(thuni::Octree *tree, TVal &&val){
                tree->set_min_extent(static_cast<float>(val));
            }
        };
        template<typename PointType, typename TVal>
        struct Specialized<PointType, COPY_POINTS,TVal>{
            static void Set(thuni::Octree *tree, TVal &&val){
                //doing nothing because the iOctree actually does not implement this
            }
        };
    };
    using namespace NSKdTreeLib;

    template <typename PointType>
    class IOcTree:public KDTreeLib<PointType> {
    public:
        /// 点云容器类型
        using PointVector = std::vector<PointType, Eigen::aligned_allocator<PointType>>;
        /// 本体智能指针类型
        using Ptr = std::shared_ptr<KDTreeLib<PointType>>;
        ///The type behind the Wrapper
        using ImplType = thuni::Octree;

        IOcTree(){
            this->p_impl = new  ImplType();
        }

        template<typename TParams>
        IOcTree(TParams&& params) {
            /*
             * size_t bucketSize_, bool copyPoints_, float minExtent_, int dim_
             */
           this->p_impl = new ImplType(params.template Get<DELETE_PARAM>(),
                   params.template Get<BALANCE_PARAM>(), params.template Get<BOX_LENGTH>());
        }
        auto* implPointer() const{
            return reinterpret_cast<ImplType*>(this->p_impl);
        }


        template<typename TTag, typename TVal>
        void SetParam(TVal &&val){
            IOctree::detail::Specialized<PointType,TTag,TVal>::Set(impl(),std::forward<TVal>(val));
        }

        ~IOcTree() {
            delete impl();
        }

        //// @brief return the IOcTree size
        virtual inline  size_t size()  {
            return impl()->size();
        }

        inline size_t validnum()  {
            throw new std::runtime_error("No Implementation Available");
        }
        int Add_Points(PointVector & PointToAdd, bool downsample_on){
            return impl()->update_record(PointToAdd,downsample_on);
        }
        void Build( PointVector &point_cloud){
            impl()->initialize_record(point_cloud);
        }

        void Box_Search(const KDLibBoxPointType &Box_of_Point, PointVector &Storage){
            //impl()->Box_Search(Box_of_Point,Storage);
            throw new std::runtime_error("Not Implemented yet");
        }

    private:
        inline auto* impl(){
            assert(this->p_impl);
            return reinterpret_cast<ImplType*>(this->p_impl);
        }
    };

}
#define KDTREELIB_IOCTREE_HPP

#endif //KDTREELIB_IOCTREE_HPP
