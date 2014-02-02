/**
 * @file TCPServer.h
 * @brief TCP socket based server
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

#ifndef _TCPSERVER_H_
#define _TCPSERVER_H_

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

class TCPServer
{
    public:

    protected:
        //Returns 0 on success, error code otherwise
        int                     GetAddrInfo(const char* node,
                                            const char* service,
                                            const struct addrinfo* hints,
                                            struct addrinfo** res);
        void                    FreeAddrInfo(struct addrinfo *res);

        //Returns socket file descriptor number if successs, -1 if failure
        int                     Socket(const struct addrinfo *res);

        //Returns 0 if success, -1 otherwise
        int                     Bind(int sockfd, const struct addrinfo *res);

        //Returns 0 if success, -1 otherwise
        int                     Listen(int sockfd, int backlog);

        //Returns new socket file descriptor if success, -1 otherwise
        int                     Accept(int sockfd, struct sockaddr_storage client_addr, socklen_t addr_size);

    private:
        int                     m_iSockFD;
        addrinfo                m_stHints;
        addrinfo                *m_stResAddr;
        std::string             m_sIP;
        int                     m_iPort;

};

#endif  //_TCPSERVER_H_
