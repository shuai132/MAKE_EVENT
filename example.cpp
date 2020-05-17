#include <string>
#include <cassert>

//#define NO_FUNCTIONAL
#include "MakeEvent.hpp"

class SimpleTest {
    MAKE_EVENT(Destroy, int, std::string);
    ~SimpleTest() {
        onDestroy(123, "SimpleTest");
    }
};

static void simple_test() {
    SimpleTest test;
    test.setDestroyCb([](int arg1, std::string arg2){
        printf("destroy callback: %d, %s\n", arg1, arg2.c_str());
    });
}

class FullTest {
    MAKE_EVENT_SET(EventSetNoArg);
    MAKE_EVENT_ADD(EventAddNoArg);

    MAKE_EVENT_SET(EventSetOneArg, int);
    MAKE_EVENT_ADD(EventAddOneArg, int);

    MAKE_EVENT_SET(EventSetMoreArg, int, std::string);
    MAKE_EVENT_ADD(EventAddMoreArg, int, std::string);

    MAKE_EVENT_ADD(TestRemove, std::string);
};

static void full_test() {
    FullTest test;
    {
        test.setEventSetNoArgCb([]() {
            printf("setEventSetNoArgCb\n");
        });
        test.onEventSetNoArg();

        test.addEventAddNoArgCb([]() {
            printf("addEventAddNoArgCb\n");
        });
        test.onEventAddNoArg();
    }
    {
        test.setEventSetOneArgCb([](int arg) {
            printf("setEventSetOneArgCb: %d\n", arg);
        });
        test.onEventSetOneArg(1);

        test.addEventAddOneArgCb([](int arg) {
            printf("addEventAddOneArgCb: %d\n", arg);
        });
        test.onEventAddOneArg(1);
    }
    {
        test.setEventSetMoreArgCb([](int arg1, std::string arg2){
            printf("setEventSetMoreArgCb: %d, %s\n", arg1, arg2.c_str());
        });
        test.onEventSetMoreArg(1, "hello");

        test.addEventAddMoreArgCb([](int arg1, std::string arg2) {
            printf("addEventAddMoreArgCb: %d, %s\n", arg1, arg2.c_str());
        });
        test.onEventAddMoreArg(1, "hello");
    }

    {
        test.removeAllTestRemoveCbs(); // only for test compile
        assert(test.removeTestRemoveCbById(1) == 0);

        auto id = test.addTestRemoveCb([](std::string arg) {
            printf("addTestRemoveCb: %s\n", arg.c_str());
        });
        assert(id == 1); // start from 1
        id = test.removeTestRemoveCbById(id);
        assert(id == 1); // return removed id
        test.onTestRemove("should not output!");
    }
}

int main() {
    simple_test();
    full_test();
    return 0;
}
