/**
 * @file RequestQ.h
 * @brief Templated RequestQ class
 * 		  This holds incoming requests in a list
 * @author Divyang Patel <divyang.jp@gmail.com>
 * @version 1.0
 * @date 2013-05-17
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

#ifndef _REQUESTQ_H_
#define _REQUESTQ_H_

#include <iostream>
#include <list>
#include "Mutex.h"
#include "Condition.h"

using namespace std;

template <class T>
class RequestQ
{
	public:
		friend class ThreadPool;
		RequestQ(){}
		~RequestQ(){}
		void		pushBack(T*);
		T*		 	getReq();	
		bool		empty();

	private:
		std::list<T*>	m_q;
		Mutex			m_mutex;
		Condition		m_cond;

};

template <class T>
void RequestQ<T>::pushBack(T* req)
{
	//m_mutex.Lock();
	m_cond.Lock();
	m_q.push_back(req);
	m_cond.Signal();
	m_cond.Unlock();
	//m_mutex.Unlock();
}

template <class T>
T* RequestQ<T>::getReq()
{
	m_mutex.Lock();
	T* req = m_q.front();
	m_q.pop_front();
	m_mutex.Unlock();

	return req;
}

template <class T>
bool RequestQ<T>::empty()
{
	return m_q.empty();
}

#endif  // _REQUESTQ_H_


