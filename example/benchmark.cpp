// install https://github.com/iboB/picobench

#define PICOBENCH_IMPLEMENT_WITH_MAIN
#include "picobench/picobench.hpp"

#include <cstdlib> // for rand

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
    int counter = 0;
    void add(int x) override {
        counter += x;
    }
};

TRAIT_STRUCT(Addable,
    TRAIT_METHOD(void, add, int)
)

void virtual_add(IAddable* x) {
    x->add(rand());
}

void trait_add(Addable& x) {
    x.add(rand());
}

static void bench_virtual_add(picobench::state& s)
{
    VSquare square;
    IAddable* iaddable = &square;
    s.set_result((uintptr_t)iaddable);

    for (auto _ : s) {
        virtual_add(iaddable);
    }
}
PICOBENCH(bench_virtual_add).iterations({ 1000, 10000, 50000, 100000 });

static void bench_trait_add(picobench::state& s)
{
    Square square;
    Addable taddable(square);
    s.set_result((uintptr_t)taddable.self);
    
    for (auto _ : s) {
        trait_add(taddable);
    }
}
PICOBENCH(bench_trait_add).iterations({ 1000, 10000, 50000, 100000 });