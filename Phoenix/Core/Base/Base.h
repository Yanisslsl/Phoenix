#pragma once

// DOC: bitwise operator shift one byte to the left so 00000001=1 becomes => 00000010=2 => 00000100=4
#define BIT(x) (1 << x)
#include <utility>
#include "Log/include/Log.h"


// A mediter [this](auto&&... args){ std::forward<decltype(args)>(args)...; }
//revient a 
// template<typename ...Args>
// void toto(Args&&... args)
// {
//     // DOC: This is a fold expression, it will expand the parameter pack and apply the operator to each element
//     (std::cout << ... << args) << std::endl;
//     std::forward<Args>(args)...;
// }

// DOC: This is a macro that call the class method that is passed in as a parameter with perfect forwarding, decltype(auto) => type auto a la compil
#define PX_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
#define PX_DELEGATE(fn) [this](auto&&... args) -> decltype(auto) { return fn(std::forward<decltype(args)>(args)...); }
#define PX_CORE_ASSERT(x, ...) { if(!(x)) { PX_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#include <memory>

namespace Phoenix
{
    template<typename T>
    using Ref = std::shared_ptr<T>;
    
    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}
