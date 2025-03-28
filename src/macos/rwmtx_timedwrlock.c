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

#include <time.h>
#include <errno.h>

#include <pthread.h>

#include "threads.h"
#include "threadse.h"

int rwmtx_timedwrlock(rwmtx_t *mtx, const struct timespec *ts) {
  int rc;
  struct timespec c;
  
  if(!mtx || !ts) {
    return thrd_error;
  }

  while((rc = pthread_rwlock_trywrlock(mtx)) == EBUSY) {
    struct timespec d;

    timespec_get(&c, TIME_UTC);

    if((c.tv_sec >= ts->tv_sec) &&
       (c.tv_nsec >= ts->tv_nsec)) {
      rc = ETIMEDOUT;
      break;
    }

    d.tv_sec = ts->tv_sec - c.tv_sec;
    d.tv_nsec = ts->tv_nsec - c.tv_nsec;

    /* Handle over and underflow */
    if(d.tv_nsec < 0) {
      --d.tv_sec;
      d.tv_nsec = 1000000000;
    }
    else if(d.tv_nsec >= 1000000000) {
      ++d.tv_sec;
      d.tv_nsec = 0;
    }

    nanosleep(&d, NULL);
  }
  
  if(rc == 0) {
    return thrd_success;
  }
  else if((rc == ETIMEDOUT) || (rc == EBUSY)) {
    return thrd_timeout;
  }
  
  return thrd_error;
}
