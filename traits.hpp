#pragma once

#include "macro_map.hpp"
#include "ppnarg.hpp"

/* Vladimir Kurzhkov 2022 MIT github.com/Morglod/cpp_traits */

#define _TRAIT_STRUCT_CONCAT_DELAY(x, y) x##y
#define _TRAIT_STRUCT_CONCAT(x, y) _TRAIT_STRUCT_CONCAT_DELAY(x, y)

#define _TRAIT_COMMA_IF_DELAYED(...) __VA_OPT__( , __VA_ARGS__ )
#define _TRAIT_COMMA_IF_(...) _TRAIT_COMMA_IF_DELAYED(__VA_ARGS__)

#define _TRAIT_NAMED_ARGS1_RUN_1(a) a _1
#define _TRAIT_NAMED_ARGS1_RUN_2(a, ...) a _2, _TRAIT_NAMED_ARGS1_RUN_1(__VA_ARGS__)
#define _TRAIT_NAMED_ARGS1_RUN_3(a, ...) a _3, _TRAIT_NAMED_ARGS1_RUN_2(__VA_ARGS__)
#define _TRAIT_NAMED_ARGS1_RUN_4(a, ...) a _4, _TRAIT_NAMED_ARGS1_RUN_3(__VA_ARGS__)
#define _TRAIT_NAMED_ARGS1_RUN_5(a, ...) a _5, _TRAIT_NAMED_ARGS1_RUN_4(__VA_ARGS__)
#define _TRAIT_NAMED_ARGS1_RUN_6(a, ...) a _6, _TRAIT_NAMED_ARGS1_RUN_5(__VA_ARGS__)
#define _TRAIT_NAMED_ARGS1_RUN_7(a, ...) a _7, _TRAIT_NAMED_ARGS1_RUN_6(__VA_ARGS__)
#define _TRAIT_NAMED_ARGS1_RUN_8(a, ...) a _8, _TRAIT_NAMED_ARGS1_RUN_7(__VA_ARGS__)
#define _TRAIT_NAMED_ARGS1_RUN_9(a, ...) a _9, _TRAIT_NAMED_ARGS1_RUN_8(__VA_ARGS__)
#define _TRAIT_NAMED_ARGS1_RUN_10(a, ...) a _10, _TRAIT_NAMED_ARGS1_RUN_9(__VA_ARGS__)
#define _TRAIT_NAMED_ARGS1_RUN_(...) __VA_OPT__( _TRAIT_STRUCT_CONCAT(_TRAIT_NAMED_ARGS1_RUN_, PP_NARG(__VA_ARGS__)) (__VA_ARGS__)  )

#define _TRAIT_NAMED_ARGS1_(...) _TRAIT_NAMED_ARGS1_RUN_(__VA_ARGS__)

#define _TRAIT_NAMED_ARGS2_RUN_1(a) _1
#define _TRAIT_NAMED_ARGS2_RUN_2(a, ...) _2, _TRAIT_NAMED_ARGS2_RUN_1(__VA_ARGS__)
#define _TRAIT_NAMED_ARGS2_RUN_3(a, ...) _3, _TRAIT_NAMED_ARGS2_RUN_2(__VA_ARGS__)
#define _TRAIT_NAMED_ARGS2_RUN_4(a, ...) _4, _TRAIT_NAMED_ARGS2_RUN_3(__VA_ARGS__)
#define _TRAIT_NAMED_ARGS2_RUN_5(a, ...) _5, _TRAIT_NAMED_ARGS2_RUN_4(__VA_ARGS__)
#define _TRAIT_NAMED_ARGS2_RUN_6(a, ...) _6, _TRAIT_NAMED_ARGS2_RUN_5(__VA_ARGS__)
#define _TRAIT_NAMED_ARGS2_RUN_7(a, ...) _7, _TRAIT_NAMED_ARGS2_RUN_6(__VA_ARGS__)
#define _TRAIT_NAMED_ARGS2_RUN_8(a, ...) _8, _TRAIT_NAMED_ARGS2_RUN_7(__VA_ARGS__)
#define _TRAIT_NAMED_ARGS2_RUN_9(a, ...) _9, _TRAIT_NAMED_ARGS2_RUN_8(__VA_ARGS__)
#define _TRAIT_NAMED_ARGS2_RUN_10(a, ...) _10, _TRAIT_NAMED_ARGS2_RUN_9(__VA_ARGS__)
#define _TRAIT_NAMED_ARGS2_RUN_(...) __VA_OPT__( _TRAIT_STRUCT_CONCAT(_TRAIT_NAMED_ARGS2_RUN_, PP_NARG(__VA_ARGS__)) (__VA_ARGS__) )

#define _TRAIT_NAMED_ARGS2_(...) _TRAIT_NAMED_ARGS2_RUN_(__VA_ARGS__)

#define TRAIT_METHOD(_RET, _NAME, ...) (_RET, _NAME, __VA_ARGS__)

#define __TRAIT_METHOD_PICK_RET(_ret, ...) _ret
#define _TRAIT_METHOD_PICK_RET(_trait_tuple_) __TRAIT_METHOD_PICK_RET _trait_tuple_

#define __TRAIT_METHOD_PICK_NAME(_ret, _name, ...) _name
#define _TRAIT_METHOD_PICK_NAME(_trait_tuple_) __TRAIT_METHOD_PICK_NAME _trait_tuple_

#define __TRAIT_METHOD_PICK_ARGS(_ret, _name, ...) __VA_ARGS__
#define _TRAIT_METHOD_PICK_ARGS(_trait_tuple_) __TRAIT_METHOD_PICK_ARGS _trait_tuple_

#define _TRAIT_STRUCT_METHOD_POINTER_MEMBER(_method_tuple_) \
    _TRAIT_METHOD_PICK_RET(_method_tuple_) (* _TRAIT_METHOD_PICK_NAME(_method_tuple_)) (void* self _TRAIT_COMMA_IF_( _TRAIT_METHOD_PICK_ARGS(_method_tuple_) ) ) = &Self::_TRAIT_STRUCT_CONCAT(static_, _TRAIT_METHOD_PICK_NAME(_method_tuple_));

#define _TRAIT_STRUCT_METHOD_POINTER_STATIC(_method_tuple_) \
    static _TRAIT_METHOD_PICK_RET(_method_tuple_) _TRAIT_STRUCT_CONCAT(static_, _TRAIT_METHOD_PICK_NAME(_method_tuple_)) (void* self _TRAIT_COMMA_IF_( _TRAIT_NAMED_ARGS1_(_TRAIT_METHOD_PICK_ARGS(_method_tuple_)) ) ) { \
        return ((T*)self)->_TRAIT_METHOD_PICK_NAME(_method_tuple_) ( _TRAIT_NAMED_ARGS2_(_TRAIT_METHOD_PICK_ARGS(_method_tuple_)) ); \
    };

#define _TRAIT_STRUCT_METHOD_POINTER_NO_INIT(_method_tuple_) \
    _TRAIT_METHOD_PICK_RET(_method_tuple_) (* _TRAIT_METHOD_PICK_NAME(_method_tuple_)) (void* self _TRAIT_COMMA_IF_( _TRAIT_METHOD_PICK_ARGS(_method_tuple_) ) );

#define _TRAIT_STRUCT_PROXY_METHOD(_method_tuple_) \
    inline _TRAIT_METHOD_PICK_RET(_method_tuple_) _TRAIT_METHOD_PICK_NAME(_method_tuple_) ( _TRAIT_NAMED_ARGS1_(_TRAIT_METHOD_PICK_ARGS(_method_tuple_)) ) { \
        return _impl-> _TRAIT_METHOD_PICK_NAME(_method_tuple_) (_get_self() _TRAIT_COMMA_IF_( _TRAIT_NAMED_ARGS2_(_TRAIT_METHOD_PICK_ARGS(_method_tuple_)) ) ); \
    }

#define _TRAIT_STRUCT_BASE(_NAME, ...) \
    template<typename T> \
    struct _NAME##_impl_T { \
        using Self = _NAME##_impl_T<T>; \
        MACRO_MAP(_TRAIT_STRUCT_METHOD_POINTER_MEMBER, __VA_ARGS__) \
        MACRO_MAP(_TRAIT_STRUCT_METHOD_POINTER_STATIC, __VA_ARGS__) \
    }; \
    struct _NAME##_impl { \
        MACRO_MAP(_TRAIT_STRUCT_METHOD_POINTER_NO_INIT, __VA_ARGS__) \
    }; \
    struct _NAME { \
        void* self = nullptr; \
        _NAME() = delete; \
        MACRO_MAP(_TRAIT_STRUCT_PROXY_METHOD, __VA_ARGS__) \
        template<typename T> \
        _NAME(T& t) : self(&t) { \
            static _NAME##_impl_T<T> impl; \
            _impl = (_NAME##_impl*)(void*)&impl; \
        } \
    private: \
        inline void* _get_self() { return self; } \
        _NAME##_impl* _impl; \
    };

#define _TRAIT_STRUCT_PTR(_NAME, ...) \
    struct _NAME##_ptr { \
        std::shared_ptr<void> self = nullptr; \
        MACRO_MAP(_TRAIT_STRUCT_PROXY_METHOD, __VA_ARGS__) \
        _NAME##_ptr() = default; \
        template<typename T> \
        _NAME##_ptr(typename std::shared_ptr<T> const& t) : self(std::reinterpret_pointer_cast<void>(t)) { \
            static _NAME##_impl_T<T> impl; \
            _impl = (_NAME##_impl*)(void*)&impl; \
        } \
    private: \
        inline void* _get_self() { return self.get(); } \
        _NAME##_impl* _impl = nullptr; \
    };

#ifdef _MEMORY_
    #define TRAITS_SHARED_PTR
#endif

#ifdef TRAITS_SHARED_PTR

#define TRAIT_STRUCT(_NAME, ...) \
    _TRAIT_STRUCT_BASE(_NAME, __VA_ARGS__) \
    _TRAIT_STRUCT_PTR(_NAME, __VA_ARGS__)

#else

#define TRAIT_STRUCT(_NAME, ...) _TRAIT_STRUCT_BASE(_NAME, __VA_ARGS__)

#endif