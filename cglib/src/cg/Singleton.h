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

#ifndef SINGLETON_MACRO_H
#define SINGLETON_MACRO_H

/** Set of macros to implement singletons.
 */

#define SINGLETON_HEADER(CLASSNAME)\
	private: static CLASSNAME* _instance; CLASSNAME();\
	public: static CLASSNAME* instance(); virtual ~CLASSNAME(); void cleanup();

#define SINGLETON_IMPLEMENTATION(CLASSNAME)\
    CLASSNAME* CLASSNAME::_instance = 0;\
    CLASSNAME* CLASSNAME::instance() {\
        if (_instance == 0) { _instance = new CLASSNAME(); }\
        return _instance; }\
    CLASSNAME::CLASSNAME() {}\
    CLASSNAME::~CLASSNAME() {}\
	void CLASSNAME::cleanup() { if (_instance != 0) { delete _instance; } }

#define SINGLETON_IMPLEMENTATION_NO_CONSTRUCTOR(CLASSNAME)\
    CLASSNAME* CLASSNAME::_instance = 0;\
    CLASSNAME* CLASSNAME::instance() {\
        if (_instance == 0) { _instance = new CLASSNAME(); }\
        return _instance; }\
    CLASSNAME::~CLASSNAME() {}\
	void CLASSNAME::cleanup() { if (_instance != 0) { delete _instance; } }

#endif // SINGLETON_MACRO_H
