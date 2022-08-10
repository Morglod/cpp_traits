#include "../traits.hpp"
#include <stdio.h>

struct Square {
    int counter = 0;
    void add(int x) { counter += x; }
};

TRAIT_STRUCT(Addable,
    TRAIT_METHOD(void, add, int)
)

void add_10(Addable x) {
    x.add(10);
}

int main() {
    Square s;
    add_10(s);
}