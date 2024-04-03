//
// Created by bowman han on 4/2/24.
//
#include "KdTreeLib.hpp"
#include "../../thirdparty/ikd-Tree/ikd-Tree/ikd_Tree.h"
#ifndef KDTREELIB_IKDTREE_HPP
namespace NSKdTreeLib{
    namespace detail{
        template<typename PointType, typename TTag, typename TVal>
        struct Specialized;
        template<typename PointType, typename TVal>
        struct Specialized<PointType, DELETE_PARAM,TVal>{
            static void Set(KD_TREE<PointType> *tree, TVal &&val){
                tree->Set_delete_criterion_param(static_cast<float>(val));
            }
        };
        template<typename PointType, typename TVal>
        struct Specialized<PointType, BALANCE_PARAM,TVal>{
            static void Set(KD_TREE<PointType> *tree, TVal &&val){
                tree->Set_balance_criterion_param(static_cast<float>(val));
            }
        };
        template<typename PointType, typename TVal>
        struct Specialized<PointType, BOX_LENGTH,TVal>{
            static void Set(KD_TREE<PointType> *tree, TVal &&val){
                tree->set_downsample_param(val);
            }
        };
    };
    template <typename PointType>
    class IKDTree:public KDTreeLib<PointType> {
    public:
        /// 点云容器类型
        using PointVector = std::vector<PointType, Eigen::aligned_allocator<PointType>>;
        /// 本体智能指针类型
        using Ptr = std::shared_ptr<KDTreeLib<PointType>>;
        ///The type behind the Wrapper
        using ImplType = KD_TREE<PointType>;


        IKDTree(){
            this->p_impl = new  KD_TREE<PointType>();
        }

        template<typename TParams>
        IKDTree(TParams&& params) {

           this->p_impl = new ImplType(params.template Get<DELETE_PARAM>(),
                   params.template Get<BALANCE_PARAM>(), params.template Get<BOX_LENGTH>());
        }
        auto* implPointer() const{
            return reinterpret_cast<ImplType*>(this->p_impl);
        }


        template<typename TTag, typename TVal>
        void SetParam(TVal &&val){
            detail::Specialized<PointType,TTag,TVal>::Set(impl(),std::forward<TVal>(val));
        }

        ~IKDTree() {

        }

        //// @brief return the KDTree size
        virtual inline  size_t size()  {
            return impl()->size();
        }

        inline size_t validnum()  {
            return impl()->validnum();
        }
        int Add_Points(PointVector & PointToAdd, bool downsample_on){
            return impl()->Add_Points(PointToAdd,downsample_on);
        }
        void Build( PointVector &point_cloud){
            impl()->Build(point_cloud);
        }

        void Box_Search(const KDLibBoxPointType &Box_of_Point, PointVector &Storage){
            impl()->Box_Search(Box_of_Point,Storage);
        }

    private:
        inline auto* impl(){
            assert(this->p_impl);
            return reinterpret_cast<ImplType*>(this->p_impl);
        }
    };

}
template class KD_TREE<NSKdTreeLib::Point3>;
#define KDTREELIB_IKDTREE_HPP

#endif //KDTREELIB_IKDTREE_HPP
