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

#ifndef KEYBUFFER_H
#define KEYBUFFER_H

#include "gl.h"
#include "Singleton.h"

namespace cg {

#define KEY_MAX 256
#define SPECIAL_KEY_MAX 22

	/** cg::Keybuffer maintains the current status of all keys of the keyboard.
	 *  At any time, this singleton can be queried to check if a key is pressed 
	 *  or released. This allows to detect multiple key combinations.
	 *  Special keys are the GLUT special keys (e.g. cursor and function keys).
	 */
    class KeyBuffer {

	SINGLETON_HEADER(KeyBuffer)

    private:
        bool _key[KEY_MAX];
        bool _specialKey[SPECIAL_KEY_MAX];
        int adjustSpecialKey(int key) const;

    public:
        void pressKey(unsigned char key);
        void pressSpecialKey(int key);
        void releaseKey(unsigned char key);
        void releaseSpecialKey(int key);
		
		/** Checks if a key is down.
		 *	\param	key		The key's ASCII character.
		 *	\return			True if the given key is down, false otherwise. 
		 */
		bool isKeyDown(unsigned char key) const;
        
		/** Checks if a key is up.
		 *	\param	key		The key's ASCII character.
		 *	\return			True if the given key is up, false otherwise. 
		 */
		bool isKeyUp(unsigned char key) const;
        
		/** Checks if a special key is down.
		 *	\param	key		The GLUT_KEY_* constant for the special key.
		 *	\return			True if the given special key is down, false otherwise. 
		 */
		bool isSpecialKeyDown(int key) const;
        
		/** Checks if a special key is up.
		 *	\param	key		The GLUT_KEY_* constant for the special key.
		 *	\return			True if the given special key is up, false otherwise. 
		 */
		bool isSpecialKeyUp(int key) const;
    };
}

#endif // KEYBUFFER_H
