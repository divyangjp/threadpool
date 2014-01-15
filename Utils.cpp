/**
 * @file Utils.cpp
 * @brief See header
 * @author Divyang Patel <divyang.jp@gmail.com>
 * @version 1.0
 * @date 2014-01-14
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

#include "Utils.h"

void Utils::MillisecsToTimespec( unsigned long ai_tMilliSecs, struct timespec& ao_stTimeSpec)
{
    ao_stTimeSpec.tv_sec = ai_tMilliSecs / 1000;
    ao_stTimeSpec.tv_nsec = (ai_tMilliSecs % 1000) * 1000000;
}
        
void Utils::SecsToTimespec( unsigned long ai_tSecs, struct timespec& ao_stTimeSpec)
{
    unsigned long tMilliSecs = ai_tSecs*1000;
    MillisecsToTimespec(tMilliSecs, ao_stTimeSpec);
}
