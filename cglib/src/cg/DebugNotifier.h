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

#ifndef DEBUG_NOTIFIER_H
#define DEBUG_NOTIFIER_H

#include "IDebugListener.h"
#include "Notifier.h"
#include "Singleton.h"

namespace cg {

	/** cg::DebugNotifier controls the debug step of the application, by
	 *  calling the cg::IDebugListener::debug method of all the previously 
	 *  registered and currently enabled cg::IDebugListener's.
	 */
	class DebugNotifier : public Notifier<IDebugListener> {

	SINGLETON_HEADER(DebugNotifier)
	public: 
		void debug();
		DUMP_METHOD(DebugNotifier)
	};
}

#endif // DEBUG_NOTIFIER_H
