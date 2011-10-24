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

#ifndef DEBUG_FILE_H
#define DEBUG_FILE_H

#include <fstream>
#include <stdexcept>
#include <string>

namespace cg {

	/** cg::DebugFile is a singleton class that writes to a single text file for debug purposes. 
	 *  Any class can write to the debug file using the singleton's public methods or, alternatively,
	 *  get the direct output file stream handle through the method cg::DebugFile::getOutputFileStream.
	 */
	class DebugFile  {

	private: 
		static DebugFile* _instance; 
		DebugFile();
		std::ofstream _file;

	public: 
		virtual ~DebugFile();
		void cleanup();
		
		/** Singleton instance.
		 *	\return Pointer to the singleton instance. 
		 */
		static DebugFile* instance(); 
		
		/** Gets the debug file stream.
		 *	\return The debug file stream. 
		 */
		std::ofstream& getOutputFileStream();
		
		/** Writes a string to the debug file. 
		 *	\param s The string to be written to the file.
		 */
		void write(const std::string& s);
		
		/** Writes a string followed by a new line to the debug file. 
		 *	\param s The string to be written to the file.
		 */
		void writeLine(const std::string& s);
		
		/** Writes a new line to the debug file. 
		 */
		void newLine();
		
		/** Writes a runtime_error exception to the debug file. 
		 *	\param e The exception to be written to the file.
		 */
		void writeException(std::runtime_error& e);
	};
}

#endif // DEBUG_FILE_H