/**
 * @file ThrReqHandler.cpp
 * @brief See header
 * @author Divyang Patel <divyang.jp@gmail.com>
 * @version 1.0
 * @date 2013-03-25
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

#include "ThrReqHandler.h"

using namespace std;

ThrReqHandler::ThrReqHandler(ThreadPool* tp):m_tpool(tp),m_end(false)
{
}

ThrReqHandler::~ThrReqHandler()
{
}

void ThrReqHandler::Run()
{

	while(!m_end)
	{
		m_tpool->appendIdle(this);

		m_work_cond.Lock();	

		while(!m_req && !m_end)
			m_work_cond.Wait();

		m_req->doWork();
		m_req = NULL;

		m_work_cond.Unlock();
	}
}

void ThrReqHandler::set_data(Request* req)
{
	m_req = req;
	m_work_cond.Signal();
}

void ThrReqHandler::Quit()
{
	m_end = true;
	Cancel();
}
