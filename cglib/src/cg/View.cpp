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

#include "View.h"

namespace cg {

	View::View(const std::string& id) : Entity(id) {
		_positionf.set(0.0f,0.0f);
		_sizef.set(1.0f,1.0f);
	}
	View::~View() {
	}
	inline
	IDrawListener* View::getDrawListener(const std::string& id) {
		Entity* entity = Registry::instance()->get(id);
		if(entity) {
			return dynamic_cast<IDrawListener*>(entity);
		}
		return 0;
	}
#define LINK_ENTITY(COMMAND,ID)\
	IDrawListener* dl = getDrawListener(ID);\
	if(dl) { _drawNotifier.COMMAND(dl); }\

#define LINK_ENTITY_AT(COMMAND,ID,ENTRYPOINT)\
	IDrawListener* dl = getDrawListener(ID);\
	if(dl) { _drawNotifier.COMMAND(dl,ENTRYPOINT); }\

	void View::linkEntityAtBeginning(std::string entity_id) {
		LINK_ENTITY(addAtBeginning,entity_id)
	}
	void View::linkEntityAtEnd(std::string entity_id) {
		LINK_ENTITY(addAtEnd,entity_id)
	}
	void View::linkEntityBefore(std::string entity_id, std::string entrypoint) {
		LINK_ENTITY_AT(addBefore,entity_id,entrypoint)
	}
	void View::linkEntityAfter(std::string entity_id, std::string entrypoint) {
		LINK_ENTITY_AT(addAfter,entity_id,entrypoint)
	}
	void View::unlinkEntity(std::string entity_id) {
		_drawNotifier.remove(entity_id);
	}
	void View::setViewport(float x, float y, float width, float height) {
		_positionf.set(x,y);
		_sizef.set(width,height);
	}
	void View::onReshape(int width, int height) {
		_positioni[0] = (int)(_positionf[0] * width);
		_positioni[1] = (int)(_positionf[1] * height);
		_sizei[0] = (int)(_sizef[0] * width);
		_sizei[1] = (int)(_sizef[1] * height);
	}
	void View::setOverlayProjection() {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0,_sizei[0],0,_sizei[1]);  
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
	}
	void View::draw() {
		glViewport(_positioni[0],_positioni[1],_sizei[0],_sizei[1]);
        glEnable(GL_DEPTH_TEST);
        _drawNotifier.draw();
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		_drawNotifier.drawBlended();
        glDisable(GL_DEPTH_TEST);
		setOverlayProjection();
        _drawNotifier.drawOverlay();
        glDisable(GL_BLEND);
	}
}