#include "../traits.hpp"
#include <stdio.h>
#include <memory>

struct Storage : std::enable_shared_from_this<Storage> {
    char* _data;
    char* data();

    std::shared_ptr<void> get_ptr() {
        return shared_from_this();
    }

    void print() {
        printf("Storage: %s\n", _data);
    }

    ~Storage() {
        printf("Storage deleted\n");
        delete [] _data;
        _data = nullptr;
    }
};

TRAIT_STRUCT(DataHandler,
    TRAIT_METHOD(void, print),
    TRAIT_METHOD(std::shared_ptr<void>, get_ptr)
)

std::shared_ptr<void> take_data(DataHandler dh) {
    return dh.get_ptr();
}

int main() {
    std::shared_ptr<void> ptr_to_storage;
    {
        auto obj = std::make_shared<Storage>();
        obj->_data = new char[] { "Hello world!" };
        ptr_to_storage = take_data(*(obj.get()));
    }
    ((Storage*)ptr_to_storage.get())->print();

    return 0;
}
