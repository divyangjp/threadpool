/**
 * @file Thread_App.cpp
 * @brief Test application for ThreadPool
 * 		  This initiates RequestQ object and ThreadPool object with
 * 		  number of threads. Then adds Request objects into the queue
 * 		  which is handled by handler threads in ThreadPool
 * @author Divyang Patel <divyang.jp@gmail.com>
 * @version 1.0
 * @date 2013-05-30
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

#include <vector>
#include "Thread.h"
#include "Mutex.h"
#include "Request.h"
#include "RequestQ.h"
#include "ThreadPool.h"
#include "TCPRequest.h"

#define NUM_THREADS 5

//using namespace std;

int main()
{
	RequestQ<Request> req_q;
	ThreadPool t_pool(NUM_THREADS, &req_q);
	t_pool.Start();

	TCPRequest tcp_req(0, 1000, "First Request");
	for(int i=0; i<5; i++)
	{
		//sleep(1);
		tcp_req.setSocketDesc(i);
		req_q.pushBack(&tcp_req);
	}

	t_pool.Join();
  	return 0;
}
