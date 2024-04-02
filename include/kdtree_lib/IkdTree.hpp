//
// Created by bowman han on 4/2/24.
//
#include "KdTreeLib.hpp"
#include "../../thirdparty/ikd-Tree/ikd-Tree/ikd_Tree.h"
#ifndef KDTREELIB_IKDTREE_HPP
namespace NSKdTreeLib{
    template <typename PointType>
    class IKDTree : public KDTreeLib<PointType> {
    public:
        using ImplType = KD_TREE<ikdTree_PointType>;
        IKDTree(){
            this->p_impl = new ImplType();
        }
        template<class TParams>
        IKDTree(TParams&& params) {
           this->p_impl = new ImplType();
           auto p = impl();
           p->Set_delete_criterion_param(params.template Get<DELETE_PARAM>());
           p->Set_balance_criterion_param(params.template Get<BALANCE_PARAM>());
           p->set_downsample_param(params.template Get<BOX_LENGTH>());
        }
        auto* implPointer() const{
            return reinterpret_cast<ImplType*>(this->p_impl);
        }
        template<typename TTag, typename TVal>
        void SetParam(TVal &&val) ;
        template<>
        void SetParam<DELETE_PARAM,double>(double &&val){
            impl()->Set_delete_criterion_param(val);
        }
        template<>
        void SetParam<BALANCE_PARAM,double>(double &&val){
            impl()->Set_balance_criterion_param(val);
        }
        template<>
        void SetParam<BOX_LENGTH,double>(double &&val){
            impl()->set_downsample_param(val);
        }
        ~IKDTree() {

        }
    private:
        inline auto* impl(){
            return reinterpret_cast<ImplType*>(this->p_impl);
        }
    };
}

#define KDTREELIB_IKDTREE_HPP

#endif //KDTREELIB_IKDTREE_HPP
