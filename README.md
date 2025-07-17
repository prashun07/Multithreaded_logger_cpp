# Concurreny in C++
- Concurrency refers to the ability to process multiple tasks or threads at the same time. It is used to improve the program's performance and response time.
- Added in C++11, concurrency features include threads, mutexes, condition variables, and atomic operations.

#### Concurrency vs Parallelism
- **Concurrency** is about dealing with multiple tasks at once, allowing them to make progress independently.
- **Parallelism** is about executing multiple tasks simultaneously, typically on multiple CPU cores.    
- Concurrency can be achieved on a single-core processor by interleaving the execution of tasks, while parallelism requires multiple cores to run tasks simultaneously.

![More](https://www.geeksforgeeks.org/operating-systems/difference-between-concurrency-and-parallelism/)

## Processes
- A process (also called task) is an instance of a running program. Each process has its own memory space and resources.
- A process is controlled by the operating system and can contain multiple threads.
- Processes are managed by the scheduler, which allocates CPU time to each process based on priority and other factors.


### process states
- A process can be in one of several states: running, waiting, ready, or terminated.
- The operating system manages the transitions between these states based on events such as I/O operations, scheduling, and resource availability.

- Ready : The process is ready to run but waiting for CPU time. Processes that are ready for execution by the CPU are stored in a queue managed by the OS.

- Running : The process is currently being executed by the CPU.

- Waiting : The process is waiting for some event to occur (e.g., I/O completion).

- Terminated : The process has finished execution and is no longer active.The underlying program is no longer executing, but the process remains in the process table as a “zombie process”. When it is finally removed from the process table, its lifetime ends.

- Ready suspended : A process that was initially in ready state but has been swapped out of main memory and placed onto external storage is said to be in suspend ready state. The process will transition back to ready state whenever it is moved to main memory again.

- Blocked suspended : A process that is blocked may also be swapped out of main memory.

## Threads
- A thread is a lightweight process that can run concurrently with other threads.
- Threads share the same memory space, which allows them to communicate and synchronize with each other.
- A thread represents a concurrent execution path within a process, and multiple threads can run in parallel on multi-core processors.
- each process has its own address space, while a thread does not require a new address space to be created. All the threads in a process can access its shared memory.
- Threads also share other OS dependent resources such as processors, files, and network connections.
- Threads can run concurrently, be paused, and resumed by the operating system.

![Thread Diagram](https://miro.medium.com/v2/resize:fit:720/format:webp/1*_aT_WRVUX_1elnVDDpMFPw.png)

### Thread States
- A thread can be in one of several states: new , runnable, blocked, or terminated.
- The operating system manages the transitions between these states based on events such as I/O operations, scheduling, and resource availability.

- New : The thread is created but not yet started. It is in the new state until the `start()` method is called.
- Runnable : The thread is ready to run and waiting for CPU time. It can be in the runnable state even if it is not currently executing.
- Blocked : The thread is waiting for a resource (e.g., a lock or I/O operation) and cannot continue until the resource becomes available.
- Terminated : The thread has finished execution and is no longer active. Once a thread has completed its execution, it cannot be restarted.


![Thread State Diagram](https://miro.medium.com/v2/resize:fit:720/format:webp/1*bKUe5bJZtzV6bqq1ZcDLqA.png)

```c++
#include <iostream>
#include <thread> // Include the thread library

void threadFunction() {
    std::cout << "Hello from thread!" << std::endl;
}
int main() {
    std::thread t(threadFunction); // Create a thread that runs threadFunction
    t.join(); // Wait for the thread to finish
    return 0;
}
```

## Synchronization
- Synchronization is the coordination of concurrent threads to ensure that they operate correctly and efficiently and avoid data corruption.
- It is essential when multiple threads access shared resources or data structures
- Synchronization mechanisms include mutexes, condition variables, and semaphores.

## Mutexes
- A mutex (short for mutual exclusion) is a synchronization primitive that allows only one thread to
access a shared resource at a time.
- Mutexes are used to protect shared data from concurrent access, ensuring that only one thread can modify the data at a time.
- When a thread locks a mutex, other threads that try to lock the same mutex will be blocked until the mutex is unlocked.
- Mutexes can be implemented using various mechanisms, such as spinlocks or operating system-level locks.
- In C++, the `std::mutex` class provides a simple and efficient way to create and manage mutexes.

- Race conditions occur when multiple threads access shared data concurrently, leading to unpredictable results.


```c++
#include <iostream>
#include <thread>
#include <mutex>
std::mutex mtx; // Create a mutex
void threadFunction() {
    mtx.lock(); // Lock the mutex 
    // Critical section: only one thread can execute this code at a time
    std::cout << "Thread is executing critical section." << std::endl;
    mtx.unlock(); // Unlock the mutex
}
int main() {
    std::thread t1(threadFunction); // Create a thread
    std::thread t2(threadFunction); // Create another thread
    t1.join(); // Wait for the first thread to finish
    t2.join(); // Wait for the second thread to finish
    return 0;

    /*
    The join() function is used to ensure that a thread has completed its execution before the program exits. If join() is not called before the main function finishes, and the thread is still executing, then the program will terminate abruptly */

}

```

### std::lock_guard
- manually locking and unlocking a mutex can lead to errors, such as forgetting to unlock it or unlocking it too early.
- To avoid these issues, C++ provides the `std::lock_guard` class, which is a RAII (Resource Acquisition Is Initialization) wrapper for mutexes.
- `std::lock_guard` automatically locks the mutex when it is created and unlocks it when it goes out of scope, ensuring that the mutex is always properly released.
```c++
#include <iostream>
#include <thread>
#include <mutex>
std::mutex mtx; // Create a mutex
void threadFunction() {
    std::lock_guard<std::mutex> lock(mtx); // Lock the mutex using lock_guard
    // Critical section: only one thread can execute this code at a time
    std::cout << "Thread is executing critical section." << std::endl;
    // The mutex will be automatically unlocked when lock goes out of scope
}
int main() {
    std::thread t1(threadFunction); // Create a thread
    std::thread t2(threadFunction); // Create another thread
    t1.join(); // Wait for the first thread to finish
    t2.join(); // Wait for the second thread to finish
    return 0;
}
``` 

- The `std::lock_guard` constructor locks the mutex, and its destructor unlocks it when the `lock_guard` object goes out of scope.
- This pattern helps prevent common threading bugs such as forgetting to unlock a mutex or accidentally unlocking it too early. It also ensures that the mutex is released even if an exception is thrown, making your code safer and easier to maintain.

### Deadlocks
- A deadlock occurs when two or more threads are blocked forever, each waiting for the other to release a resource or mutex.
- Deadlocks can occur when multiple threads try to lock multiple mutexes in different orders.
- To avoid deadlocks, you can use techniques such as:
  - Locking mutexes in a consistent order.
  - Using `std::lock` to lock multiple mutexes simultaneously.
  - Using timeouts or try-lock mechanisms to avoid waiting indefinitely.


```c++
// Example of a deadlock situation
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx1, mtx2;

void task1() {
    std::lock_guard<std::mutex> lock1(mtx1);    
    std::this_thread::sleep_for(std::chrono::milliseconds(1));  // Simulate work
    std::lock_guard<std::mutex> lock2(mtx2);
    std::cout << "Task 1 complete." << std::endl;
}

void task2() {
    std::lock_guard<std::mutex> lock2(mtx2);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));  // Simulate work
    std::lock_guard<std::mutex> lock1(mtx1);
    std::cout << "Task 2 complete." << std::endl;
}

int main() {
    std::thread t1(task1);
    std::thread t2(task2);

    t1.join();
    t2.join();

    return 0;
}
```
To avoid deadlocks in the above example, you can ensure that both tasks lock the mutexes in the same order:

```c++
void task1() {
    std::lock_guard<std::mutex> lock1(mtx1);
    std::lock_guard<std::mutex> lock2(mtx2);
    std::cout << "Task 1 complete." << std::endl;
}  
void task2() {
    std::lock_guard<std::mutex> lock1(mtx1);
    std::lock_guard<std::mutex> lock2(mtx2);
    std::cout << "Task 2 complete." << std::endl;
}
```
This way, both tasks will always lock `mtx1` before `mtx2`, preventing a deadlock situation.

### Shared Mutexes
- A shared mutex allows multiple threads to read shared data concurrently while ensuring exclusive access for writing.
- C++ provides `std::shared_mutex` for this purpose, which allows multiple readers or one writer at a time.
- This is useful for scenarios where read operations are more frequent than write operations, as it improves performance by allowing concurrent reads.

### Types of locks in shared mutexes
- **Shared Lock**: Allows multiple threads to read shared data concurrently. Multiple threads can hold a shared lock simultaneously.
- **Exclusive Lock**: Allows only one thread to write shared data at a time. When a thread holds an exclusive lock, no other thread can hold a shared or exclusive lock on the same mutex.

```c++
#include <iostream>
#include <thread>
#include <shared_mutex>     
std::shared_mutex sharedMtx; // Create a shared mutex
void readFunction() {
    std::shared_lock<std::shared_mutex> lock(sharedMtx); // Acquire a shared lock
    // Critical section: multiple threads can read concurrently
    std::cout << "Reading shared data." << std::endl;
}
void writeFunction() {
    std::unique_lock<std::shared_mutex> lock(sharedMtx); // Acquire an exclusive lock
    // Critical section: only one thread can write at a time
    std::cout << "Writing shared data." << std::endl;
}
int main() {
    std::thread t1(readFunction); // Create a thread for reading
    std::thread t2(readFunction); // Create another thread for reading
    std::thread t3(writeFunction); // Create a thread for writing
    t1.join(); // Wait for the first thread to finish
    t2.join(); // Wait for the second thread to finish
    t3.join(); // Wait for the third thread to finish
    return 0;
}
``` 

## Condition Variables
- Condition variables are synchronization primitives that allow threads to wait for a specific condition to be met before proceeding.
- They are used in conjunction with mutexes to synchronize access to shared data.
- Condition variables allow threads to block until a certain condition is met, which helps avoid busy-waiting and improves efficiency.
- C++ provides `std::condition_variable` for this purpose.
- it is used to notify one or more threads that a condition has changed, allowing them to wake up and check the condition.


```c++
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> buffer;
const unsigned int MAX_SIZE = 5;

void producer() {
    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return buffer.size() < MAX_SIZE; }); // Wait if buffer is full
        buffer.push(i);
        std::cout << "Produced: " << i << std::endl;
        cv.notify_all(); // Notify consumers
    }
}

void consumer() {
    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !buffer.empty(); }); // Wait if buffer is empty
        int item = buffer.front();
        buffer.pop();
        std::cout << "Consumed: " << item << std::endl;
        cv.notify_all(); // Notify producers
    }
}

int main() {
    std::thread prod(producer);
    std::thread cons(consumer);
    prod.join();
    cons.join();
    return 0;
}
```
