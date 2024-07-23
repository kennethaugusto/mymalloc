#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mymalloc.h"

#define NUM_RUNS 50

static int task1() {
    for (int i = 0; i < 120; i++) {
        void *ptr = mymalloc(1, __FILE__, __LINE__);
        myfree(ptr, __FILE__, __LINE__);
    }
    return 0;
}

static int task2() {
    void *ptr[120];
    for (int i = 0; i < 120; i++) {
        ptr[i] = malloc(1);
    }
    for (int j = 0; j < 120; j++) {
        free(ptr[j]);
    }
    return 0;
}

static int task3() {
    void *ptr[120];
    int alloc_count = 0;
    int index = 0;

    while (alloc_count < 120) {
        int choice = rand() % 2;
        if (choice == 0) {
            ptr[index] = mymalloc(1, __FILE__, __LINE__);
            if (ptr[index] != NULL) {\
                index++;
                alloc_count++;
            }
        }
        else if (index > 0) {
            index--;
            myfree(ptr[index], __FILE__, __LINE__);
            ptr[index] = NULL;
        }
    }
    for (int i = 0; i < index; i++) {
        if (ptr[i] != NULL) {
            myfree(ptr[i], __FILE__, __LINE__);
        }
    }
    return 0;
}

static int task4() {
    void *ptrs[120] = {NULL};
    int allocated = 0;
    for (int i = 0; i < 240; i++) {
        int operation = rand() % 2;
        if (operation == 0 && allocated < 120) {
            size_t size = (size_t)(rand() % 64) + 1;
            ptrs[allocated++] = mymalloc(size, __FILE__, __LINE__);
        } else if (allocated > 0) {
            myfree(ptrs[--allocated], __FILE__, __LINE__);
            ptrs[allocated] = NULL;
        }
    }
    while (allocated > 0) {
        myfree(ptrs[--allocated], __FILE__, __LINE__);
        ptrs[allocated] = NULL;
    }
    return 0;
}


static int task5() {
    void *ptrs[300] = {NULL};
    int i = 0;
    for (; i < 300; i++) {
        ptrs[i] = mymalloc(1, __FILE__, __LINE__);
        if (ptrs[i] == NULL) {
            return -1;
        }
    }
    for (int j = 0; j < i; j++) {
        if (ptrs[j] != NULL) {
            myfree(ptrs[j], __FILE__, __LINE__);
        }
    }
    return 0;
}

int main(void) {
    struct timeval begin, end;
    double total_time_task1 = 0.0, total_time_task2 = 0.0, total_time_task3 = 0.0, total_time_task4 = 0.0, total_time_task5 = 0.0;

    for (int i = 0; i < NUM_RUNS; ++i) {

        // task 1
        gettimeofday(&begin, NULL);
        if (task1() < 0) {
            fprintf(stderr, "Test case 1 FAILED\n");
            return 1;
        }
        gettimeofday(&end, NULL);
        total_time_task1 += (end.tv_sec - begin.tv_sec) * 1000.0;
        total_time_task1 += (end.tv_usec - begin.tv_usec) / 1000.0;

        
        // task 2
        gettimeofday(&begin, NULL);
        if (task2() < 0) {
            fprintf(stderr, "Test case 2 FAILED\n");
            return 1;
        }
        gettimeofday(&end, NULL);
        total_time_task2 += (end.tv_sec - begin.tv_sec) * 1000.0;
        total_time_task2 += (end.tv_usec - begin.tv_usec) / 1000.0;

        // Task 3
        gettimeofday(&begin, NULL);
        if (task3() < 0) {
            fprintf(stderr, "Test case 3 FAILED\n");
            return 1;
        }
        gettimeofday(&end, NULL);
        total_time_task3 += (end.tv_sec - begin.tv_sec) * 1000.0;
        total_time_task3 += (end.tv_usec - begin.tv_usec) / 1000.0;

        
        // Task 4
        gettimeofday(&begin, NULL);
        if (task4() < 0) {
            fprintf(stderr, "Test case 4 FAILED\n");
            return 1;
        }
        gettimeofday(&end, NULL);
        total_time_task4 += (end.tv_sec - begin.tv_sec) * 1000.0;
        total_time_task4 += (end.tv_usec - begin.tv_usec) / 1000.0;
        
        
        // Task 5 (testCase_E)
        gettimeofday(&begin, NULL);
        if (task5() < 0) {
            fprintf(stderr, "Test case E FAILED\n");
            return 1;
        }
        gettimeofday(&end, NULL);
        total_time_task5 += (end.tv_sec - begin.tv_sec) * 1000.0;
        total_time_task5 += (end.tv_usec - begin.tv_usec) / 1000.0;
    }

    double avg_time_task1 = total_time_task1 / NUM_RUNS;
    double avg_time_task2 = total_time_task2 / NUM_RUNS;
    double avg_time_task3 = total_time_task3 / NUM_RUNS;
    double avg_time_task4 = total_time_task4 / NUM_RUNS;
    double avg_time_task5 = total_time_task5 / NUM_RUNS;

    printf("Average time to execute task 1: %.6f ms\n", avg_time_task1);
    printf("Average time to execute task 2: %.6f ms\n", avg_time_task2);
    printf("Average time to execute task 3: %.6f ms\n", avg_time_task3);
    printf("Average time to execute task 4: %.6f ms\n", avg_time_task4);
    printf("Average time to execute task 5: %.6f ms\n", avg_time_task5);

    return 0;
}