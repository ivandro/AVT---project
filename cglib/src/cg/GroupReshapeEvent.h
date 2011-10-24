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

#ifndef GROUP_RESHAPE_EVENT_H
#define GROUP_RESHAPE_EVENT_H

#include "Group.h"
#include "IReshapeEventListener.h"

namespace cg {

	/** cg::GroupReshapeEvent is a Group that automatically broadcasts
	 *  reshape events to its inner entities. The 'pre' methods are 
	 *  called before sending the event to the inner entities, while 
	 *  the 'post' methods are called after.
	 */
	class GroupReshapeEvent : public IGetEntities, public IReshapeEventListener {
	protected:
		/** Called before sending the onReshape event to the group's inner entities. 
		 *	\param	width	The window's width, in pixels.
		 *	\param	height	The window's height, in pixels.
		 */
		virtual void preOnReshape(int width, int height) {}
		
		/** Called after sending the onReshape event to the group's inner entities. 
		 *	\param	width	The window's width, in pixels.
		 *	\param	height	The window's height, in pixels.
		 */
		virtual void postOnReshape(int width, int height) {}
		
    public:
		IGETENTITIES_IMPLEMENTATION
		virtual void onReshape(int width, int height) {
			preOnReshape(width,height);
			FOR_EACH_ENTITY(onReshape(width,height),IReshapeEventListener)
			postOnReshape(width,height);
		}
    };

}

#endif // GROUP_RESHAPE_EVENT_H
