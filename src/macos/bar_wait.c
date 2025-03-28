/*
 * Copyright 2025, Adelsbach UG (haftungsbeschraenkt)
 * Copyright 2025, Jan Adelsbach <jan@jadelsbach.de>
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


#include <pthread.h>
#include <errno.h>

#include "threads.h"
#include "threadse.h"

int bar_wait(bar_t *barrier) {
  int rc;
  
  if(!barrier) {
    return thrd_error;
  }

  if((rc = pthread_mutex_lock(&barrier->mtx)) == EDEADLK) {
    return thrd_error;
  }

  --barrier->left;

  if(barrier->left <= 0) {
    barrier->left = barrier->count;
    ++barrier->serial;

    pthread_cond_broadcast(&barrier->cnd);
  }
  else {
    int s = barrier->serial;

    while(barrier->serial == s) {
      pthread_cond_wait(&barrier->cnd, &barrier->mtx);
    }
  }

  if(pthread_mutex_unlock(&barrier->mtx)) {
    return thrd_error;
  }

  return thrd_success;
}
