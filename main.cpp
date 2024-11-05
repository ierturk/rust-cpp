#include <iostream>
#include <windows.h>
#include "bindings.h"

typedef int (__cdecl *add_func)(int, int);

int main() {
    // Load the shared library
    HMODULE handle = LoadLibrary(TEXT("rust_cpp_example.dll"));
    if (!handle) {
        std::cerr << "Unable to load library: " << GetLastError() << std::endl;
        return 1;
    }

    // Get the function from the library
    add_func add = (add_func)GetProcAddress(handle, "add");
    if (!add) {
        std::cerr << "Unable to find function: " << GetLastError() << std::endl;
        FreeLibrary(handle);
        return 1;
    }

    // Call the function
    int result = add(3, 4);
    std::cout << "Result of add(3, 4): " << result << std::endl;

    // Close the library
    FreeLibrary(handle);
    return 0;
}