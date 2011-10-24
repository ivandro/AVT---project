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

#ifndef GROUP_KEYBOARD_EVENT_H
#define GROUP_KEYBOARD_EVENT_H

#include "Group.h"
#include "IKeyboardEventListener.h"

namespace cg {

	/** cg::GroupKeyboardEvent is a Group that automatically broadcasts
	 *  keyboard events to its inner entities. The 'pre' methods are 
	 *  called before sending the event to the inner entities, while the 
	 *  'post' methods are called after.
	 */
	class GroupKeyboardEvent : public IGetEntities, public IKeyboardEventListener {
	protected:
		/** Called before sending the onKeyPressed event to the group's inner entities. 
		 *	\param	key	The character of the key pressed.
		 */
		virtual void preOnKeyPressed(unsigned char key) {}
		
		/** Called after sending the onKeyPressed event to the group's inner entities. 
		 *	\param	key	The character of the key pressed.
		 */
		virtual void postOnKeyPressed(unsigned char key) {}
		
		/** Called before sending the onKeyReleased event to the group's inner entities. 
		*	\param	key	The character of the key released.
		*/
		virtual void preOnKeyReleased(unsigned char key) {}
		
		/** Called after sending the onKeyReleased event to the group's inner entities. 
		 *	\param	key	The character of the key released.
		 */
		virtual void postOnKeyReleased(unsigned char key) {}
		
		/** Called before sending the onSpecialKeyPressed event to the group's inner entities. 
		 *	\param	key	A GLUT_KEY_* constant for the special key pressed.
		 */
		virtual void preOnSpecialKeyPressed(int key) {}
		
		/** Called after sending the onSpecialKeyPressed event to the group's inner entities. 
		 *	\param	key	A GLUT_KEY_* constant for the special key pressed.
		 */
		virtual void postOnSpecialKeyPressed(int key) {}
		
		/** Called before sending the onSpecialKeyReleased event to the group's inner entities. 
		 *	\param	key	A GLUT_KEY_* constant for the special key released.
		 */
		virtual void preOnSpecialKeyReleased(int key) {}
		
		/** Called after sending the onSpecialKeyReleased event to the group's inner entities. 
		 *	\param	key	A GLUT_KEY_* constant for the special key released.
		 */
		virtual void postOnSpecialKeyReleased(int key) {}
		
    public:
		IGETENTITIES_IMPLEMENTATION
		void onKeyPressed(unsigned char key) {
			preOnKeyPressed(key);
			FOR_EACH_ENTITY(onKeyPressed(key),IKeyboardEventListener)
			postOnKeyPressed(key);
		}
		void onKeyReleased(unsigned char key) {
			preOnKeyReleased(key);
			FOR_EACH_ENTITY(onKeyReleased(key),IKeyboardEventListener)
			postOnKeyReleased(key);
		}
		void onSpecialKeyPressed(int key) {
			preOnSpecialKeyPressed(key);
			FOR_EACH_ENTITY(onSpecialKeyPressed(key),IKeyboardEventListener)
			postOnSpecialKeyPressed(key);
		}
		void onSpecialKeyReleased(int key) {
			preOnSpecialKeyReleased(key);
			FOR_EACH_ENTITY(onSpecialKeyReleased(key),IKeyboardEventListener)
			postOnSpecialKeyReleased(key);
		}
    };

}

#endif // GROUP_KEYBOARD_EVENT_H
