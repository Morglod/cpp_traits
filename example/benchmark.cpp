// install https://github.com/iboB/picobench

#define PICOBENCH_IMPLEMENT_WITH_MAIN
#include "picobench/picobench.hpp"

#include <cstdlib> // for rand

#include "./benchmark_domain.hpp"

static void bench_virtual_add(picobench::state& s)
{
    VSquare square;
    IAddable* iaddable = &square;
    s.set_result((uintptr_t)iaddable);

    for (auto _ : s) {
        virtual_add(iaddable);
    }
}
PICOBENCH(bench_virtual_add).iterations({ 1000, 10000, 50000 }).samples(1000);

static void bench_trait_add(picobench::state& s)
{
    Square square;
    Addable taddable(square);
    s.set_result((uintptr_t)&taddable);
    
    for (auto _ : s) {
        trait_add(taddable);
    }
}
PICOBENCH(bench_trait_add).iterations({ 1000, 10000, 50000 }).samples(1000);

static void bench_trait2_add(picobench::state& s)
{
    Square square;
    Addable2 taddable(square);
    s.set_result((uintptr_t)&taddable);
    
    for (auto _ : s) {
        trait2_add(taddable);
    }
}
PICOBENCH(bench_trait2_add).iterations({ 1000, 10000, 50000 }).samples(1000);


static void bench_trait3_add(picobench::state& s)
{
    Square square;
    Addable3 taddable(square);
    s.set_result((uintptr_t)&taddable);
    
    for (auto _ : s) {
        trait3_add(taddable);
    }
}
PICOBENCH(bench_trait3_add).iterations({ 1000, 10000, 50000 }).samples(1000);

static void bench_trait4_add(picobench::state& s)
{
    Square square;
    Addable4 taddable(square);
    s.set_result((uintptr_t)&taddable);
    
    for (auto _ : s) {
        trait4_add(taddable);
    }
}
PICOBENCH(bench_trait4_add).iterations({ 1000, 10000, 50000 }).samples(1000);

static void bench_trait5_add(picobench::state& s)
{
    Square square;
    Addable5 taddable(square);
    s.set_result((uintptr_t)&taddable);
    
    for (auto _ : s) {
        trait5_add(taddable);
    }
}
PICOBENCH(bench_trait5_add).iterations({ 1000, 10000, 50000 }).samples(1000);
