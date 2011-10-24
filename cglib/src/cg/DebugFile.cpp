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

#include "DebugFile.h"

#include <time.h>

namespace cg {

    DebugFile* DebugFile::_instance = 0;

    DebugFile* DebugFile::instance() {
        if (_instance == 0) { 
			_instance = new DebugFile(); 
		}
        return _instance; 
	}
    DebugFile::DebugFile() {
		_file.open("cglib.log", std::fstream::out | std::fstream::app);
		time_t t;
		time(&t);
		char buf[26];
		ctime_s(buf,26,&t);
		_file << std::endl << "[log] " << buf << std::endl;
	}
    DebugFile::~DebugFile() { 
	}
    void DebugFile::cleanup() {
		_file.close();
		delete _instance;
	}
	std::ofstream& DebugFile::getOutputFileStream() {
		return _file;
	}
	void DebugFile::write(const std::string& s) {
		_file << s;
	}
	void DebugFile::writeLine(const std::string& s) {
		_file << s << std::endl;
	}
	void DebugFile::newLine() {
		_file << std::endl;
	}
	void DebugFile::writeException(std::runtime_error& e) {
		_file << "(EXCEPTION) " << e.what() << std::endl;
	}
}