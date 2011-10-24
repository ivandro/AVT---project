// This file is an example for CGLib.
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

#include "MyApp.h"

namespace lab6 {

	MyApp::MyApp() {
		_windowInfo.caption = "Lab2";
		_windowInfo.width = 800;
		_windowInfo.height = 600;
	}
	MyApp::~MyApp() {
	}
	void MyApp::createEntities() {
		addEntity(new MyScene());
		addEntity(new MyCamera());
		addEntity(new MyLight("Light1"));
		addEntity(new MyController());
		addEntity(new MyWorld());
		addEntity(new MyTeapot("Teapot1"));
		addEntity(new MyTexturedBox("Box1"));
		addEntity(new MyQuadric("Quadric1"));
	}
	void MyApp::createViews() {
		cg::View* v = createView("view");
		v->linkEntityAtEnd("Lighting");
		v->linkEntityAtEnd("Camera");
		v->linkEntityAtEnd("Light1");
		v->linkEntityAtEnd("World");
		v->linkEntityAtEnd("Teapot1");
		v->linkEntityAtEnd("Box1");
		v->linkEntityAtEnd("Quadric1");
		v->linkEntityAtEnd("Controller");
	}
}