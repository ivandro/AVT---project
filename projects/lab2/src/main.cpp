#include "cg/cg.h"
#include "MyApp.h"

int main(int argc, char** argv) {
	cg::Manager::instance()->runApp(new lab2::MyApp(),60,argc,argv);
	return 0;
}