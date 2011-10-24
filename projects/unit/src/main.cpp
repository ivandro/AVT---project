#include "cg/cg.h"

#include <iostream>
#include "VectorTest.h"

int main(int argc, char** argv) {
	cg::TestSuite *ts = new cg::TestSuite("CglibTestSuite");
	ts->addTest(new VectorTest());
	ts->run();
	return 0;
}