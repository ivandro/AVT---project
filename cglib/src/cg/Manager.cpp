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

#include "Manager.h"

namespace cg {

	SINGLETON_IMPLEMENTATION_NO_CONSTRUCTOR(Manager)

	Manager::Manager() {
        _intervalMillis = 0;
    }

    //---<OpenGL callbacks>---

    void appUpdateCallback(int value) {
        glutTimerFunc(Manager::instance()->getIntervalMillis(),appUpdateCallback,0);
        glutPostRedisplay();
        Manager::instance()->getApp()->onUpdate();
    }
    void appDisplayCallback() {
        Manager::instance()->getApp()->onDisplay();
        glutSwapBuffers();
    }

    // [RESHAPE]

    void appReshapeCallback(int width, int height) {
        Manager::instance()->getApp()->onReshape(width, height);
        ReshapeEventNotifier::instance()->handleReshape(width, height);
        glutPostRedisplay();
    }

    // [MOUSE]

    void appMouseCallback(int button, int state, int x, int y) {
        MouseEventNotifier::instance()->handleMouse(button,state,x,y);
    }
    void appMotionCallback(int x, int y) {
        MouseEventNotifier::instance()->handleMouseMotion(x,y);
    }
    void appPassiveMotionCallback(int x, int y) {
        MouseEventNotifier::instance()->handleMousePassiveMotion(x,y);
    }

    // [KEYBOARD]

    void appKeyPressedCallback(unsigned char key, int x, int y) {
        KeyBuffer::instance()->pressKey(key);
        KeyboardEventNotifier::instance()->handleKeyPressed(key);
    }
    void appKeyReleasedCallback(unsigned char key, int x, int y) {
        KeyBuffer::instance()->releaseKey(key);
        KeyboardEventNotifier::instance()->handleKeyReleased(key);
    }
    void appSpecialKeyPressedCallback(int key, int x, int y) {
        KeyBuffer::instance()->pressSpecialKey(key);
        KeyboardEventNotifier::instance()->handleSpecialKeyPressed(key);
    }
    void appSpecialKeyReleasedCallback(int key, int x, int y) {
        KeyBuffer::instance()->releaseSpecialKey(key);
        KeyboardEventNotifier::instance()->handleSpecialKeyReleased(key);
    }

    //---</OpenGL callbacks>---

    Application* Manager::getApp() {
        return _app;
    }
    void Manager::runApp(Application *app, int fps, int glut_argc, char** glut_argv) {
        _app = app;
        _intervalMillis = 1000 / fps;
        glutInit(&glut_argc, glut_argv);
        const tWindowInfo& win = _app->getWindowInfo();
        glutInitDisplayMode(win.display_mode);
        glutInitWindowPosition(win.x,win.y);
        glutInitWindowSize(win.width,win.height);
        glutCreateWindow(win.caption.c_str());
		GLenum err = glewInit();
		assert(err == GLEW_OK);
		assert(checkOpenGLInfo(false));
        _app->onInit();
        _app->onReshape(win.width,win.height);
        glutDisplayFunc(appDisplayCallback);
        glutReshapeFunc(appReshapeCallback);
        glutMouseFunc(appMouseCallback);
        glutMotionFunc(appMotionCallback);
        glutPassiveMotionFunc(appPassiveMotionCallback);
        glutIgnoreKeyRepeat(1);
        glutKeyboardFunc(appKeyPressedCallback);
        glutKeyboardUpFunc(appKeyReleasedCallback);
        glutSpecialFunc(appSpecialKeyPressedCallback);
        glutSpecialUpFunc(appSpecialKeyReleasedCallback);
        glutTimerFunc(_intervalMillis,appUpdateCallback,0);
        glutMainLoop();
    }
	void Manager::shutdownApp() {
		_app->shutdown();
		delete _app;
		cleanup();
		exit(0);
	}
    int Manager::getIntervalMillis() const {
        return _intervalMillis;
    }
}
