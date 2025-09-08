#include "_threadpool.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// 测试任务计数器
static int task_completed = 0;
static int task_created = 0;
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

/* 线程池中的线程，模拟处理业务 */
void process_task(void *arg)
{
    int task_id = *(int *)arg;
    printf("thread 0x%x working on task %d\n", (unsigned int)pthread_self(), task_id);
    
    // 模拟不同的处理时间
    int process_time = 1 + (task_id % 3);
    sleep(process_time);
    
    pthread_mutex_lock(&counter_mutex);
    task_completed++;
    pthread_mutex_unlock(&counter_mutex);
    
    printf("task %d completed in %d seconds\n", task_id, process_time);
}

/* 快速任务，测试高并发 */
void quick_task(void *arg)
{
    int task_id = *(int *)arg;
    printf("Quick task %d start\n", task_id);
	usleep(100*1000); // 100ms
    pthread_mutex_lock(&counter_mutex);
    task_completed++;
    pthread_mutex_unlock(&counter_mutex);
    printf("Quick task %d completed\n", task_id);
}

/* 长时间任务 */
void long_task(void *arg)
{
    int task_id = *(int *)arg;
    printf("Long task %d started\n", task_id);
    sleep(5);
    pthread_mutex_lock(&counter_mutex);
    task_completed++;
    pthread_mutex_unlock(&counter_mutex);
    printf("Long task %d completed\n", task_id);
}

// 测试1: 基本功能测试
void test_basic_functionality()
{
    printf("=== Test 1: Basic Functionality ===\n");
    task_completed = 0;
    task_created = 0;
    
    threadpool_t *thp = threadpool_create(1,5,5); // 最大5个线程
    printf("Thread pool created with max 5 threads\n");
    
    // 添加10个任务
    int tasks[10];
    for (int i = 0; i < 10; i++) {
        tasks[i] = i;
        threadpool_add_task(thp, process_task, (void*)&tasks[i]);
        task_created++;
        printf("Added task %d\n", i);
    }
    
    // 等待所有任务完成
    sleep(15);
    
    printf("Tasks created: %d, Tasks completed: %d\n", task_created, task_completed);
    threadpool_destroy(thp);
    printf("Test 1 completed\n\n");
}

// 测试2: 高并发测试
void test_high_concurrency()
{
    printf("=== Test 2: High Concurrency ===\n");
    task_completed = 0;
    task_created = 0;
    
    threadpool_t *thp = threadpool_create(1,10,20); // 最大10个线程
    
    // 添加50个快速任务
    int *tasks = malloc(50 * sizeof(int));
    for (int i = 0; i < 50; i++) {
        tasks[i] = i;
        threadpool_add_task(thp, quick_task, (void*)&tasks[i]);
        task_created++;
        if (i % 10 == 0 && i !=0) {
            printf("Added %d tasks...\n", i);
            usleep(50 * 1000); // 稍微延迟一下
        }
    }
    
    // 监控线程池状态
    for (int i = 0; i < 8; i++) {
		usleep(i * 15*1000);
        int busy = threadpool_busy_thread_num(thp);
        int total = threadpool_max_thread_num(thp);
        printf("Time %ds: %d/%d threads busy, %d tasks completed\n", 
               i+1, busy, total, task_completed);
    }
    
	sleep(5);
    printf("Total tasks created: %d, completed: %d\n", task_created, task_completed);
    free(tasks);
    threadpool_destroy(thp);
    printf("Test 2 completed\n\n");
}

// 测试3: 混合任务测试
void test_mixed_tasks()
{
    printf("=== Test 3: Mixed Tasks ===\n");
    task_completed = 0;
    task_created = 0;
    
    threadpool_t *thp = threadpool_create(1,8,16); // 最大8个线程
    
    // 混合添加快速任务和长时间任务
    int *tasks = malloc(25 * sizeof(int));
    
    // 先添加5个长时间任务
    for (int i = 0; i < 5; i++) {
        tasks[i] = i;
        threadpool_add_task(thp, long_task, (void*)&tasks[i]);
        task_created++;
        printf("Added long task %d\n", i);
    }
    
    sleep(2); // 让长时间任务先运行
    
    // 然后添加20个快速任务
    for (int i = 5; i < 25; i++) {
        tasks[i] = i;
        threadpool_add_task(thp, quick_task, (void*)&tasks[i]);
        task_created++;
        if (i % 5 == 0) {
            printf("Added %d quick tasks...\n", i-4);
        }
    }
    
    // 监控状态
    for (int i = 0; i < 15; i++) {
        usleep(300*1000);
        int busy = threadpool_busy_thread_num(thp);
        int total = threadpool_max_thread_num(thp);
        printf("Time %ds: %d/%d threads busy, %d tasks completed\n", 
               (i+1)*2, busy, total, task_completed);
    }
    
	sleep(5);
    printf("Mixed tasks - Created: %d, Completed: %d\n", task_created, task_completed);
    free(tasks);
    threadpool_destroy(thp);
    printf("Test 3 completed\n\n");
}

// 测试4: 边界条件测试
void test_edge_cases()
{
    printf("=== Test 4: Edge Cases ===\n");
    task_completed = 0;
    task_created = 0;
    
    // 测试小线程池
    threadpool_t *thp = threadpool_create(1,3,6); // 只有3个线程
    
    printf("Testing with small thread pool (3 threads)\n");
    
    int *tasks = malloc(15 * sizeof(int));
    for (int i = 0; i < 15; i++) {
        tasks[i] = i;
        threadpool_add_task(thp, process_task, (void*)&tasks[i]);
        task_created++;
        
        // 每添加几个任务后查看状态
        if (i % 3 == 0) {
            int busy = threadpool_busy_thread_num(thp);
            int total = threadpool_max_thread_num(thp);
            printf("After %d tasks: %d/%d threads busy\n", i+1, busy, total);
            sleep(1);
        }
    }
    
    sleep(20); // 等待所有任务完成
    
    printf("Edge case test - Created: %d, Completed: %d\n", task_created, task_completed);
    free(tasks);
    threadpool_destroy(thp);
    printf("Test 4 completed\n\n");
}

// 测试5: 性能测试
void test_performance()
{
    printf("=== Test 5: Performance Test ===\n");
    task_completed = 0;
    task_created = 0;
    
    threadpool_t *thp = threadpool_create(2,20,40); // 较大线程池
    
    clock_t start = clock();
    
    // 执行n个任务
	int n =100000;
    int *tasks = malloc(n* sizeof(int));
    for (int i = 0; i < n; i++) {
        tasks[i] = i;
        threadpool_add_task(thp, quick_task, (void*)&tasks[i]);
        task_created++;
    }
    
    // 等待所有任务完成
    while (task_completed < task_created) {
        usleep(200 * 1000);
        printf("Progress: %d/%d tasks completed\n", task_completed, task_created);
    }
    
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("Performance test completed in %.2f seconds\n", time_taken);
    printf("Throughput: %.2f tasks/second\n", task_created / time_taken);
    
    free(tasks);
    threadpool_destroy(thp);
    printf("Test 5 completed\n\n");
}

int main(void)
{
    printf("Starting Thread Pool Tests...\n\n");
    
    // 运行所有测试
    //test_basic_functionality();
    //test_high_concurrency();
    //test_mixed_tasks();
    //test_edge_cases();
    test_performance();
    
    printf("All tests completed successfully!\n");
    
    pthread_mutex_destroy(&counter_mutex);
    return 0;
}
