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

#include <pthread.h>
#include "threads.h"
#include "threadse.h"

int rwmtx_init(rwmtx_t *mtx, int type) {
  pthread_rwlockattr_t attr;
  int psh;
  
  if(!mtx) {
    return thrd_error;
  }
  else if((type != rwmtx_private) && (type != rwmtx_shared)) {
    return thrd_error;
  }
  
  psh = (type == rwmtx_private) ? PTHREAD_PROCESS_PRIVATE
    : PTHREAD_PROCESS_SHARED;
  
  if(pthread_rwlockattr_init(&attr)) {
    return thrd_error;
  }
  else if(pthread_rwlockattr_setpshared(&attr, psh)) {
    pthread_rwlockattr_destroy(&attr);    
    return thrd_error;
  }
  
  if(pthread_rwlock_init(mtx, &attr)) {
    pthread_rwlockattr_destroy(&attr);    
    return thrd_error;
  }

  pthread_rwlockattr_destroy(&attr);
  
  return thrd_success;
}
