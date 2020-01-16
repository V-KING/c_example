
target = a.out

SRC_DIR = .
CC=gcc
CXX=g++
Q=@
NQ=echo

# !!!
INCLUDE = -I./
LDFLAGS = -L/usr/local/lib -lprotobuf  \
	-lpthread \
	-Wl,-rpath=/usr/local/lib

CFLAGS = -std=gnu9x -g $(INCLUDE) -w
CXXFLAGS = -std=c++11 -g $(INCLUDE) -w
OBJS=main.o addressbook.pb.o

all: $(target)

gen_protobuf:
	protoc -I=$(SRC_DIR) --cpp_out=$(SRC_DIR) $(SRC_DIR)/addressbook.proto
	
$(target):$(OBJS)
	@$(NQ) executable file:  $(target)
	$(Q)$(CXX) $(CFLAGS) $^ -o $(target) $(LDFLAGS)

%.o: %.c
	@$(NQ) generate:   $@
	$(Q)$(CC) $(CFLAGS) -c $< -o $@
%.o: %.cc
	@$(NQ) generate:   $@
	$(Q)$(CXX) $(CXXFLAGS) -c $< -o $@
%.o: %.cpp
	@$(NQ) generate:   $@
	$(Q)$(CXX) $(CXXFLAGS) -c $< -o $@
	
clean:
	rm  *.o $(target)