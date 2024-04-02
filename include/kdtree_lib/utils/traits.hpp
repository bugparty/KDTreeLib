//
// Created by bowman han on 4/2/24.
//

#ifndef KDTREELIB_TRAITS_HPP
#define KDTREELIB_TRAITS_HPP
namespace NSKdTreeLib::Traits{
    /** 用来存储类型 */
    template <typename T>
    struct Identity_
    {
        using type = T;
    };
/**待定参数占位*/
    struct NullParameter{};
}

#endif //KDTREELIB_TRAITS_HPP
