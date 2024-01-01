
// DOC: bitwise operator shift one byte to the left so 00000001=1 becomes => 00000010=2 => 00000100=4
#define BIT(x) (1 << x)


// DOC: This is a macro that call the class method that is passed in as a parameter with perfect forwarding
#define PX_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#define PX_CORE_ASSERT(x, ...) { if(!(x)) { PX_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

