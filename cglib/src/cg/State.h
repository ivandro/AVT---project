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

#include <fstream>

#ifndef STATE_H
#define STATE_H

namespace cg {

	/** cg::State is a utility class maintaining an enabled/disabled status.
	 */
	struct State {
	private:
		bool _isEnabled;

	public:
		/** Creates a State structure.
		 *	\param	is_enabled	True if the State should be enabled, false otherwise.
		 *	\return				An State structure with state is_enabled (enabled by default). 
		 */
		State(bool is_enabled = true) : _isEnabled(is_enabled) {}
		
		/** Destructor. 
		 */
		virtual ~State() {}
		
		/** Enables the State structure. 
		 */
		void enable() {	_isEnabled = true; }
		
		/** Disables the State structure. 
		 */
		void disable() { _isEnabled = false; }
		
		/** If the State structure is enabled, it will be disabled and vice-versa. 
		 */
		void toggle() {	_isEnabled = !_isEnabled; }
		
		/** Checks if the State structure is enabled.
		 *	\return	True if the State structure is enabled, false otherwise. 
		 */
		bool isEnabled() const { return _isEnabled; }
		
		/** Sets the State structure to a desired bool state. 
		 *	\param	is_enabled	True if we want the State to be enabled, false otherwise.
		 */
		void set(bool is_enabled) { _isEnabled = is_enabled; }

		/** Prints "[+]" if the State structure is enabled and "[-]" if it is disabled. 
		 *	\param	os	
		 *	\param	s	The State structure.
		 */
		friend inline std::ostream& operator<<(std::ostream& os, const State& s) {
			if(s._isEnabled) { os << "[+]"; } else { os << "[-]"; }
			return os;
		}
	};
}

#endif // STATE_H