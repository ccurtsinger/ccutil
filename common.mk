INCLUDE_PATHS += $(ROOT)/include $(ROOT)/gtest/include
TESTS_DIR = $(ROOT)/tests
DIRS ?= 

GTEST_VERSION = 1.7.0
GTEST_DIR = $(ROOT)/gtest-$(GTEST_VERSION)
GTEST_LIB = $(GTEST_DIR)/libgtest.a
GTEST_FLAGS = $(GTEST_LIB) -I$(GTEST_DIR)/include

INCLUDE_FLAGS = $(addprefix -I,$(INCLUDE_PATHS))
INCLUDE_FILES = $(wildcard $(ROOT)/include/*.h)

RECURSIVE_TARGETS ?= clean build

$(RECURSIVE_TARGETS)::
	@for dir in $(DIRS); do \
	  $(MAKE) -C $$dir $@; \
	done

$(ROOT)/gtest-$(GTEST_VERSION).zip:
	cd $(ROOT); wget http://googletest.googlecode.com/files/gtest-$(GTEST_VERSION).zip

$(GTEST_DIR): $(ROOT)/gtest-$(GTEST_VERSION).zip
	cd $(ROOT); unzip gtest-$(GTEST_VERSION).zip

$(GTEST_LIB): $(GTEST_DIR)
	cd $(GTEST_DIR); $(CXX) -Iinclude -I. -c src/gtest-all.cc; ar -rv libgtest.a gtest-all.o
