/**
 * @file Thread.h
 * @brief Abstract Thread base class. This is wrapper class
 * 		  for Pthreads. Specific thread handlers should derive from
 * 		  this class
 * @author Divyang Patel <divyang.jp@gmail.com>
 * @version 1.0
 * @date 2013-03-11
 *
 * Copyright (C)
 * 2013 - Divyang Patel <divyang.jp@gmail.com>
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies of the Software.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#ifndef _THREAD_H_
#define _THREAD_H_

#include <iostream>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include "Mutex.h"

using namespace std;

class Thread
{
  public:
    Thread();
    virtual 	~Thread();
    void  		Start();
    void  		Join();
    void  		Detach();
    void  		Cancel();
    pthread_t   Self();
	virtual void Quit();
	bool        IsRunning();

    static void * stThreadRoutine(void*);

    virtual void  Run() = 0;

  protected:
	static Mutex 	m_MutexCom;
	bool			m_running;
	unsigned int    m_iThreadId;
	static unsigned int m_siTIdCount;

  private:
    pthread_t       m_thread;
    pthread_attr_t  m_thread_attr;
};

#endif  //  _THREAD_H_

