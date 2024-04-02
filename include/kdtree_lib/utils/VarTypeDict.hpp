//
// Created by bowman han on 3/31/24.
//

#ifndef METAPROGRAMMING_VARTYPEDICT_H
#define METAPROGRAMMING_VARTYPEDICT_H
#include <type_traits>
namespace NSVarTypeDict {
    /* 用来存储类型 */
    template <typename T>
    struct Identity_
    {
        using type = T;
    };
    /*待定参数占位*/
    struct NullParameter{};
    /*N表示要构造的元素数量，TCont存储最终结果，T已经生成的序列*/
    template <size_t N, template<typename ...> class TCont, typename ...T>
    struct Create_ {
        using type = typename Create_<N-1,TCont,NullParameter,T...>::type;
    };
    /*特化最后一个元素*/
    template <template<typename...> class TCont, typename ...T>
    struct Create_<0,TCont,T...>{
        using type = TCont<T...>;
    };
    /* 递归查找tag在参数包中的位置
     * @param TFindTag: 要查找的tag
     * @param N：当前扫描的位置
     * @param TCurTag：当前扫描的tag
     * @param TTags：剩余的tag
     */
    template <typename TFindTag, size_t N, typename TCurTag, typename...TTags>
    struct Tag2ID_
    {
        //N从0开始，每次递归加1，直到特化找到目标
        //TTags每次消耗一个元素
        constexpr static size_t value = Tag2ID_<TFindTag, N + 1, TTags...>::value;
    };
    /*特化处理，当找到目标tag时候结束递归*/
    template <typename TFindTag, size_t N, typename...TTags>
    struct Tag2ID_<TFindTag, N, TFindTag, TTags...>
    {
        //返回当前位置
        constexpr static size_t value = N;
    };
    /*Tag2ID的api
     *@param TFindTag 要查找的类型
     *@param TTags 所有的类型*/
    template <typename TFindTag, typename...TTags>
    constexpr size_t Tag2ID = Tag2ID_<TFindTag, 0, TTags...>::value;
/************begin of Pos2Type ************/
    template <size_t Pos, typename...TTags>
    struct Pos2Type_
    {
        static_assert((Pos != 0), "Invalid position.");
    };

    template <size_t Pos, typename TCur, typename...TTags>
    struct Pos2Type_<Pos, TCur, TTags...>
    {
        using type = typename std::conditional_t<(Pos == 0),

                Identity_<TCur>,
        Pos2Type_<Pos-1, TTags...>>::type;
    };

    template <size_t Pos, typename...TTags>
    using Pos2Type = typename Pos2Type_<Pos, TTags...>::type;
/************end of Pos2Type ************/
/************begin of NewTupleType ************/
    template <typename TVal,size_t N,size_t M,
            typename TProcessedTypes,typename ... TRemainTypes>
    struct NewTupleType_;
    template <typename TVal,
            //n: the position of target in type array
            //m: already scanned type count
            size_t N,size_t M,
            template <typename...> class TCont,
            typename... TModifiedTypes,typename TCurType,typename ... TRemainTypes>
            struct NewTupleType_<TVal,N,M,TCont<TModifiedTypes...>,
                    TCurType,TRemainTypes...>
            {
                //每次M增加1，并把CurType放入TCont
                using type =typename  NewTupleType_<TVal,N,M+1,
                    TCont<TModifiedTypes...,TCurType>,TRemainTypes...>::type;
            };
/*  N=M时候的特化处理，这时候搜索已经完成，终结循环，返回目标类型*/
    template <typename TVal,size_t N,template <typename ...> class TCont,
              typename...TModifiedTypes,
              typename TCurType,
              typename ...TRemainTypes>
              struct NewTupleType_<TVal,N,N,TCont<TModifiedTypes...>,
                      TCurType,TRemainTypes...>
              {
                  //replace TCurType(which is NullParameter) with TVal
                  using type = TCont<TModifiedTypes...,TVal,TRemainTypes...>;
              };
/*    最终使用的api*/
    template <typename TVal,size_t TagPos,
                typename TCont,typename... TRemainTypes>
                using NewTupleType = typename NewTupleType_<TVal, TagPos,0,TCont,
                                     TRemainTypes...>::type;
/************end of NewTupleType ************/
    /*ZeroCost Abstraction for VarTypeDict
     * 0成本抽象的可变类型参数词典
     * sample usage:
         auto dict = VarTypeDict<A,B,C>::Create()
            .Set<A>(12.5f)
            .Set<B>(1)
            .Set<C>(13.99);
        cout <<"valA "<< dict.Get<A>() << endl;
        cout <<"valB "<< dict.Get<B>() << endl;
        cout <<"valC "<< dict.Get<C>() << endl;
     * */
    template <typename ... TParameters>
    struct VarTypeDict{
        template <typename ... TTypes>
        struct Values {
            Values()=default;
            Values(std::shared_ptr<void>(&&input)[sizeof...(TTypes)]){
                for(size_t i=0;i<sizeof...(TTypes);i++){
                    m_tuple[i]=std::move(input[i]);
                }
            }
        public:
            template <typename TTag, typename TVal>
            auto Set(TVal&& val)&&{
                using namespace NSVarTypeDict;
                //获取TTag位置
                constexpr static size_t TagPos = Tag2ID<TTag, TParameters...>;
                using rawVal = std::decay_t<TVal>;
                rawVal* tmp = new rawVal(std::forward<TVal>(val));
                m_tuple[TagPos]=std::shared_ptr<void>(tmp,[](void* ptr){
                    rawVal* nptr = static_cast<rawVal*>(ptr);
                    delete nptr;
                });
                //按照给定类型，重新构造对象
                using new_type = NewTupleType<rawVal,TagPos,Values<>,TTypes...>;
                return new_type(std::move(m_tuple));
            }
            /* 获取指定类型的值
             * @param TTag: 要获取的类型
             */
            template <typename TTag>
            auto& Get() const
            {
                using namespace NSVarTypeDict;
                constexpr static size_t TagPos = Tag2ID<TTag, TParameters...>;
                using AimType = Pos2Type<TagPos, TTypes...>;

                void* tmp = m_tuple[TagPos].get();
                AimType* res = static_cast<AimType*>(tmp);
                return *res;
            }

            template <typename TTag>
            using ValueType = Pos2Type<Tag2ID<TTag, TParameters...>, TTypes...>;
        private:
            std::shared_ptr<void> m_tuple[sizeof...(TTypes)];
        };
    public:
        static auto Create(){
            using namespace NSVarTypeDict;
            //传入Create_只有前两个参数，T...是空的，最后构造出Values<NullParameter,NullParameter...>
            using type =typename  Create_<sizeof...(TParameters),
                                Values>::type;
            return type{};
        }
    };

}
#endif //METAPROGRAMMING_VARTYPEDICT_H
