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

#ifndef THREADS_EXT_H
#define THREADS_EXT_H
#include <pthread.h>

/* non-portable adelsbach extensions */

enum rwmtx_type {
  rwmtx_private = 1,
  rwmtx_shared  = 2
};

typedef pthread_rwlock_t rwmtx_t;

int  rwmtx_init(rwmtx_t *mtx, int type);
int  rwmtx_destroy(rwmtx_t *mtx);
int  rwmtx_rdlock(rwmtx_t *mtx);
int  rwmtx_wrlock(rwmtx_t *mtx);
int  rwmtx_tryrdlock(rwmtx_t *mtx);
int  rwmtx_trywrlock(rwmtx_t *mtx);
int  rwmtx_timedrdlock(rwmtx_t *mtx, const struct timespec *ts);
int  rwmtx_timedwrlock(rwmtx_t *mtx, const struct timespec *ts);
int  rwmtx_unlock(rwmtx_t *mtx);


enum smtx_type {
  smtx_private = 1,
  smtx_shared  = 2
};

typedef pthread_spinlock_t smtx_t;

int  smtx_init(smtx_t *mtx, int type);
int  smtx_destroy(smtx_t *mtx);
int  smtx_lock(smtx_t *mtx);
int  smtx_unlock(smtx_t *mtx);
int  smtx_trylock(smtx_t *mtx);

enum bar_type {
  bar_private = 1,
  bar_shared  = 2
};

typedef pthread_barrier_t bar_t;

int  bar_init(bar_t *barrier, int type, unsigned count);
int  bar_destroy(bar_t *barrier);
int  bar_wait(bar_t *barrier);

#endif
