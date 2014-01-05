/**
 * @file ThreadPool.h
 * @brief Pool of threads. When request comes into RequestQ list,
 * 		  ThreadPool dispatches a free thread from the pool
 * 		  to handle the request. It maintains list of Idle threads
 * @author Divyang Patel <divyang.jp@gmail.com>
 * @version 1.0
 * @date 2013-03-23
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

#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include <iostream>
#include <vector>
#include "Thread.h"
#include "Condition.h"
#include "ThrReqHandler.h"
#include "Request.h"
#include "RequestQ.h"

class ThrReqHandler;

class ThreadPool : public Thread
{
	public:
		ThreadPool(int num_threads, RequestQ<Request>* req);
		~ThreadPool();

		void 		appendIdle(ThrReqHandler*);
		//void 		appendBusy(ThrReqHandler*);
		ThrReqHandler* 	getIdleThread();
		void		Run();

	private:
		std::vector<ThrReqHandler*>	m_busy_thrv;
		std::vector<ThrReqHandler*>	m_idle_thrv;
		Condition				m_idle_cond;
		RequestQ<Request>*		m_req_q;
};


#endif //_THREADPOOL_H_

