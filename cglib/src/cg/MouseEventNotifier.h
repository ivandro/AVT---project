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

#ifndef MOUSE_EVENT_NOTIFIER_H
#define MOUSE_EVENT_NOTIFIER_H

#include "IMouseEventListener.h"
#include "Notifier.h"
#include "Singleton.h"

namespace cg {

	/** cg::MouseEventNotifier is a singleton notifier that maintains a list
	 *  of cg::IMouseListener and controls the distribution of mouse events. 
	 *  When a mouse event reaches cg::MouseEventNotifier, it is dispatched 
	 *  to all previously registered and currently enabled cg::IMouseListener's.
	 */
	class MouseEventNotifier : public Notifier<IMouseEventListener> {

	SINGLETON_HEADER(MouseEventNotifier)

	public:
		void handleMouse(int button, int state, int x, int y);
        void handleMouseMotion(int x, int y);
        void handleMousePassiveMotion(int x, int y);
		DUMP_METHOD(MouseEventNotifier)
	};
}

#endif // MOUSE_EVENT_NOTIFIER_H
