// This file is part of CGLib.
//
// CGLib is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// CGLib is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CGLib; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
// Copyright 2007 Carlos Martinho

#ifndef GROUP_UPDATE_H
#define GROUP_UPDATE_H

#include "Group.h"
#include "IUpdateListener.h"

namespace cg {

	/** cg::GroupUpdate is a Group that automatically invokes the update 
	 *  method of all its inner entities. The preUpdate method is called 
	 *  before invoking the children methods, while the postUpdate is 
	 *  called after.
	 */
	class GroupUpdate : public IGetEntities, public IUpdateListener {
	protected:
		/** Called before sending the update event to the group's inner entities. 
		 *	\param	elapsed_millis	The minimum number of milliseconds before the callback is triggered.
		 */
		virtual void preUpdate(unsigned long elapsed_millis) {}
		
		/** Called after sending the update event to the group's inner entities. 
		 *	\param	elapsed_millis	The minimum number of milliseconds before the callback is triggered.
		 */
		virtual void postUpdate(unsigned long elapsed_millis) {}
		
    public:
		IGETENTITIES_IMPLEMENTATION
		virtual void update(unsigned long elapsed_millis) {
			preUpdate(elapsed_millis);
			FOR_EACH_ENTITY(update(elapsed_millis),IUpdateListener)
			postUpdate(elapsed_millis);
		}
    };

}

#endif // GROUP_UPDATE_H
