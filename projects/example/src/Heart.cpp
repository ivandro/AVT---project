#include "Heart.h"

namespace example{

 Heart::Heart(std::string id) : cg::Entity(id) {
	}
	Heart::~Heart() {
	}
	void Heart::init() {
		cg::tWindowInfo win = cg::Manager::instance()->getApp()->getWindowInfo();
		_debug = false;
		_position.set(0, -10);
		_angle = 0.0;
		_colorFaceB=0.0f;	
		faceMod=1;

	}
	void Heart::update(unsigned long elapsed_millis) {
		_colorFaceB =_colorFaceB + faceMod*0.01f;
		if(_colorFaceB > 0.7f|| _colorFaceB < 0.0f)
			faceMod=-1*faceMod;
		_angle += elapsed_millis/10;
	}

	void Heart::draw() {
        glPushMatrix();
		glTranslated(_position[0],0,_position[1]);
		glScaled(0.1,0.1,0.1);
		glRotated(_angle,0,1,0);
		
			drawSide(0,0);
			drawSide(180,-2);
			drawHeart(-2);
			drawHeart(0);
		if(_debug){
			
			
			glBegin(GL_LINES);
			glColor3f(0.0,1.0,0.0); //Green x axis
			glVertex3f(0.0,0.0,0.0);
			glVertex3f(10.0,0.0,0.0);
			glColor3f(1.0,0.0,0.0); //Red y axis
			glVertex3f(0.0,0.0,0.0);
			glVertex3f(0.0,10.0,0.0);
			glColor3f(0.0,1.0,1.0); //Yellow z axis cause blue is less visible
			glVertex3f(0.0,0.0,0.0);
			glVertex3f(0.0,0.0,10.0);
			glEnd();

		}
		glPopMatrix();
		glFlush();			//Finish rendering


	}
		void Heart::setDebug(bool debug){
			_debug = debug;
		}
		void Heart::drawHeart(float translate){
		glPushMatrix();
        glTranslatef(0,0,translate);
        glBegin(GL_TRIANGLE_FAN);
		//glColor3f(1.0,_colorFaceB,0.5);
		glColor3d(1.0,0.3,0.5);
		glVertex3f(0,7,0);
		glVertex3f(0,1,0);
		glVertex3f(-3,3,0);
		glVertex3f(-4,5,0);
		glVertex3f(-4,6,0);
		glVertex3f(-3,7.5,0);
		glVertex3f(-2,8,0);
		glVertex3f(-1,8,0);
		glVertex3f(0,7,0);
		glVertex3f(1,8,0);
		glVertex3f(2,8,0);
		glVertex3f(3,7.5,0);
		glVertex3f(4,6,0);
		glVertex3f(4,5,0);
		glVertex3f(3,3,0);
		glVertex3f(0,1,0);
		glEnd();
        glPopMatrix();

		}
		void Heart::drawSide(float angle,float translate){
			glDisable(GL_CULL_FACE);

			glPushMatrix();
			glTranslatef(0,0,translate);
			glRotated(angle,0,1.0,0);
			glBegin(GL_QUAD_STRIP);
			glColor3f(1.0,1.0,1.0);
			glVertex3f(0,7,0);
			glVertex3f(0,8,-1);
			glVertex3f(-1,8,0);
			glVertex3f(-1,9,-1);
			glVertex3f(-2,8,0);
			glVertex3f(-2,9,-1);
			glVertex3f(-3,8,0);
			glVertex3f(-4,8,-1);
			glVertex3f(-4,6,0);
			glVertex3f(-6,6,-1);
			glVertex3f(-4,5,0);
			glVertex3f(-5,5,-1);
			glVertex3f(-3,3,-1);
			glVertex3f(-4,3,-1);
			glVertex3f(0,1,0);
			glVertex3f(0,0,-1);
			glVertex3f(4,3,-1);
			glVertex3f(3,3,0);
			glVertex3f(5,5,-1);
			glVertex3f(4,5,0);
			glVertex3f(6,6,-1);
			glVertex3f(4,6,0);
			glVertex3f(3,8,0);
			glVertex3f(2,9,-1);
			glVertex3f(2,8,0);
			glVertex3f(0,7,0);
			glEnd();	
			glPopMatrix();
			glEnable(GL_CULL_FACE);

		}

}