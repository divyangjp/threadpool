/**
 * @file Thread.cpp
 * @brief See header
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

#include "Thread.h"

Mutex Thread::m_MutexCom;
unsigned int Thread::m_siTIdCount = 0;

Thread::Thread()
{
    m_siTIdCount++;
    m_iThreadId = m_siTIdCount;
    pthread_attr_init(&m_thread_attr);
}

Thread::~Thread()
{
}

void Thread::Start()
{
  m_running = true;
  pthread_create(&m_thread, &m_thread_attr, stThreadRoutine, this);
}

void Thread::Join()
{
  pthread_join(m_thread, NULL);
}

void Thread::Detach()
{
  pthread_detach(m_thread);
}

void Thread::Cancel()
{
  pthread_cancel(m_thread);
}

pthread_t Thread::Self()
{
  return pthread_self();
}

void Thread::Quit()
{
	m_running = false;
}

bool Thread::IsRunning()
{
    return m_running;
}

void* Thread::stThreadRoutine(void* arg)
{
  ((Thread*)arg)->Run();
  return NULL;
}
