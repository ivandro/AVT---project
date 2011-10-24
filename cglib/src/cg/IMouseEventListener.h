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

#ifndef IMOUSE_EVENT_LISTENER_H
#define IMOUSE_EVENT_LISTENER_H

namespace cg {

	/** cg::IMouseEVentListener is the callback interface for mouse events.
	 */
	class IMouseEventListener {
    public:
        /** When a user presses and releases mouse buttons in the window, each press 
		 *	and each release generates a mouse event in GLUT that is distributed by cglib 
		 *	to all registred Entities that implement the IMouseEventListener interface. 
		 *	For more details, please refer to glutMouseFunc in GLUT documentation. 
		 *	\param	button	One of  GLUT_LEFT_BUTTON,  GLUT_MIDDLE_BUTTON, or  GLUT_RIGHT_BUTTON.
		 *	\param	state	Either  GLUT_UP or  GLUT_DOWN.
		 *	\param	x		The mouse's window relative x coordinate.
		 *	\param	y		The mouse's window relative y coordinate.
		 */
		virtual void onMouse(int button, int state, int x, int y) {}
		
        /** When the mouse moves within the window while one or more mouse buttons are pressed
		 *	a mouse motion event is generated in GLUT that is distributed by cglib to all 
		 *	registered Entities that implement the IMouseEventListener interface. For more 
		 *	details, please refer to glutMotionFunc in GLUT documentation. 
		 *	\param	x		The mouse's window relative x coordinate.
		 *	\param	y		The mouse's window relative y coordinate.
		 */
        virtual void onMouseMotion(int x, int y) {}
		
        /** When the mouse moves within the window while no mouse buttons are pressed a mouse 
		 *	passive motion event is generated in GLUT that is distributed by cglib to all 
		 *	registered Entities that implement the IMouseEventListener interface. For more 
		 *	details, please refer to glutPassiveMotionFunc in GLUT documentation.
		 *	\param	x		The mouse's window relative x coordinate.
		 *	\param	y		The mouse's window relative y coordinate.
		 */
        virtual void onMousePassiveMotion(int x, int y) {}
    };

}

#endif // IMOUSE_EVENT_LISTENER_H
