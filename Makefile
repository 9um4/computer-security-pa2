CC = gcc
CFLAGS = -g -I. -Icontrollers -Ihandlers -Ipolicies -Iutils -Imacros -Ienums -Wimplicit-function-declaration
TARGET = mac

# 모든 .c 파일을 대상으로 자동 수집
SRCS = $(shell find . -name '*.c')
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	sudo chown root:root $(TARGET)
	sudo chmod 4755 $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

rebuild: clean all

clean:
	rm -f $(TARGET) $(OBJS) *.log

unsetuid:
	sudo chmod 0755 $(TARGET)

build: rebuild
