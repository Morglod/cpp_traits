# Traits

Use rust-like traits without any struct modifications & templates!

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

Basic traits may be used as type-erased references. To store values, use shared_ptr version.

In example above, `Addable` type has constructor:

```cpp
template<typename T> Addable(T& t);
```

Which saves pointer to T and picks specific trait's implementation for type T.

"Trait" structure will hold pointer to initial object & pointer to implementation  
static cost will be: 1 pointer per method per type

### Performance

https://quick-bench.com/q/RRZUoW5AVvuqjyzKvL_O2B5gU0E

Method call:
* GCC 11.2 -O3   virtual call is 10% faster
* Clang 13 -O3   equal to virtual call
* MSVC 2022      +- same as virtual call

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
  using Self = Addable_impl_T<T>;
  void (*add)(void *self, int) = &Self::static_add;
  static void static_add(void *self, int _1) { return ((T *)self)->add(_1); };
};

struct Addable_impl {
  void (*add)(void *self, int);
};

struct Addable {
  void *self = nullptr;
  Addable() = delete;
  inline void add(int _1) { return _impl->add(_get_self(), _1); }

  template <typename T>
  Addable(T &t) : self(&t) {
    static Addable_impl_T<T> impl;
    _impl = (Addable_impl *)(void *)&impl;
  }

private:
  inline void *_get_self() { return self; }
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
#define TRAITS_SHARED_PTR // <--------------------- add shared_ptr
#include <memory>        // <---------------- or just simply include <memory> before traits
#include "traits.hpp"

struct Storage {
    char* _data;
    void print();
};

TRAIT_STRUCT(DataHandler,
    TRAIT_METHOD(void, print)
)

DataHandler_ptr take_data(DataHandler_ptr dh) { // <------ we use _ptr version here which stores shared_ptr as self
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

* `__VA_OPT__` (currently for C++20 only)

## todo

* Remove `__VA_OPT__`, than C++11 may be supported
* More benchmarks & tests
