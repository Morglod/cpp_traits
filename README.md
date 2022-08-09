# Traits

Use traits without initial struct modifications

"Trait" structure would hold pointer to initial object & pointer to implementation

static cost will be: 1 pointer per method per type

Requirements:
* `__VA_OPT__` (tested currently on C++20 only)

```cpp
struct Square {
    int counter = 0;
    void inc(int x) { counter += x; }
};

TRAIT_STRUCT(Addable,
    TRAIT_METHOD(void, inc, int)
)

void add_10(Addable x) {
    x.add(10);
}

int main() {
    Square s;
    add_10(s);
}
```

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
  inline void add(int _1) { return _impl->add(self, _1); }
  template <typename T> Addable(T &t) : self(&t) {
    static Addable_impl_T<T> impl;
    _impl = (Addable_impl *)(void *)&impl;
  }

private:
  Addable_impl *_impl;
};
```

</details>

---

## todo

* Detailed readme
* Benchmarks