/**
 * @file TCPRequest.h
 * @brief Specific request type TCPRequest class
 * 		  Derived from Request. This is used as an example
 * 		  of incoming request type to be processed by multithreading
 * 		  server
 * @author Divyang Patel <divyang.jp@gmail.com>
 * @version 1.0
 * @date 2013-05-18
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

#ifndef _TCPREQUEST_H_
#define _TCPREQUEST_H_

#include <iostream>
#include "Request.h"

class TCPRequest : public Request
{
	public:
		TCPRequest(int sock_desc, int req_id, std::string req_data):
			Request(req_id, req_data), m_sock_desc(sock_desc)
		{}
		~TCPRequest(){}
		void 	doWork();
		int		getSocketDesc();
		int		setSocketDesc(int ai_iSockId);

	private:
		int		m_sock_desc;
};

#endif  //_TCPREQUEST_H_

