#include <cstdlib> // for rand

#include "./benchmark_domain.hpp"

__declspec(noinline) void virtual_add(IAddable* x) {
    x->add(rand());
}

__declspec(noinline) void trait_add(Addable& x) {
    x.add(rand());
}

__declspec(noinline) void trait2_add(Addable2& x) {
    x.add(rand());
}

__declspec(noinline) void trait3_add(Addable3& x) {
    x.add(rand());
}

__declspec(noinline) void trait4_add(Addable4& x) {
    x.add(rand());
}

__declspec(noinline) void trait5_add(Addable5& x) {
    x.add(rand());
}