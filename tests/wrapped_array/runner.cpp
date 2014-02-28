#include <cstdlib>
#include <gtest/gtest.h>

#include <wrapped_array.h>

using cppgoodies::wrap_array;

TEST(WrapArrayTest, Simple) {
  int values[] = {0, 1, 2, 3, 4, 5};
  auto a = wrap_array(values, 6);
  auto iter = a.begin();
  
  for(int i=0; i<6; i++) {
    EXPECT_EQ(i, *iter);
    iter++;
  }
  EXPECT_EQ(a.end(), iter);
}

int main(int argc, char** argv) {
	srand(time(NULL));  
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
