/// @cond
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

#ifndef RESHAPE_EVENT_NOTIFIER_H
#define RESHAPE_EVENT_NOTIFIER_H

#include "IReshapeEventListener.h"
#include "Notifier.h"
#include "Singleton.h"

namespace cg {

	/** cg::ReshapeEventNotifier is a singleton notifier that maintains a list
	 *  of cg::IReshapeListener and controls the distribution of reshape events. 
	 *  When a reshape event reaches cg::ReshapeEventNotifier, it is dispatched 
	 *  to all previously registered and currently enabled cg::IReshapeListener's.
	 */
	class ReshapeEventNotifier : public Notifier<IReshapeEventListener> {

	SINGLETON_HEADER(ReshapeEventNotifier)
	
	public:
		void handleReshape(int width, int height);
		DUMP_METHOD(ReshapeEventNotifier)
	};
}

#endif // RESHAPE_EVENT_NOTIFIER_H
/// @endcond
