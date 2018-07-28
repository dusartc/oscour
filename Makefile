# Directories
DEPDIR=deps
OBJDIR=objs

# Find all sources : let s say we have a src/thing.cpp
# genetic algorithm
GASRC = $(shell find genalgo/sources -name "*.cpp")
GAOTMP = $(patsubst %.cpp,%.o,$(GASRC:genalgo/sources/%=%))
GAOBJS = $(patsubst %,$(OBJDIR)/%,$(GAOTMP))
GADEPS = $(patsubst %.o,$(DEPDIR)/%.d,$(GAOTMP))
# general
GESRC = $(shell find general/sources -name "*.cpp")
GEOTMP = $(patsubst %.cpp,%.o,$(GESRC:general/sources/%=%))
GEOBJS = $(patsubst %,$(OBJDIR)/%,$(GEOTMP))
GEDEPS = $(patsubst %.o,$(DEPDIR)/%.d,$(GEOTMP))
# k-means
KMSRC = $(shell find kmeans/sources -name "*.cpp")
KMOTMP = $(patsubst %.cpp,%.o,$(KMSRC:kmeans/sources/%=%))
KMOBJS = $(patsubst %,$(OBJDIR)/%,$(KMOTMP))
KMDEPS = $(patsubst %.o,$(DEPDIR)/%.d,$(KMOTMP))

DEPS = $(GADEPS) $(GEDEPS) $(KMDEPS)
OBJS = $(GAOBJS) $(GEOBJS) $(KMOBJS)

# CUSRC = $(shell find $(SRCDIR) -name "*.cu")
# CUOTMP = $(patsubst %.cu,%.o,$(CUSRC:$(SRCDIR)/%=%))
# CUOBJS = $(patsubst %,$(OBJDIR)/%,$(CUOTMP))
# CUDEPS = $(patsubst %.o,$(DEPDIR)/%.d,$(CUOTMP))

# Variables
CC = icpc
#CC = g++
CPPFLAGS = -Wall -Wextra -O3 -std=c++11
CPPHEADERS = -Igenalgo/headers -Ikmeans/headers -Igeneral/headers
LIBS = -pthread -lm -fopenmp
DISPLAYLIBS = -lsfml-graphics -lsfml-window -lsfml-system
TESTLIBS = -lgtest -L/usr/lib
ICPCREPORT = -qopt-report=1 -qopt-report-phase=loop,vec,par -qopt-report-annotate=html
# -fopt-info optimized


NVCC = /usr/local/cuda/bin/nvcc
CUDAFLAGS= -std=c++11 -O3 -Iheaders

# Routines
all: $(GAOBJS) $(KMOBJS) $(GEOBJS)
	@echo Building the executable...
	$(CC) -o main $(GAOBJS) $(KMOBJS) $(GEOBJS) $(LIBS) $(DISPLAYLIBS) $(CPPHEADERS) $(CPPFLAGS)

test: $(GAOBJS) $(KMOBJS)
	@echo Building performance test...
	$(CC) general/tests/perftest.cpp -o test $(GAOBJS) $(KMOBJS) $(LIBS) $(CPPHEADERS) $(CPPFLAGS) $(TESTLIBS)
	@echo Executing performance test
	./test

kmeans: $(KMOBJS)
	@echo k-means sources built

kmeans_test: kmeans genalgo
	@echo Building k-means tests
	$(CC) kmeans/tests/maintest.cpp -o test $(CPPFLAGS) $(CPPHEADERS) $(KMOBJS) $(GAOBJS) $(LIBS) $(TESTLIBS)
	@echo Executing k-means tests
	./test

genalgo: $(GAOBJS)
	@echo Genetic algorithm sources built

genalgo_test: genalgo
	@echo Building genetic algorithm tests
	$(CC) genalgo/tests/maintest.cpp -o test $(CPPFLAGS) $(CPPHEADERS) $(GAOBJS) $(LIBS) $(TESTLIBS)
	@echo Executing genetic algorithm tests
	./test

general: $(GEOBJS)
	@echo Display and simulation sources built




clean:
	@echo Clearing...
	rm -fr $(OBJDIR)/ $(DEPDIR)/

.PHONY: all clean test

-include $(DEPS) # $(CUDEPS)

# $(OBJDIR)/%.o: $(SRCDIR)/%.cu
# 	@echo Building cuda sources
# 	mkdir -p $(dir $@)
# 	mkdir -p $(DEPDIR)/$(dir $(@:$(OBJDIR)/%=%))
# 	$(eval CU = $(shell find $(SRCDIR)/$(dir $*) -name "$(notdir $*).cu"))
# 	$(NVCC) -c $(CUDAFLAGS) $(CU) -o $@ $(LIBS)
# 	$(NVCC) -M $(CUDAFLAGS) $(CU) $(LIBS) > $(DEPDIR)/$*.d

$(OBJDIR)/%.o: kmeans/sources/%.cpp
	@echo Building c++ sources
	mkdir -p $(dir $@)
	mkdir -p $(DEPDIR)/$(dir $(@:$(OBJDIR)/%=%))
	$(eval CPP = $(shell find kmeans/sources/$(dir $*) -name "$(notdir $*).cpp"))
	$(CC) -c $(CPPFLAGS) $(CPPHEADERS) $(CPP) -o $@ $(LIBS) $(ICPCREPORT)
	$(CC) -MM $(CPPFLAGS) $(CPPHEADERS) $(CPP) $(LIBS) > $(DEPDIR)/$*.d

$(OBJDIR)/%.o: genalgo/sources/%.cpp
	@echo Building c++ sources
	mkdir -p $(dir $@)
	mkdir -p $(DEPDIR)/$(dir $(@:$(OBJDIR)/%=%))
	$(eval CPP = $(shell find genalgo/sources/$(dir $*) -name "$(notdir $*).cpp"))
	$(CC) -c $(CPPFLAGS) $(CPPHEADERS) $(CPP) -o $@ $(LIBS) $(ICPCREPORT)
	$(CC) -MM $(CPPFLAGS) $(CPPHEADERS) $(CPP) $(LIBS) > $(DEPDIR)/$*.d

$(OBJDIR)/%.o: general/sources/%.cpp
	@echo Building c++ sources
	mkdir -p $(dir $@)
	mkdir -p $(DEPDIR)/$(dir $(@:$(OBJDIR)/%=%))
	$(eval CPP = $(shell find general/sources/$(dir $*) -name "$(notdir $*).cpp"))
	$(CC) -c $(CPPFLAGS) $(CPPHEADERS) $(CPP) -o $@ $(LIBS) $(ICPCREPORT)
	$(CC) -MM $(CPPFLAGS) $(CPPHEADERS) $(CPP) $(LIBS) > $(DEPDIR)/$*.d
