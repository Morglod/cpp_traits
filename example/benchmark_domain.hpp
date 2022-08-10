#pragma once


#include "../traits.hpp"

struct Square {
    int counter = 0;
    void add(int x) { counter += x; }
};

class IAddable {
public:
    virtual void add(int x) = 0;
};

class VSquare : public IAddable {
public:
    void add(int x) override {
        counter += x;
    }
    int counter = 0;
};

// TRAIT_STRUCT(Addable,
//     TRAIT_METHOD(void, add, int)
// )

// ---------- current implementation --------------

template <typename T>
struct Addable_impl_T {
    void (*add)(void *self, int) = [](void *self, int _1) {
        return ((T *)self)->add(_1);
    };
};

struct Addable_impl {
    void (*add)(void *self, int);
};

struct Addable {
    void *self = nullptr;

    Addable() = delete;

    inline void add(int _1) {
        return _impl->add(self, _1);
    }

    template <typename T>
    Addable(T &t) : self(&t) {
        static Addable_impl_T<T> impl;
        _impl = (Addable_impl *)(void *)&impl;
    }

private:
    Addable_impl *_impl;
};

// ------  with virtual ---------


struct Addable2_impl {
    virtual void add(void *self, int) = 0;
};

template <typename T>
struct Addable2_impl_T : public Addable2_impl {
    void add(void *self, int _1) override {
        return ((T *)self)->add(_1);
    }
};

struct Addable2 {
    void *self = nullptr;

    Addable2() = delete;

    inline void add(int _1) {
        return _impl->add(self, _1);
    }

    template <typename T>
    Addable2(T &t) : self(&t) {
        static Addable2_impl_T<T> impl;
        _impl = (Addable2_impl *)&impl;
    }

private:
    Addable2_impl *_impl;
};

// ------  with static unsafe ---------


struct Addable3_impl {
    static void add(void *self, int) {}
};

template <typename T>
struct Addable3_impl_T {
    static void add(void *self, int _1) {
        return ((T *)self)->add(_1);
    }
};

struct Addable3 {
    void *self = nullptr;

    Addable3() = delete;

    inline void add(int _1) {
        return _impl->add(self, _1);
    }

    template <typename T>
    Addable3(T &t) : self(&t) {
        static Addable3_impl_T<T> impl;
        _impl = (Addable3_impl *)(void *)&Addable3_impl_T<T>::add;
    }

private:
    Addable3_impl *_impl;
};


// ------  with direct ptrs ---------

struct Addable4 {
    void *self = nullptr;

    Addable4() = delete;

    inline void add(int _1) {
        return _add(self, _1);
    }

    template <typename T>
    Addable4(T &t) : self(&t) {
        static auto s_add = [](void *self, int _1) {
            return ((T *)self)->add(_1);
        };
        _add = s_add;
    }

private:
    void (*_add)(void *self, int);
};

// ------  unsafe with same type fake ---------

template <typename T>
struct Addable5_impl_T {
    static void add(void* self, int _1) {
        return ((T *)self)->add(_1);
    }
};

struct Addable5 {
    void *self = nullptr;

    typedef void (*add_type)(void* self, int _1);

    Addable5() = delete;

    inline void add(int _1) {
        return ((add_type)_impl_add)(self, _1);
    }

    template <typename T>
    Addable5(T &t) : self(&t) {
        static Addable5_impl_T<T> impl;
        _impl_add = Addable5_impl_T<T>::add;
    }

private:
    void *_impl_add;
};

//--------------

void virtual_add(IAddable* x);
void trait_add(Addable& x);
void trait2_add(Addable2& x);
void trait3_add(Addable3& x);
void trait4_add(Addable4& x);
void trait5_add(Addable5& x);