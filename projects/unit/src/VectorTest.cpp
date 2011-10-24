#include "VectorTest.h"

VectorTest::VectorTest() : Test("VectorTest") {
}

VectorTest::~VectorTest() {
}

void VectorTest::testConstructor0() {
	cg::Vector3d v;
	CHECK(v[0] == 0.0 && v[1] == 0.0 && v[2] == 0.0)
}

void VectorTest::testConstructor1() {
	cg::Vector3d v(1.0);
	CHECK(v[0] == 1.0 && v[1] == 1.0 && v[2] == 1.0)
}

void VectorTest::testConstructor2() {
	double d[3] = {1.0,2.0,3.0};
	cg::Vector3d v(d);
	CHECK(v[0] == 1.0 && v[1] == 2.0 && v[2] == 3.0)
}

void VectorTest::testConstructor3() {
	cg::Vector3d v0(1.0);
	cg::Vector3d v1(v0);
	CHECK(v1[0] == 1.0 && v1[1] == 1.0 && v1[2] == 1.0)
}

void VectorTest::testGet() {
	cg::Vector3d v; 
	v[0] = 1.0; v[1] = 2.0; v[2] = 3.0;
	double *d = v.get();
	CHECK(d[0] == 1.0 && d[1] == 2.0 && d[2] == 3.0)
	const double *c = v.get();
	CHECK(c[0] == 1.0 && c[1] == 2.0 && c[2] == 3.0)
}

void VectorTest::testCompare0() {
	cg::Vector3d v(1.0);
	CHECK(v == 1.0)	
	CHECK(v != 2.0)	
}

void VectorTest::testCompare1() {
	double d[3] = {1.0,2.0,3.0};
	cg::Vector3d v0(d);
	cg::Vector3d v1(d);
	cg::Vector3d v2(1.0);
	CHECK(v0 == v1)	
	CHECK(v0 != v2)
}

void VectorTest::testCompare2() {
	double d0[3] = {0.9,1.9,2.9};
	cg::Vector3d v0(d0);
	double d1[3] = {1.1,2.1,3.1};
	cg::Vector3d v1(d1);
	CHECK(isEqual(v0,v1,0.200001))
	CHECK(isEqual(v0,v1,0.2) == false)
}

void VectorTest::testAssignment0() {
	cg::Vector3d v(2.0);
	v *= 3.0;
	CHECK(v == 6.0)
	v /= 2.0;
	CHECK(v == 3.0)
}

void VectorTest::testAssignment1() {
	cg::Vector3d v0(2.0);
	cg::Vector3d v1(3.0);
	cg::Vector3d v2(2.0);
	v0 *= v1;
	CHECK(v0 == 6.0)
	v0 /= v2;
	CHECK(v0 == 3.0)
	v0 += v2;
	CHECK(v0 == 5.0)
	v0 -= v1;
	CHECK(v0 == 2.0)
}

void VectorTest::testUnary() {
	cg::Vector3d v(1.0);
	CHECK(-v == -1.0)
}

void VectorTest::testBinary() {
	cg::Vector3d v0; v0[0] = 1.0; v0[1] = 3.0; v0[2] = 5.0;
	cg::Vector3d v1; v1[0] = 2.0; v1[1] = 5.0; v1[2] = 8.0;
	cg::Vector3d v;
	v = v0 + v1;
	CHECK(v[0] == 3.0 && v[1] == 8.0 && v[2]== 13.0)
	v = v0 - v1;
	CHECK(v[0] == -1.0 && v[1] == -2.0 && v[2]== -3.0)
	v = v0 * v1;
	CHECK(v[0] == 2.0 && v[1] == 15.0 && v[2] == 40.0)
	v = v0 / v1;
	CHECK(v[0] == 0.5 && v[1] == 0.6 && v[2] == 0.625)
	v = v0 / 2.0;
	CHECK(v[0] == 0.5 && v[1] == 1.5 && v[2] == 2.5)
}