/*
 * Copyright 2024, Adelsbach UG (haftungsbeschraenkt)
 * Copyright 2014-2024, Jan Adelsbach <jan@jadelsbach.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software and associated documentation files (the “Software”), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS 
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
 * IN THE SOFTWARE.
 */

#ifndef THREADS_H
#define THREADS_H

#include <pthread.h>
#include <time.h>

#define ONCE_FLAG_INIT      PTHREAD_ONCE_INIT
#define TSS_DTOR_ITERATIONS PTHREAD_DESTRUCTOR_ITERATIONS
#define _Thread_local __thread

typedef void (*tss_dtor_t)(void*);
typedef int (*thrd_start_t)(void*);

enum mtx_type {
  mtx_plain     = 0,
  mtx_try       = 1,
  mtx_timed     = 2,
  mtx_recursive = 4
};

enum thrd_status {
  thrd_success = 0,
  thrd_timeout = 1,
  thrd_error   = 2,
  thrd_busy    = 3,
  thrd_nomem   = 4
}; 

typedef pthread_cond_t  cnd_t;
typedef pthread_t       thrd_t;
typedef pthread_key_t   tss_t;
typedef pthread_mutex_t mtx_t;
typedef pthread_once_t  once_flag;

int    mtx_init(mtx_t *mtx, int type);
void   mtx_destroy(mtx_t *mtx);
int    mtx_lock(mtx_t *mtx);
int    mtx_timedlock(mtx_t *mtx, const struct timespec *ts);
int    mtx_trylock(mtx_t *mtx);
int    mtx_unlock(mtx_t *mtx);

void   call_once(once_flag *flag, void (*fn)());

int    cnd_init(cnd_t *cnd);
void   cnd_destroy(cnd_t *cnd);
int    cnd_broadcast(cnd_t *cnd);
int    cnd_signal(cnd_t *cnd);
int    cnd_wait(cnd_t *cnd, mtx_t *mtx);
int    cnd_timedwait(cnd_t *cnd, mtx_t *mtx, const struct timespec *ts);

int    tss_create(tss_t *key, tss_dtor_t dtor);
void   tss_delete(tss_t key);
void  *tss_get(tss_t key);
int    tss_set(tss_t key, void *val);

int    thrd_create(thrd_t *thr, thrd_start_t fn, void *arg);
void   thrd_exit(int code);
thrd_t thrd_current(void);
int    thrd_detach(thrd_t thr);
int    thrd_join(thrd_t thr, int *code);
int    thrd_equal(thrd_t a, thrd_t b);
void   thrd_sleep(const struct timespec *ts);
void   thrd_yield(void);


#endif 
