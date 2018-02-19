#include "gtest/gtest.h"

class Calc {
public:
	int add(int x, int y) {
		return x + y;
	}
};

namespace {

class MyAddTest : public ::testing::Test {
protected:
	Calc mycalc;

};

TEST_F(MyAddTest, DoAddPositive) {
	ASSERT_EQ( 2, mycalc.add(1,1));
}

}
