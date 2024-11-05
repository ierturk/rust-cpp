#include <iostream>
#include <dlfcn.h>

typedef int (*add_func)(int, int);

int main() {
    // Load the shared library
    void* handle = dlopen("./target/release/librust_cpp_example.so", RTLD_LAZY);
    if (!handle) {
        std::cerr << "Unable to load library: " << dlerror() << std::endl;
        return 1;
    }

    // Get the function from the library
    add_func add = (add_func)dlsym(handle, "add");
    if (!add) {
        std::cerr << "Unable to find function: " << dlerror() << std::endl;
        dlclose(handle);
        return 1;
    }

    // Call the function
    int result = add(3, 4);
    std::cout << "Result of add(3, 4): " << result << std::endl;

    // Close the library
    dlclose(handle);
    return 0;
}