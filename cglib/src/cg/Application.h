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

#ifndef APPLICATION_H
#define APPLICATION_H

#include <stdexcept>
#include <string>
#include <sys/timeb.h>
#include "gl.h"

#include "DebugFile.h"
#include "DebugNotifier.h"
#include "Entity.h"
#include "KeyBuffer.h"
#include "KeyboardEventNotifier.h"
#include "MouseEventNotifier.h"
#include "Properties.h"
#include "Registry.h"
#include "ReshapeEventNotifier.h"
#include "UpdateNotifier.h"
#include "Util.h"
#include "View.h"



namespace cg {
	
    typedef struct {
        std::string caption;
        unsigned int x, y, width, height;
        int display_mode;
    } tWindowInfo;

    typedef struct {
        unsigned long last, current, elapsed;
    } tTimeInfo;

	/** cg::Application is an abstract class controlling the initialization, 
	 *  update and display cycle of the application.
	 *
	 *  To create an application, just create a subclass of cg::Application and 
	 *  implement the methods cg::Application::createEntities and 
	 *  cg::Application:createViews.
	 *  In the cg::Application::createEntities method, use the protected method
	 *  cg::Application::addEntity to add each entity, one by one. This method will
	 *  automatically register the cg::Entity with the correct notifiers, according
	 *  to its implemented interfaces. These in turn will be called by each notifier 
	 *  during the simulation cycle.
	 *  In the cg::Application::createViews method, use the protected method
	 *  cg::Application::createView to create a new View for the application.
	 *  At least one view is required.
	 *
	 *  The simulation cycle can be resumed to the following ordered steps: 
	 *  debug, update, draw and drawOverlay. The init step is performed once at 
	 *  the beginning of the simulation.
	 *  For a detailed view of the simulation cycle, please refer to the methods
	 *  the cg::Application::onInit, cg::Application::onUpdate, and 
	 *  cg::Application::onDisplay.
     *  These methods can be redefined in the subclass if a finer control of
	 *  the simulation cycle is needed.
	 */
    class Application {

    protected:
        tWindowInfo _windowInfo;

        tTimeInfo _timeInfo;
        struct timeb _timeb;
        void updateFrameTime();

		bool _isFirstUpdate;
		void setup();
		void addEntity(Entity* entity);
		View* createView(const std::string& id);

    public:
		/** Creates a cg::Application with the default parameters.
		 *  The parameters are defined in the setup private method.
		 */
		Application();
		
		/** Creates a cg::Application and loads (property,value) pairs defined in property_file at startup.
		 *	\param property_file File containing the (property,value) pairs to be loaded at startup.
		 */
		Application(const std::string property_file);
        
		/** Destructor.
		 */
        virtual ~Application();

        /** Returns information on the Application's window.
		 *	\return A structure containing window information (caption, x, y, width, height, display_mode). 
		 */
		const tWindowInfo& getWindowInfo() const;
		
        /** Returns time related information from the Application.
		 *	\return A structure containing time information (last, current, elapsed). 
		 */
		const tTimeInfo& getTimeInfo() const;

        virtual void onInit();
        virtual void onUpdate();
        virtual void onDisplay();
        void onReshape(int w, int h);
		
		/** Closes the Application.
		 */
		void shutdown();

        /** Called when the Application starts. 
		 *	Must be reimplemented to create all entities controlled by the Application. 
		 */
		virtual void createEntities() = 0;

		/** Called when the Application starts. 
		 *	Must be reimplemented to create all application viewports. 
		 */
		virtual void createViews() = 0;

		/** Writes the cg::Application structure to the "log.txt" file in the program directory. 
		 */
		void dump() const;
    };

}

#endif // APPLICATION_H
