#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

// Shared buffer between producers and consumers
std::queue<int> buffer;

// Mutex for synchronizing access to the buffer
std::mutex mtx;

// Condition variables for signaling buffer state
std::condition_variable not_full;
std::condition_variable not_empty;

// Maximum number of items the buffer can hold
const int buffer_size = 5;

// Producer thread function
void producer(int id){
    for(int i = 0; i < 10; i++){
        std::unique_lock<std::mutex> lock(mtx);  // Acquire lock before accessing buffer

        // Wait if buffer is full
        not_full.wait(lock, []{ return buffer.size() < buffer_size; });

        // Add item to buffer
        buffer.push(i);
        printf("Producer %d produced: %d\n", id, i);

        lock.unlock();  // Release lock before notifying
        not_empty.notify_all();  // Notify consumers that data is available

        // Simulate production delay
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// Consumer thread function
void consumer(int id){
    for(int i = 0; i < 10; i++){
        std::unique_lock<std::mutex> lock(mtx);  // Acquire lock before accessing buffer

        // Wait if buffer is empty
        not_empty.wait(lock, []{ return !buffer.empty(); });

        // Remove item from buffer
        int data = buffer.front();
        buffer.pop();
        printf("Consumer %d consumed: %d\n", id, data);

        lock.unlock();  // Release lock before notifying
        not_full.notify_all();  // Notify producers that space is available

        // Simulate consumption delay
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

int main(){
    // Create two producer threads and two consumer threads
    std::thread p1(producer, 1);
    std::thread p2(producer, 2);
    std::thread c1(consumer, 1);
    std::thread c2(consumer, 2);

    // Wait for all threads to complete
    p1.join();
    p2.join();
    c1.join();
    c2.join();

    // Print final buffer size (should be 0 if everything consumed)
    printf("Final Buffer Size = %ld\n", buffer.size());

    return 0;
}