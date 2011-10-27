#include "MyBox.h"

namespace example {

	MyBox::MyBox(std::string id):

		cg::Entity(id),
		_movable( true ),
		_isDebug( false ),
		m_lastMousePosition( 0.0, 0.0, -1.0 ) {
	}

	MyBox::~MyBox() {
	}

	// porque é que está função é inline? 
	// Qual é a diferença entre o x0 e x1, y0 e y1?
	// O que é o parâmetro n? 
	// O que são os parâmetros nx, ny e nz? normal?
	// nome da função é muito esquecito! plano dividido? o que é isso? 
	// A função não é um predicado( não devolve um booleano ) logo realiza uma acção no presente! Seria mais fácil se o nome estivesse no infinitivo ou no presente? 
	inline 
	void MyBox::dividedPlane(int n, 
		double x0, double y0, double x1, double y1,
		double nx, double ny, double nz) 
	{
		int countx = 0;	// O que é que está variável faz? contagem de x? o que é que isso significa?
		int county = 0; // O que é que está variável faz? contagem de y? o que é que isso significa?
		double x = x0; 
		double y = y0;
		double stepx = (x1-x0)/(double)n; 
		double stepy = (y1-y0)/(double)n;

		glBegin(GL_QUADS);
		glNormal3d(nx,ny,nz);	// Aqui descobri que nx, ny e nz são realmente as normais! Seria mais fácil compreender o sentido dessas variáveis se fossem renomeadas normalX, normalY, normalZ? ( aumenta apenas 5 letras ao tamanho da palavra )

		// o que é o n? e o que é o countx e county? ainda não sei! :S. Não estou a perceber os ciclos!
		while (countx != n) {
			while (county != n) {
				glVertex3d(x, 0, y);		// A variável tem o nome y, mas é utilizada como z? Seria mais fácil renomear a variável como z? opengl utiliza o z quando devia utilizar o y? ou isto é uma verificação que o implementador reparou nesta situação? Seria melhor não colocar excepções a regra? ou então documentar bem esses casos?
				glVertex3d(x+stepx, 0, y);  // Não consigo ter uma imagem do que resulta o conjunto dos vertices! suponho que um quadrado pois o glBegin está no modo GL_QUADS. Seria melhor se cada instrução glVertex3d indicasse que parte do quadrado é o vertice? 
				glVertex3d(x+stepx, 0, y+stepy);
				glVertex3d(x, 0, y+stepy);
				county++;
				y += stepy;				
			}
			countx++;
			x += stepx;			
			county = 0;
			y = y0;			
		}

		glEnd();
	}

	
	inline
	void MyBox::makeModel() {
		_modelDL = glGenLists(1);
		assert(_modelDL != 0);
		glNewList(_modelDL,GL_COMPILE);

		Material m = MaterialBank::getMaterial(MaterialBank::MATERIAL_COPPER);
		 m.shade(GL_FRONT_AND_BACK);

			// TOP
			glPushMatrix();
				glTranslatef(0,1,0);
				dividedPlane(10, -1,-1,1,1, 0,1,0);
			glPopMatrix();
			// BOTTOM
			glPushMatrix();
				glTranslatef(0,-1,0);
				glRotatef(180, 1,0,0);
				dividedPlane(10, -1,-1,1,1, 0,1,0);
			glPopMatrix();
			// LEFT
			glPushMatrix();
				glTranslatef(0,0,1);
				glRotatef(90,1,0,0);
				dividedPlane(10, -1,-1,1,1, 0,1,0);
			glPopMatrix();
			// RIGHT
			glPushMatrix();
				glTranslatef(0,0,-1);
				glRotatef(-90,1,0,0);
				dividedPlane(10, -1,-1,1,1, 0,1,0);
			glPopMatrix();
			// FRONT
			glPushMatrix();
				glTranslatef(1,0,0);
				glRotatef(-90,0,0,1);
				dividedPlane(10, -1,-1,1,1, 0,1,0);
			glPopMatrix();
			// BACK
			glPushMatrix();
				glTranslatef(-1,0,0);
				glRotatef(90,0,0,1);
				dividedPlane(10, -1,-1,1,1, 0,1,0);
			glPopMatrix();
		glEndList();
	}
	void MyBox::init() {
		_physics.setPosition(3,1.01,-3);
		_physics.setAngularVelocity(1000); //considerar sizeOfBlock/2 em x de 10  
		_physics.setLinearVelocity(100); 
		//_lastposition = _physics.getPosition(); Remove
		makeModel();
	}
	void MyBox::update(unsigned long elapsed_millis) {
		if(_movable && !_isDebug){
			if(cg::KeyBuffer::instance()->isKeyDown('w')) {
				_physics.goAhead();		
		
			}
			if(cg::KeyBuffer::instance()->isKeyDown('s')) {
				
				_physics.goBack();	
		
			}
			if(cg::KeyBuffer::instance()->isKeyDown('a')) {
				_physics.strafeLeft();
			}
			if(cg::KeyBuffer::instance()->isKeyDown('d')) {
				_physics.strafeRight();
			}
			// _lastposition.set(_physics.getPosition()); REMOVE
			MyFPSCamera * fps = (MyFPSCamera *) cg::Registry::instance()->get("FPSCamera");
			fps->setPosition(_physics.getPosition());

			double elapsed_seconds = elapsed_millis / (double)10000;
			_physics.step(elapsed_seconds);
		}
	}

	void MyBox::onMousePassiveMotion(int x, int y) {

	}

	void MyBox::draw() {
		glPushMatrix();
			_physics.applyTransforms();
			glCallList(_modelDL);
		glPopMatrix();
	}

	void MyBox::togglemovable(){
		_movable = !_movable;
	}

	void MyBox::toggleDebugMode() {
		_isDebug = !_isDebug;
	}

}