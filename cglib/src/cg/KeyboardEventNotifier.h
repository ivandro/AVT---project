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

#ifndef KEYBOARD_EVENT_NOTIFIER_H
#define KEYBOARD_EVENT_NOTIFIER_H

#include "IKeyboardEventListener.h"
#include "Notifier.h"
#include "Singleton.h"

namespace cg {

	/** cg::KeyboardEventNotifier is a singleton notifier that maintains a list
	 *  of cg::IKeyboardListener and controls the distribution of keyboard events. 
	 *  When a keyboard event reaches cg::KeyboardEventNotifier, it is dispatched 
	 *  to all previously registered and currently enabled cg::IKeyboardListener's.
	 */
	class KeyboardEventNotifier : public Notifier<IKeyboardEventListener> {

	SINGLETON_HEADER(KeyboardEventNotifier)
	public:
        void handleKeyPressed(unsigned char key);
        void handleKeyReleased(unsigned char key);
        void handleSpecialKeyPressed(int key);
        void handleSpecialKeyReleased(int key);
		DUMP_METHOD(KeyboardEventNotifier)
	};
}

#endif // KEYBOARD_EVENT_NOTIFIER_H
