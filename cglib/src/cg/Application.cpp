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

#include "Application.h"

namespace cg {

    Application::Application() {
		setup();
    }
    Application::Application(const std::string property_file) {
		setup();
		try {
			cg::Properties::instance()->load(property_file);
		} catch(std::runtime_error& e) {
			DebugFile::instance()->writeException(e);
			throw e;
		}
    }
	inline
	void Application::setup() {
        _timeInfo.last = 0;
        _timeInfo.current = 0;
        _timeInfo.elapsed = 0;
        _windowInfo.caption = "OpenGL GLUT Application";
        _windowInfo.x = 100;
        _windowInfo.y = 100;
        _windowInfo.width = 640;
        _windowInfo.height = 480;
        _windowInfo.display_mode = GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH;
		_isFirstUpdate = true;
	}
    Application::~Application() {
    }
    const tWindowInfo& Application::getWindowInfo() const {
        return _windowInfo;
    }
    const tTimeInfo& Application::getTimeInfo() const {
        return _timeInfo;
    }
    void Application::onInit() {
        glShadeModel(GL_SMOOTH);
		try {
			createEntities();
			createViews();
		} catch(std::runtime_error& e) {
			DebugFile::instance()->writeException(e);
			throw e;
		}
		Registry::instance()->init();
    }
    inline
    void Application::updateFrameTime() {
        ftime(&_timeb);
		_timeInfo.last = _timeInfo.current;
		_timeInfo.current = (unsigned long)((_timeb.time * 1000) + _timeb.millitm);
		_timeInfo.elapsed = _timeInfo.current - _timeInfo.last;
    }
    void Application::onUpdate() {
        updateFrameTime();
		if(_isFirstUpdate) {
			_isFirstUpdate = false;
			return;
		}
		DebugNotifier::instance()->debug();
		UpdateNotifier::instance()->update(_timeInfo.elapsed);
    }
    void Application::onDisplay() {
        glClearColor(0.1f,0.1f,0.1f,0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ViewNotifier::instance()->draw();
		assert(checkOpenGLError() == false);
    }
    void Application::onReshape(int w, int h) {
        _windowInfo.width = w;
        _windowInfo.height = h;
    }
	void Application::addEntity(Entity *entity) {
		if(entity != 0) {
			Registry::instance()->add(entity);
		}
	}
	View* Application::createView(const std::string& id) {
		View* v = new View(id);
		if(v != 0) {
			Registry::instance()->add(v);
		}
		return v;
	}
	void Application::shutdown() {
		KeyboardEventNotifier::instance()->cleanup();
		MouseEventNotifier::instance()->cleanup();
		ReshapeEventNotifier::instance()->cleanup();
		UpdateNotifier::instance()->cleanup();
		DebugNotifier::instance()->cleanup();
		Registry::instance()->cleanup();
		DebugFile::instance()->cleanup();
		KeyBuffer::instance()->cleanup();
		Properties::instance()->cleanup();
		Util::instance()->cleanup();
		ViewNotifier::instance()->cleanup();
	}
	void Application::dump() const {
		Registry::instance()->dump();
		DebugFile::instance()->writeLine("[Notifiers]");
		UpdateNotifier::instance()->dump();
		KeyboardEventNotifier::instance()->dump();
		MouseEventNotifier::instance()->dump();
		ReshapeEventNotifier::instance()->dump();
		DebugNotifier::instance()->dump();
		DebugFile::instance()->newLine();
		ViewNotifier::instance()->dump();
	}
}
