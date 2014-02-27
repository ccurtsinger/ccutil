#include <cstdlib>
#include <gtest/gtest.h>

#include <triemap.h>

using cppgoodies::triemap;

enum { Items = 10000 };

class Element {
public:
	bool value;
	Element(bool value) {
		this->value = value;
	}
};

class triemap_Test : public testing::Test {
protected:
    // Test with a stride of 3 (which doesn't evenly divide 32 or 64)
    // just to be sure the base case works properly
	triemap<int, Element*, 4> set;
	int contents[Items];
	
	virtual void SetUp() {
		// Add random elements to the triemap and an array
		for(size_t i=0; i<Items; i++) {
			int x = rand();
            set[x] = new Element(true);
			contents[i] = x;
		}
	}
};

// Make sure everything in the array is also in the set
TEST_F(triemap_Test, ContainsTest) {
	for(size_t i=0; i<Items; i++) {
		EXPECT_TRUE(set.contains(contents[i]) && set[contents[i]]->value);
	}
}

// Make sure things that aren't in the array are also not in the set
TEST_F(triemap_Test, NotContainsTest) {
	size_t count = 0;
	while(count < Items) {
		int x = rand();
		bool found = false;
		for(size_t i=0; i<Items && !found; i++) {
			if(contents[i] == x) {
				found = true;
			}
		}
		
		if(!found) {
			EXPECT_FALSE(set.contains(x));
			count++;
		}
	}
}

int main(int argc, char** argv) {
	srand(time(NULL));
	
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
