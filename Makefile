TEST_SRC=normalusage.cpp \
	 empty.cpp \
	 copy.cpp \
	 writing.cpp
TARGET=test
CC=g++
CFLAGS=-std=c++17
LIBPATH=$(HOME)/googletest-test/googletest/build/lib 
LIB=-L$(LIBPATH) -lgtest -lgtest_main
INCLUDE=-I$(HOME)/googletest-test/googletest/googletest/include

all: $(TARGET)

# g++ test.cpp -std=c++17 -L ~/googletest-test/googletest/build/lib -lgtest -lgtest_main ; LD_LIBRARY_PATH=/home/cyl/googletest-test/googletest/build/lib ./a.out
$(TARGET): $(TEST_SRC) ring_iterator.h
	$(CC) $(TEST_SRC) $(CFLAGS) $(INCLUDE) $(LIB) -o $@

run: $(TARGET)
	LD_LIBRARY_PATH=$(LIBPATH) ./$^
