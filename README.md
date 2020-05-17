# MAKE_EVENT

Observer-Mode(Event Callback) for C++11 Class

# Usage

1. 引入头文件
```
#include "MakeEvent.hpp"
```

2. 在类中使用声明事件  
MAKE_EVENT(事件名, 参数类型...);

3. 例子
```cpp
#include <string>
#include "MakeEvent.hpp"

class SimpleTest {
    MAKE_EVENT(Destroy, int, std::string);
    ~SimpleTest() {
        onDestroy(123, "SimpleTest");
    }
};

static void simple_test() {
    SimpleTest test;
    test.setDestroyCb([](int arg1, const std::string& arg2){
        printf("destroy callback: %d, %s\n", arg1, arg2.c_str());
    });
}
```

# Others

* 某些嵌入式平台的编译器对C++11支持不完善（不支持std::function）  
编译时定义`-DNO_FUNCTIONAL`，或引入头文件之前`#define NO_FUNCTIONAL`。
