# Traits

Use traits without initial struct modifications and templates

"Trait" structure would hold pointer to initial object & pointer to implementation

static cost will be: 1 pointer per method per type

```cpp
struct Square {
    int counter = 0;
    void add(int x) { counter += x; }
};

// define trait
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
```

### How it works

In example above, `Addable` type has constructor:

```cpp
template<typename T> Addable(T& t);
```

Which saves pointer to T and picks specific trait's implementation for type T.

### Build example

Run `example/build.cmd / sh` or use `example/CMakeLists.txt`

<details>
<summary>

## Whats inside macro?

</summary>

Trait structure under macro:

```cpp
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
```

</details>

<details>
<summary>

## How to own shared_ptr through trait?

</summary>

Strange question, but why not

Better check "how to store shared_ptr in trait"

[real example](./example/example2_get_ptr.cpp)

```cpp
struct MyObject : public std::enable_shared_from_this<MyObject> {
    inline std::shared_ptr<void> get_ptr() {
        return shared_from_this(); // comes from enable_shared_from_this
    }
};

TRAIT_STRUCT(DataHandler,
    TRAIT_METHOD(std::shared_ptr<void>, get_ptr)
)

void take_data(DataHandler dh) {
    std::shared_ptr<void> ptr_to_my_object = dh.get_ptr();
}

void do_stuff() {
    auto obj = std::make_shared<MyObject>();
    take_data(*(obj.get()));
}
```

</details>

<details>
<summary>

## How to store shared_ptr inside trait?

</summary>

```cpp
#define TRAITS_SHARED_PTR
#include "traits.hpp"

struct MyObject : public std::enable_shared_from_this<MyObject> {
    inline std::shared_ptr<void> get_ptr() {
        return shared_from_this(); // comes from enable_shared_from_this
    }
};

TRAIT_STRUCT(DataHandler,
    TRAIT_METHOD(std::shared_ptr<void>, get_ptr)
)

void take_data(DataHandler_ptr dh) { // <------ we use _ptr version here which stores shared_ptr as self
    return dh;
}

void do_stuff() {
    DataHandler_ptr data_trait; // <------ also _ptr version could be initialized with `nullptr`
    {
        auto obj = std::make_shared<Storage>();
        obj->_data = new char[] { "Hello world!" };

        // get as return value
        data_trait = take_data(obj);

        // or just cast
        data_trait = obj;
    }
    data_trait.print();
}
```

</details>

---

## Requirements
* `__VA_OPT__` (tested currently on C++20 only)

## todo

* Benchmarks