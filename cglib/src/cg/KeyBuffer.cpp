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

#include "KeyBuffer.h"

namespace cg {

	SINGLETON_IMPLEMENTATION_NO_CONSTRUCTOR(KeyBuffer)

	KeyBuffer::KeyBuffer() {
        int i;
        for (i = 0; i < KEY_MAX; i++) {
            _key[i] = false;
        }
        for (i = 0; i < SPECIAL_KEY_MAX; i++) {
            _specialKey[i] = false;
        }
    }
    void KeyBuffer::pressKey(unsigned char key) {
        _key[key] = true;
    }
    void KeyBuffer::releaseKey(unsigned char key) {
        _key[key] = false;
    }
    bool KeyBuffer::isKeyDown(unsigned char key) const {
        return _key[key];
    }
    bool KeyBuffer::isKeyUp(unsigned char key) const {
        return !_key[key];
    }

    inline
    int KeyBuffer::adjustSpecialKey(int key) const {
        if (key >= GLUT_KEY_LEFT) {
            return (key - GLUT_KEY_LEFT + 12);
        } else {
            return (key - GLUT_KEY_F1);
        }
    }

    void KeyBuffer::pressSpecialKey(int key) {
        key = adjustSpecialKey(key);
        _specialKey[key] = true;
    }
    void KeyBuffer::releaseSpecialKey(int key) {
        key = adjustSpecialKey(key);
        _specialKey[key] = false;
    }
    bool KeyBuffer::isSpecialKeyDown(int key) const {
        key = adjustSpecialKey(key);
        return _specialKey[key];
    }
    bool KeyBuffer::isSpecialKeyUp(int key) const {
        key = adjustSpecialKey(key);
        return !_specialKey[key];
    }

}
