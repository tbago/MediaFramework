//
//  ThreadMutex.h
//  Base
//
//  Created by tbago on 2021/1/8.
//  Copyright © 2021 tbago. All rights reserved.
//

#ifndef BASE_THREAD_MUTEX_H_
#define BASE_THREAD_MUTEX_H_

#include <stdint.h>
#include <pthread.h>

/**
 * Thread muxtex lock
 */
#ifndef INFINITE
    #define INFINITE    0xFFFFFFFF  // Infinite timeout
#endif

class ThreadMutex {
public:
    ThreadMutex();
    ~ThreadMutex();
    ThreadMutex(const ThreadMutex &threadMutex) = delete;
    ThreadMutex & operator=(const ThreadMutex &threadMutex) = delete;
public:
    /*
     * lock current thread
     * @param timeout in milliseconds
     */
    bool Lock(uint32_t timeout = INFINITE);
    bool Unlock();
private:
    pthread_mutex_t _mutex;
    pthread_mutexattr_t _mutexAttr;
};

#endif  // BASE_THREAD_MUTEX_H_

