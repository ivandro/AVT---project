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

#ifndef VIEW_H
#define VIEW_H

#include <cmath>
#include "gl.h"
#include "DrawNotifier.h"
#include "Entity.h"
#include "IDrawListener.h"
#include "IViewListener.h"
#include "Notifier.h"
#include "LockableOrderedMap.h"
#include "Registry.h"
#include "Vector.h"

namespace cg {

	/** cg::View defines a view over a group of entities of the application.
	 *	Note that the same entity can be linked to different views. Only 
	 *	entities linked to a View are drawn. The order by which the Entities 
	 *	are linked to the view affects the way they will appear. Entities at 
	 *	the beginning are drawn first, entities at the end are drawn last.
	 */
	class View : public Entity, public IViewListener,
		public IReshapeEventListener
	{
	private:
		Vector2f _positionf,_sizef;
		Vector2i _positioni, _sizei;
		DrawNotifier _drawNotifier;
		IDrawListener* getDrawListener(const std::string& id);

	public:
		/** Creates a View.
		 *	\param id	A unique id.
		 *	\return		An enabled View with identifier id.
		 */
		View(const std::string& id);
		/**	Destroys a View.
		 */
		virtual ~View();
		/**	Initializes a View. Called when a View is created.
		 */
		void init() {}

		/**	Links an Entity at the beginning of the list.
		 *	\param	id	Id of the Entity to be linked.
		 */
		void linkEntityAtBeginning(std::string entity_id);
		/**	Links an Entity at the end of the list.
		 *	\param	id	Id of the Entity to be linked.
		 */
		void linkEntityAtEnd(std::string entity_id);
		/**	Links an Entity before an entry point (another Entity).
		 *	\param	entity_id	Id of the Entity to be linked.
		 *	\param	entry_point	Id of the Entity representing the entry point.
		 */
		void linkEntityBefore(std::string entity_id, std::string entry_point);
		/**	Links an Entity after an entry point (another Entity).
		 *	\param	entity_id	Id of the Entity to be linked.
		 *	\param	entry_point	Id of the Entity representing the entry point.
		 */
		void linkEntityAfter(std::string entity_id, std::string entry_point);
		/**	Unlinks an Entity from the View.
		 *	\param	entity_id	Id of the Entity to be unlinked.
		 */
		void unlinkEntity(std::string entity_id);

		/**	Set's the View's viewport.
		 *	\param	x		The View's new x position (considering width of the window = 1.0).
		 *	\param	y		The View's new y position (considering height of the window = 1.0).
		 *	\param	width	The View's new width (considering width of the window = 1.0).
		 *	\param	height	The View's new height (considering height of the window = 1.0).
		 */
		void setViewport(float x, float y, float width, float height);
		/** Calls the draw, drawBlended and drawOverlay methods of all Entities 
		 *	connected to the View, in the same order by which they were added.
		 */
		virtual void draw();
		/** Defines the projection to be used by the View
		 */
		virtual void setOverlayProjection();
		void onReshape(int width, int height);
	};
}

#endif // VIEW_H