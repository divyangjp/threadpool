/**
 * @file Condition.cpp
 * @brief Wrapper class impl for Posix Condition
 * @author Divyang Patel <divyang.jp@gmail.com>
 * @version 1.0
 * @date 2013-04-05
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

#include "Condition.h"

Condition::Condition()
{
	pthread_cond_init(&m_cond, NULL);
}

Condition::~Condition()
{
	pthread_cond_destroy(&m_cond);
}

void Condition::Wait()
{
	pthread_cond_wait(&m_cond, &m_mutex);
}

void Condition::Signal()
{
	pthread_cond_signal(&m_cond);
}

void Condition::Broadcast()
{
	pthread_cond_broadcast(&m_cond);
}

