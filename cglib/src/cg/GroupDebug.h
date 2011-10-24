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

#ifndef GROUP_DEBUG_H
#define GROUP_DEBUG_H

#include <fstream>
#include "Group.h"
#include "IDebugListener.h"

namespace cg {

	/** cg::GroupDebug is a Group that automatically invokes the debug method
	 *  of all its inner entities. The preDebug method is called before
	 *  invoking the children methods, while the postDebug is called after.
	 */
	class GroupDebug : public IGetEntities, public IDebugListener {
	protected:
		/** Called before sending the debug event to the group's inner entities. 
		 *	\param	file	The debug output file stream.
		 */
		virtual void preDebug(std::ofstream& file) {}
		
		/** Called after sending the debug event to the group's inner entities. 
		 *	\param	file	The debug output file stream.
		 */
		virtual void postDebug(std::ofstream& file) {}
		
    public:
		IGETENTITIES_IMPLEMENTATION
		virtual void debug(std::ofstream& file) {
			preDebug(file);
			FOR_EACH_ENTITY(debug(file),IDebugListener)
			postDebug(file);
		}
    };

}

#endif // GROUP_DEBUG_H
