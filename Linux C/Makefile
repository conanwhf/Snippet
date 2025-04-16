######################################
# Public parts
######################################
#toolchain
TOOLCHAIN = aarch64-linux-gnu-
CC = $(TOOLCHAIN)g++
LD = $(TOOLCHAIN)ld
AR = $(TOOLCHAIN)ar
RANLIB  = $(TOOLCHAIN)ranlib
STRIP = $(TOOLCHAIN)strip

#source file
SOURCE  := $(wildcard *.c) $(wildcard *.cpp)
OBJS    := $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCE)))
  
#compile and lib parameter
LIBS    := 
LDFLAGS := `pkg-config --libs opencv4` 
DEFINES := `pkg-config --cflags opencv4`
ifdef DEBUG
DEFINES := -DDEBUG $(DEFINES)
endif
INCLUDE := -I.
CFLAGS  := -g -Wall -O3 $(DEFINES) $(INCLUDE)

.PHONY : everything objs clean cleanall rebuild

######################################
# 可执行文件
######################################
TARGET  := test
everything : $(TARGET)
all : $(TARGET)
objs : $(OBJS)
rebuild: cleanall everything

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)
#	$(STRIP) $(TARGET)
clean:
	rm -f $(OBJS) $(TARGET)
	

######################################
#静态链接库
######################################
TARGET  := libtest.a
HEADER	:= test.h
everything : $(TARGET)
all : $(TARGET)
objs : $(OBJS)
rebuild: cleanall everything

$(TARGET) : $(OBJS)
	$(AR) cr $(TARGET) $(OBJS)
	$(RANLIB) $(TARGET)
#	$(STRIP) $(TARGET)
clean :
	rm -fr $(OBJS) $(TARGET)
install:
    cp $(TARGET) $(HEADER) ../libs/


######################################
#动态链接库
######################################
TARGET  := libtest.so
HEADER	:= test.h
everything : $(TARGET)
all : $(TARGET)
objs : $(OBJS)
rebuild: cleanall everything

$(OBJS) : $(SOURCE)
#???	$(CC) $(CFLAGS) -fPIC -c $< -o $@ $(INCLUDE) $(LIBS) 
    $(CC) $(CFLAGS) $(INCLUDE) -c $^
$(TARGET) : $(OBJS)
	$(CC) -shared -o $@ $(OBJS)
#	$(STRIP) $(TARGET)
clean:
	rm -f $(OBJS) $(TARGET)
install:
    cp $(TARGET) $(HEADER) ../libs/
