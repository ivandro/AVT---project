#include "cg/cg.h"

class VectorTest : public cg::Test
{
private:
	void testConstructor0();
	void testConstructor1();
	void testConstructor2();
	void testConstructor3();
	void testGet();
	void testCompare0();
	void testCompare1();
	void testCompare2();
	void testAssignment0();
	void testAssignment1();
	void testUnary();
	void testBinary();

public:
	VectorTest();
	virtual ~VectorTest();
	void test() {
		TEST(testConstructor0)
		TEST(testConstructor1)
		TEST(testConstructor2)
		TEST(testConstructor3)
		TEST(testGet)
		TEST(testCompare0)
		TEST(testCompare1)
		TEST(testCompare2)
		TEST(testAssignment0)
		TEST(testAssignment1)
		TEST(testUnary)
		TEST(testBinary)
		/* TODO */
	}
};