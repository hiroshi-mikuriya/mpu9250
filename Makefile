CXX	   := gcc
CXXFLAGS  := -Wall -std=c99

TARGET	:= mpu9250
PROJ_ROOT := $(realpath .)
SRCS	  := main.c i2c.c spi.c mpu9250i2c.c mpu9250spi.c
OBJS	  := $(SRCS:.c=.o)

### Rules ######################################################################

.PHONY: all
all: $(TARGET)

.PHONY: make
make: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LIBS)

.PHONY: clean
clean:
	$(RM) -f $(TARGET) *.o

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $<
