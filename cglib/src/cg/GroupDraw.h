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

#ifndef GROUP_DRAW_H
#define GROUP_DRAW_H

#include <stdexcept>
#include "Group.h"
#include "IDrawListener.h"
#include "LockableOrderedMap.h"

namespace cg {

	/** cg::GroupDraw is a Group that automatically invokes the draw method
	 *  of all its inner entities. The preDraw method is called before
	 *  invoking the children methods, while the postDraw is called after.
	 */
	class GroupDraw : public IDrawListener {
	protected:
		/** Called before sending the draw event to the group's inner entities. 
		 */
		virtual void preDraw() {}
		virtual void preDrawBlended() {}
		virtual void preDrawOverlay() {}
		
		/** Called after sending the draw event to the group's inner entities. 
		 */
		virtual void postDraw() {}
		virtual void postDrawBlended() {}
		virtual void postDrawOverlay() {}
		
    public:
		IGETENTITIES_IMPLEMENTATION
		virtual void draw() {
			preDraw();
			FOR_EACH_ENTITY(draw(),IDrawListener)			
			postDraw();
		}
		virtual void drawBlended() {
			preDrawBlended();
			FOR_EACH_ENTITY(drawBlended(),IDrawListener)
			postDrawBlended();
		}
		virtual void drawOverlay() {
			preDrawOverlay();
			FOR_EACH_ENTITY(drawOverlay(),IDrawListener)
			postDrawOverlay();
		}
	};
}

#endif // GROUP_DRAW_H
