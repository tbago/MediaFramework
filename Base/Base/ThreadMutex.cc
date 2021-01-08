//
//  ThreadMutex.cc
//  Base
//
//  Created by tbago on 2021/1/8.
//  Copyright © 2021 tbago. All rights reserved.
//

#include "ThreadMutex.h"
#include <unistd.h>
#include <assert.h>

ThreadMutex::ThreadMutex()
{
    if (pthread_mutexattr_init(&_mutexAttr) != 0) {
//        LOG(FATAL)<<"pthread_mutexattr_init: ";
    }
    if (pthread_mutexattr_settype(&_mutexAttr, PTHREAD_MUTEX_RECURSIVE) != 0) {
        pthread_mutexattr_destroy(&_mutexAttr);
//        LOG(FATAL)<<"pthread_mutexattr_settype: ";
    }
    if (pthread_mutex_init(&_mutex, &_mutexAttr) != 0) {
        pthread_mutexattr_destroy(&_mutexAttr);
//        LOG(FATAL)<<"pthread_mutex_init: ";
    }
}

ThreadMutex::~ThreadMutex()
{
    pthread_mutexattr_destroy(&_mutexAttr);
    pthread_mutex_destroy(&_mutex);
}

bool ThreadMutex::Lock(uint32_t timeout /* = INFINITE */)
{
    int err;
    if (timeout == INFINITE) {
        err = pthread_mutex_lock(&_mutex);
        if(err == 0)
            return true;
        else {
//            debug_print("pthread_mutex_lock failed: %d\n", err);
            assert(false);
            return false;
        }
    } else {
        uint32_t ta = 0;
        while(ta <= timeout) {
            err = pthread_mutex_trylock(&_mutex);
            if (err == 0) {
               return true;
            }
            usleep(10000);
            ta += 10;
        }
        return false;
    }
}

bool ThreadMutex::Unlock()
{
    if(pthread_mutex_unlock(&_mutex) == 0)
        return true;
    else {
        assert(false);
        return false;
    }
}
