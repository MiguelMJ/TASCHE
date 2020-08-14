EXEC = tasche
CXX = g++
CXXFLAGS = -std=c++11 -Wall -fmax-errors=3 $(INCLUDES) $(LINKDIRS)
CC = $(CXX)
CFLAGS = $(CXXFLAGS)

FLEX = flex
FLEXFLAGS = --nounistd
BISON = bison
BISONFLAGS = 

INCLUDES = -Iinclude -Ithirdparty
LINKDIRS = 
LDFLAGS = 
LIBS =
LINKAGE = $(LIBS) $(LDFLAGS)
CPP_SRC = $(EXEC).cpp $ $(wildcard src/*.cpp)
FLEX_SRC = $(wildcard src/*flex)
BISON_SRC = $(wildcard src/*bison)

OBJ = $(CPP_SRC:%.cpp=%.o)\
      $(FLEX_SRC:%.cpp=%.o)\
      $(BISON_SRC:%.cpp=%.o)
DEP = $(OBJ:%.o=%.d)

#
# Debug build settings
#
DBGDIR = debug
DBGEXEC = $(DBGDIR)/$(EXEC)
DBGOBJ = $(addprefix $(DBGDIR)/, $(OBJ))
DBGDEP = $(addprefix $(DBGDIR)/, $(DEP))
DBGCFLAGS = -g -O0 -DDEBUG

#
# Release build settings
#
RELDIR = release
RELEXEC = $(RELDIR)/$(EXEC)
RELOBJ = $(addprefix $(RELDIR)/, $(OBJ))
RELDEP = $(addprefix $(RELDIR)/, $(DEP))
RELFLAGS = -O3 -DNDEBUG

.PHONY: all debug prep release clean clean-release clean-debug docs

all: release

-include $(DBGDEP)
-include $(RELDEP)

debug: prep $(DBGEXEC)

$(DBGEXEC): $(DBGOBJ)
	$(CXX) $(CXXFLAGS) $(DBGCFLAGS) $^ -o $(DBGEXEC) $(LINKAGE)

$(DBGDIR)/%.d: %.cpp
	$(CPP) $(CFLAGS) $< -MM -MT $(@:.d=.o) > $@
	@echo '\t$$(CXX) -c $$(CXXFLAGS) $$(DBGCFLAGS) -o $$@ $$<' >> $@

release: prep $(RELEXEC)

$(RELEXEC): $(RELOBJ)
	$(CXX) $(CXXFLAGS) $(RELCFLAGS) $^ -o $(RELEXEC) $(LINKAGE)

$(RELDIR)/%.d: %.cpp
	$(CPP) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@
	@echo '\t$$(CXX) -c $$(CXXFLAGS) $$(RELCFLAGS) -o $$@ $$<' >> $@

prep:	
	@mkdir -p $(DBGDIR)/src
	@mkdir -p $(RELDIR)/src
clean: clean-release clean-debug

clean-release:
	@rm -f -r $(RELDIR)
	@mkdir -p $(RELDIR)/src
clean-debug:
	@rm -f -r $(DBGDIR)
	@mkdir -p $(DBGDIR)/src
