
// define TRAITS_SHARED_PTR or include <memory> before <traits.hpp>
#define TRAITS_SHARED_PTR
#include "../traits.hpp"

#include <stdio.h>
#include <memory>

namespace {

    struct Storage : std::enable_shared_from_this<Storage> {
        char* _data;
        char* data();

        inline std::shared_ptr<void> get_ptr() { return shared_from_this(); }

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

    DataHandler_ptr take_data(DataHandler_ptr dh) {
        return dh;
    }

}

int main() {
    DataHandler_ptr data_trait;
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
