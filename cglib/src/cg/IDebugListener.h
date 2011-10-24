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

#ifndef IDEBUG_LISTENER_H
#define IDEBUG_LISTENER_H

#include <fstream>

namespace cg {

	/** cg::IDebugListener is the callback interface for the debug step.
	 */
	class IDebugListener {
    public:
        /** Automatically invoked by the DebugNotifier on each debug step. 
		 *	Defines the callback's behavior. 
		 *	\param	file	The debug file.
		 */
		virtual void debug(std::ofstream& file) = 0;
    };

}

#endif // IDEBUG_LISTENER_H
