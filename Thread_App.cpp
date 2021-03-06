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
#include "Common.h"
#include "TCPServer.h"

int main()
{
	RequestQ<Request> req_q;
	ThreadPool t_pool(NUM_THREADS, &req_q);
	t_pool.Start();

	//Server
    TCPServer Server(LOCALHOST, DEFAULT_PORT, BACKLOG);
    cout << "Server has started listening on port : " << DEFAULT_PORT << endl;
    cout << "==============================================" << endl;

    //Get server socket fd
    int server_sockfd = Server.GetSockFD();

/*
	for(int i=0; i<5; i++)
	{
		//sleep(1);
		//This dynamically allocated memory will be freed by the thread handler
		//after completing the work for the request (in ThrReqHandler.cpp)
		TCPRequest* tcp_req = new TCPRequest(i, 1000+i, "Request");
		req_q.pushBack(tcp_req);
	}
*/
    //Server should keep accepting requests
    int req_count = 0;
    while(1)
    {
        int client_sockfd = Server.Accept(server_sockfd);

        cout << "New request no " << 1000+req_count << endl;
        TCPRequest* tcp_req = new TCPRequest(client_sockfd, 1000+req_count, "Request");
        req_q.pushBack(tcp_req);

        req_count++;
    }

	t_pool.Join();
  	return 0;
}
