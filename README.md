# Producer-Consumer Problem in Modern C++

This project is a simple implementation of the classic **Producer-Consumer problem** using modern C++ (`std::thread`, `std::mutex`, `std::condition_variable`).

It demonstrates how multiple producer and consumer threads can safely interact with a shared bounded buffer using thread synchronization primitives.

This is a learning project to explore concurrency in C++. If you're preparing for systems programming, embedded development, or just want to improve your understanding of multithreading, this example is a great place to start.



## Concepts Covered

- Multithreading with `std::thread`
- Mutexes with `std::mutex` and `std::unique_lock`
- Condition variables for thread coordination
- Safe access to a shared queue (`std::queue`)
- Simulating delays with `std::this_thread::sleep_for`
- Classic bounded buffer problem (size-limited queue)



## Build and Run

### Requirements

- C++11 or higher
- A compiler like `g++` or `clang++`

### Compile

```bash
g++ -std=c++11 -pthread Producer_Consumer_Problem.cpp -o producer_consumer
```

### Run
```
./producer_consumer
```

### Example Output

Producer 1 produced: 0  
Consumer 2 consumed: 0  
Producer 2 produced: 0  
Consumer 1 consumed: 0  
...  
Final Buffer Size = 0

