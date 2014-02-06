/**
 * @file TCPRequest.cpp
 * @brief See header
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

#include "TCPRequest.h"

using namespace std;

void TCPRequest::doWork()
{
	cout << "Client Socket Descriptor = " << m_sock_desc << endl;

    //Need to ensure that socket is closed after work is done
	close(m_sock_desc);
}

int TCPRequest::getSocketDesc()
{
	return m_sock_desc;
}

void TCPRequest::setSocketDesc(int ai_iSockId)
{
	m_sock_desc = ai_iSockId;
}
