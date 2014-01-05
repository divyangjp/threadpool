/**
 * @file ThrReqHandler.h
 * @brief Derived from Thread class. This handler class is a thread
 * 		  which handles the incoming requests
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

#ifndef _THRREQHANDLER_H_
#define _THRREQHANDLER_H_

#include <iostream>
#include "Thread.h"
#include "Mutex.h"
#include "Request.h"
#include "Condition.h"
#include "ThreadPool.h"

class ThreadPool;

class ThrReqHandler : public Thread
{
	public:
		ThrReqHandler(ThreadPool*);
		~ThrReqHandler();
		void Run();
		void set_data(Request*);
		void Quit();

	private:
		ThreadPool* m_tpool;
		Request*	m_req;
		Condition	m_work_cond;
		bool		m_end;
};


#endif	// _THRREQHANDLER_H_
