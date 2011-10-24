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

#ifndef IKEYBOARD_EVENT_LISTENER_H
#define IKEYBOARD_EVENT_LISTENER_H

namespace cg {

	/** cg::IKeyboardEventListener is the callback interface for keyboard events.
	  * Special keys are the GLUT special keys (e.g. cursor and function keys).
	  */
	class IKeyboardEventListener {
    public:
        /** When a user types into the window, each key press generating an ASCII character
		 *	will generate a keyboard event in GLUT that is distributed by cglib to all 
		 *	registred Entities that implement the IKeyboardEventListener interface. 
		 *	For more details, please refer to glutKeyboardFunc in GLUT documentation. 
		 *	\param	key		The generated ASCII character.
		 */
        virtual void onKeyPressed(unsigned char key) {}
		
        /** When a user types into the window, each key release matching an ASCII character 
		 *	will generate a keyboard up event in GLUT that is distributed by cglib to all 
		 *	registred Entities that implement the IKeyboardEventListener interface. 
		 *	For more details, please refer to glutKeyboardUpFunc in GLUT documentation. 
		 *	\param	key		The generated ASCII character.
		 */
        virtual void onKeyReleased(unsigned char key) {}
		
        /** When keyboard function or directional keys are pressed a keyboard event will be
		 *	generated in GLUT and distributed by cglib to all registred Entities that implement 
		 *	the IKeyboardEventListener interface. For more details, please refer to glutSpecialFunc 
		 *	in GLUT documentation. 
		 *	\param	key		A GLUT_KEY_* constant for the special key pressed.
		 */
        virtual void onSpecialKeyPressed(int key) {}
		
        /** When keyboard function or directional keys are released a keyboard event will be
		 *	generated in GLUT and distributed by cglib to all registred Entities that implement 
		 *	the IKeyboardEventListener interface. For more details, please refer to  
		 *	glutSpecialUpFunc in GLUT documentation. 
		 *	\param	key		A GLUT_KEY_* constant for the special key released.
		 */
        virtual void onSpecialKeyReleased(int key) {}
    };

}

#endif // IKEYBOARD_EVENT_LISTENER_H
