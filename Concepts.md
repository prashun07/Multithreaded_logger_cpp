# logger.h 

- use of mutex std::lock_guard<std::mutex> lock(mtx);
    This line creates a `std::lock_guard` object named `lock` that locks the mutex `mtx` for the duration of the current scope. `std::lock_guard` is a C++ RAII (Resource Acquisition Is Initialization) class template that provides a simple and exception-safe way to acquire and release a mutex.

    When this line is executed, the constructor of `std::lock_guard` immediately locks the provided mutex (`mtx`). The mutex remains locked for as long as the `lock` object exists. When the `lock` object goes out of scope (for example, when the function returns or the enclosing block ends), its destructor is called, which automatically unlocks the mutex.

    This pattern helps prevent common threading bugs such as forgetting to unlock a mutex or accidentally unlocking it too early. It also ensures that the mutex is released even if an exception is thrown, making your code safer and easier to maintain.