//My own implementation of a semaphoire since cpp doesnt allow it

#include <mutex>
#include <condition_variable>

class Semaphore {
private:
    int count;
    std::mutex mtx;
    std::condition_variable cv;
public:
    Semaphore(int cnt) : count(cnt) {}

    void acquire() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]{ return count > 0; });
        --count;
    }

    bool tryAcquire() {
        std::unique_lock<std::mutex> lock(mtx);
        if(count > 0) {
            --count;
            return true;
        }
        return false;
    }

    void release() {
        std::unique_lock<std::mutex> lock(mtx);
        ++count;
        cv.notify_one();
    }
};

class SemaphoreGuard {
private:
    Semaphore& sem;
public:
    SemaphoreGuard(Semaphore& semaphore) : sem(semaphore) { sem.acquire(); }
    ~SemaphoreGuard() { sem.release(); }
};