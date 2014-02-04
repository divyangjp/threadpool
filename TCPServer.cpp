/**
 * @file TCPServer.cpp
 * @brief See header
 * @author Divyang Patel <divyang.jp@gmail.com>
 * @version 1.0
 * @date 2014-01-28
 *
 * Copyright (C)
 * 2014 - Divyang Patel <divyang.jp@gmail.com>
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

#include "TCPServer.h"
#include <cstring>
#include <cstdlib>

using namespace std;

TCPServer::TCPServer(const char* ai_sIP,
                     const char* ai_sPort,
                     int ai_iBacklog)
{
    int gai_rval = GetAddrInfo(ai_sIP, ai_sPort, &m_stHints, &m_stResAddr);

    m_iSockFD = Socket(m_stResAddr);

    if(m_iSockFD == -1)
    {
        cout << "socket call failed. Exiting..." << endl;
        exit(1);
    }

    int bind_rval = Bind(m_iSockFD, m_stResAddr);
    int lisn_rval = Listen(m_iSockFD, ai_iBacklog); //Error checking?
    FreeAddrInfo(m_stResAddr);

}

TCPServer::~TCPServer()
{

}

int TCPServer::GetAddrInfo(const char* node,
                           const char* service,
                           struct addrinfo *hints,
                           struct addrinfo **res)
{
    int nResult=0;

    memset(hints, 0, sizeof(struct addrinfo));
    hints->ai_family = AF_UNSPEC;                   /* Allow IPv4 or IPv6 */
    hints->ai_socktype = SOCK_STREAM;               /* TCP stream sockets */
    hints->ai_flags = AI_PASSIVE;                   /* Fill in my IP for me. Though we've localhost IP, we'll just use this for now */

    nResult = getaddrinfo(NULL, service, hints, res);

    if(nResult != 0)
    {
        cout << "Failed to getaddrinfo. Error : " << gai_strerror(nResult) << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    //At this point, res structure contains list of addrinfos
    return nResult;
}

void TCPServer::FreeAddrInfo(struct addrinfo *res)
{
    freeaddrinfo(res);
}

int TCPServer::Socket(const struct addrinfo *res)
{
    int nResult=0;

    nResult = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    //nResult is socket file descriptor in case of success and -1 otherwise
    return nResult;
}

int TCPServer::Bind(int sockfd, const struct addrinfo *res)
{
    int nResult = 0;

    nResult = bind(sockfd, res->ai_addr, res->ai_addrlen);

    //nResult is 0 in case of success and -1 otherwise
    return nResult;
}

int TCPServer::Listen(int sockfd, int backlog)
{
    int nResult = 0;

    nResult = listen(sockfd, backlog);

    //nResult is 0 in case of succcess and -1 otherwise
    return nResult;
}

int TCPServer::Accept(int sockfd)
{
    int nResult = 0;

    //Erase any previous client address stored
    memset(&m_ClientAddr, 0, sizeof(struct sockaddr_storage));

    socklen_t addrlen = sizeof(struct sockaddr_storage);
    nResult = accept(sockfd, (struct sockaddr*)&m_ClientAddr, &addrlen);

    //nResult is newly alloted socket file descriptor for the client connected in case of success.
    //-1 if failure
    return nResult;
}

int TCPServer::GetSockFD()
{
    return m_iSockFD;
}
