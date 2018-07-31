# Directories
DEPDIR=deps
OBJDIR=objs

# Find all sources : let s say we have a src/thing.cpp
# genetic algorithm
GASRC = $(shell find genalgo/sources -name "*.cpp")
GAOTMP = $(patsubst %.cpp,%.o,$(GASRC:genalgo/sources/%=%))
GAOBJS = $(patsubst %,$(OBJDIR)/%,$(GAOTMP))
GADEPS = $(patsubst %.o,$(DEPDIR)/%.d,$(GAOTMP))
# neuralnetwork
NNSRC = $(shell find neuralnetwork/sources -name "*.cpp")
NNOTMP = $(patsubst %.cpp,%.o,$(NNSRC:neuralnetwork/sources/%=%))
NNOBJS = $(patsubst %,$(OBJDIR)/%,$(NNOTMP))
NNDEPS = $(patsubst %.o,$(DEPDIR)/%.d,$(NNOTMP))
# jeu
J1SRC = $(shell find jeu/sources -name "*.cpp")
J1OTMP = $(patsubst %.cpp,%.o,$(J1SRC:jeu/sources/%=%))
J1OBJS = $(patsubst %,$(OBJDIR)/%,$(J1OTMP))
J1DEPS = $(patsubst %.o,$(DEPDIR)/%.d,$(J1OTMP))

DEPS = $(GADEPS) $(GNNDEPS) $(J1DEPS)
OBJS = $(GAOBJS) $(GNNOBJS) $(J1OBJS)

# Variables
CC = g++
CPPFLAGS = -Wall -Wextra -O3 -std=c++11
CPPHEADERS = -Igenalgo/headers -Ineuralnetwork/headers -Ijeu/headers
LIBS = -pthread -lm -fopenmp
TESTLIBS = -lgtest -L/usr/lib

# Routines
all: $(GAOBJS) $(NNOBJS) $(J1OBJS)
	@echo Building the executable...
	$(CC) -o main $(GAOBJS) $(NNOBJS) $(J1OBJS) $(LIBS) $(CPPHEADERS) $(CPPFLAGS)

test: $(GAOBJS) $(KMOBJS)
	@echo Building performance test...
	$(CC) general/tests/perftest.cpp -o test $(GAOBJS) $(KMOBJS) $(LIBS) $(CPPHEADERS) $(CPPFLAGS) $(TESTLIBS)
	@echo Executing performance test
	./test



genalgo: $(GAOBJS)
	@echo Genetic algorithm sources built

genalgo_test: genalgo
	@echo Building genetic algorithm tests
	$(CC) genalgo/tests/maintest.cpp -o test $(CPPFLAGS) $(CPPHEADERS) $(GAOBJS) $(LIBS) $(TESTLIBS)
	@echo Executing genetic algorithm tests
	./test

neuralnetwork: $(NNOBJS)
	@echo Display and simulation sources built




clean:
	@echo Clearing...
	rm -fr $(OBJDIR)/ $(DEPDIR)/

.PHONY: all clean test

-include $(DEPS)

$(OBJDIR)/%.o: neuralnetwork/sources/%.cpp
	@echo Building neural network c++ sources
	mkdir -p $(dir $@)
	mkdir -p $(DEPDIR)/$(dir $(@:$(OBJDIR)/%=%))
	$(eval CPP = $(shell find neuralnetwork/sources/$(dir $*) -name "$(notdir $*).cpp"))
	$(CC) -c $(CPPFLAGS) $(CPPHEADERS) $(CPP) -o $@ $(LIBS)
	$(CC) -MM $(CPPFLAGS) $(CPPHEADERS) $(CPP) $(LIBS) > $(DEPDIR)/$*.d

$(OBJDIR)/%.o: genalgo/sources/%.cpp
	@echo Building genetic algorithm c++ sources
	mkdir -p $(dir $@)
	mkdir -p $(DEPDIR)/$(dir $(@:$(OBJDIR)/%=%))
	$(eval CPP = $(shell find genalgo/sources/$(dir $*) -name "$(notdir $*).cpp"))
	$(CC) -c $(CPPFLAGS) $(CPPHEADERS) $(CPP) -o $@ $(LIBS)
	$(CC) -MM $(CPPFLAGS) $(CPPHEADERS) $(CPP) $(LIBS) > $(DEPDIR)/$*.d

$(OBJDIR)/%.o: jeu/sources/%.cpp
	@echo Building game c++ sources
	mkdir -p $(dir $@)
	mkdir -p $(DEPDIR)/$(dir $(@:$(OBJDIR)/%=%))
	$(eval CPP = $(shell find jeu/sources/$(dir $*) -name "$(notdir $*).cpp"))
	$(CC) -c $(CPPFLAGS) $(CPPHEADERS) $(CPP) -o $@ $(LIBS)
	$(CC) -MM $(CPPFLAGS) $(CPPHEADERS) $(CPP) $(LIBS) > $(DEPDIR)/$*.d
