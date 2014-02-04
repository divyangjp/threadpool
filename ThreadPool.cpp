/**
 * @file ThreadPool.cpp
 * @brief See header
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


#include "ThreadPool.h"

using namespace std;

ThreadPool::ThreadPool(int num_threads, RequestQ<Request>* req):m_req_q(req)
{
    //Assign thread ID.
    //For ThreadPool, we will add 1000 to thread ID, so that we can differentiate
    //it from request handler (worker) threads.
    m_iThreadId = m_siTIdCount + 1000;

	for(int i=0; i<num_threads; ++i)
	{
		ThrReqHandler *thr = new ThrReqHandler(this);
		thr->Start();
		//appendIdle(thr);
	}
}

ThreadPool::~ThreadPool()
{
    //cout << "m_idle_thrv.size() " << m_idle_thrv.size() << endl;
	for(int i=(m_idle_thrv.size()-1); i>=0; --i)
	{
		m_idle_thrv[i]->Quit();
		delete m_idle_thrv[i];
		m_idle_thrv.pop_back();
	}
}

void ThreadPool::appendIdle(ThrReqHandler* thr)
{
	m_idle_thrv.push_back(thr);
	m_idle_cond.Signal();
}

/*
void ThreadPool::appendBusy(ThrReqHandler* thr)
{
	m_busy_thrv.push_back(thr);
}
*/

ThrReqHandler* ThreadPool::getIdleThread()
{
	m_idle_cond.Lock();

	while(m_idle_thrv.empty())
		m_idle_cond.Wait();

	m_idle_cond.Unlock();

	if(!m_idle_thrv.empty())
	{
		ThrReqHandler* thr = m_idle_thrv.back();
		m_idle_thrv.pop_back();
		return thr;
	}
}

void ThreadPool::Run()
{
	int nResult = 0;
	int nContinue = 1;
	while(nContinue)
	{
		m_req_q->m_cond.Lock();

		if(m_req_q->empty())
		{
			//m_req_q->m_cond.Wait();
			//Instead of indifinite wait, ThreadPool now wait for SECONDS_TO_WAIT
			//If in that timeframe, there is no request in request queue,
			//ThreadPool will exit.
			nResult = m_req_q->m_cond.TimedWait(SECONDS_TO_WAIT);
		}
		//cout << "nResult = " << nResult << endl;

		if((nResult == 0) && !m_req_q->empty())
		{
			Request* req = m_req_q->getReq();
			ThrReqHandler* thr = getIdleThread();

			thr->set_data(req);
		}
		else if(nResult == ETIMEDOUT || nResult)
		{
			//Break while loop
			cout << "Thread pool wait timed out after " << SECONDS_TO_WAIT << " secs" << endl;
			nContinue = 0;
		}

		m_req_q->m_cond.Unlock();
	}
}
