ROOT = ../..
include $(ROOT)/common.mk

test: runner
	@./runner --gtest_output=xml

runner: runner.cpp $(GTEST_LIB) $(INCLUDE_FILES)
	@clang++ --std=c++11 $(INCLUDE_FLAGS) -o runner runner.cpp $(GTEST_FLAGS)
