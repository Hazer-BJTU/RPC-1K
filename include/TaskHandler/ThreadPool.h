#pragma once

#include "Log.h"
#include <atomic>
#include <random>
#include <memory>
#include <queue>
#include <mutex>
#include <thread>
#include <algorithm>
#include <condition_variable>

namespace rpc1k {

static constexpr int DEFAULT_RANDOM_SEED = 42;
static constexpr int UDIST_LOWER_BOUND = 0;
static constexpr int UDIST_UPPER_BOUND = 255;

class Task {
private:
    static thread_local std::mt19937 gen;
    static thread_local std::uniform_int_distribution<int> udist;
    int task_idx;
public:
    Task();
    ~Task();
    Task(const Task&) = delete;
    Task& operator = (const Task&) = delete;
    virtual void run();
    int get_task_idx() const;
};

static constexpr int MAX_QUEUE_LENGTH = 256;
static constexpr int DEFAULT_QUEUE_NUM = 4;

class ThreadPool {
private:
    static bool created;
    static int total_workers;
    static int num_groups;
    static int max_tasks;
    class SubGroup {
    public:
        std::atomic<bool> end_flag;                //Exit flag for all workers.
        std::atomic<int> num_active_threads;       //Number of active workers.
        std::queue<std::shared_ptr<Task>> task_q;  //Task queue, protected by q_lock.
        std::mutex q_lock;                         //Mutually exclusive lock.
        std::condition_variable cv_not_empty;      //Condition variable for Producer-Consumer model.
        std::condition_variable cv_not_full;       //Condition variable for Producer-Consumer model.
        std::condition_variable cv_all_done;       //Condition variable for task synchronization.
        SubGroup();
        ~SubGroup();
        SubGroup(const SubGroup&) = delete;
        SubGroup& operator = (const SubGroup&) = delete;
        bool quit();
        void wait();
    };
    std::vector<std::unique_ptr<SubGroup>> groups;
    std::vector<std::thread> workers;
    ThreadPool();
    ~ThreadPool();
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator = (const ThreadPool&) = delete;
public:
    static bool set_global_taskHandler_config(int total_workers, int num_groups, int max_tasks);
    static ThreadPool& get_global_taskHandler();
    void enqueue(const std::shared_ptr<Task>& task_ptr);
    void wait_for_all_subgroups();
};

}
