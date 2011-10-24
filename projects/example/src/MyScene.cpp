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

#include "MyScene.h"

namespace example {

	MyScene::MyScene() : cg::Entity("Lighting") {
	}
	MyScene::~MyScene() {
	}
	void MyScene::init() {
		glCullFace(GL_FRONT);
		glEnable(GL_CULL_FACE);

		GLfloat lmodel_ambient[] = {0.1f,0.1f,0.1f,1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
		glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

		float fog_color[] = {0.1f,0.1f,0.1f,1.0f};
		glFogi(GL_FOG_MODE,GL_LINEAR);
		glFogfv(GL_FOG_COLOR, fog_color);
		glFogf(GL_FOG_START,15.0f);
		glFogf(GL_FOG_END,25.0f);
	}
	void MyScene::draw() {
		glEnable(GL_LIGHTING);
		glEnable(GL_FOG);
	}
	void MyScene::drawOverlay() {
		glDisable(GL_LIGHTING);
		glDisable(GL_FOG);
	}
}