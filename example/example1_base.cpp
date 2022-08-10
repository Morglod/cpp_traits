#include "../traits.hpp"
#include <stdio.h>

struct Square {
    int id = 0;
    int counter = 0;

    void add(int x) {
        counter += x;
    }

    void draw() {
        printf("Square%i: %i\n", id, counter);
    }
};

struct Circle {
    int id = 0;
    int counter = 0;

    void add(int x) {
        counter += x;
    }

    void draw() {
        printf("Circle%i: %i\n", id, counter);
    }
};

TRAIT_STRUCT(Drawable,
    TRAIT_METHOD(void, draw)
)

TRAIT_STRUCT(Addable,
    TRAIT_METHOD(void, add, int)
)

void add_10(Addable x) {
    x.add(10);
}

void draw_smth(Drawable x) {
    x.draw();
}

int main() {
    Square s1;
    Square s2; s2.id = 1;
    Circle c;

    add_10(s1);
    add_10(s1);
    add_10(s2);
    add_10(c);

    draw_smth(s1);
    draw_smth(s2);
    draw_smth(c);

    return 0;
}
