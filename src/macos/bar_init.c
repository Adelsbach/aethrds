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

int bar_init(bar_t *barrier, int type, unsigned count) {
  int rc;
  pthread_condattr_t cndattr;
  pthread_mutexattr_t mtxattr;
  
  if(!barrier) {
    return thrd_error;
  }
  else if((type != bar_private) && (type != bar_shared)) {
    return thrd_error;
  }

  pthread_condattr_init(&cndattr);
  pthread_mutexattr_init(&mtxattr);

  if(type == bar_shared) {
    if(!pthread_condattr_setpshared(&cndattr, 1)) {
      return thrd_error;
    }
    else if(!pthread_mutexattr_setpshared(&mtxattr, 1)) {
      return thrd_error;
    }
  }

  if((rc = pthread_mutex_init(&barrier->mtx, &mtxattr))) {
    switch(rc) {
    case ENOMEM:
      return thrd_nomem;
    default:
      return thrd_error;
    }
  }
  else if((rc = pthread_cond_init(&barrier->cnd, &cndattr))) {
    pthread_mutex_destroy(&barrier->mtx);

    switch(rc) {
    case ENOMEM:
      return thrd_nomem;
    default:
      return thrd_error;
    }
  }

  barrier->count  = count;
  barrier->left   = count;
  barrier->serial = 0;
  
  return thrd_success;
}
