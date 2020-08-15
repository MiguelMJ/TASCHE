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
      $(addsuffix .o, $(FLEX_SRC))\
      $(addsuffix .o, $(BISON_SRC))
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


#
# Flex and Bison rules
#
%.flex.d: %.cpp
	$(CPP) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@
	@echo '\t$$(CXX) -c $$(CXXFLAGS) $$(RELCFLAGS) -o $$@ $$<' >> $@
%.bison.d: %.cpp
	$(CPP) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@
	@echo '\t$$(CXX) -c $$(CXXFLAGS) $$(RELCFLAGS) -o $$@ $$<' >> $@
%.cpp: %.flex
	$(FLEX) $(FLEXFLAGS) -o $<.cpp $<
%.cpp: %.bison
	$(BISON) $(BISONFLAGS) --defines=include/$(notdir $<).hpp -o $<.cpp $<
#
# Debug rules
#
debug: prep $(DBGEXEC)

$(DBGEXEC): $(DBGOBJ)
	$(CXX) $(CXXFLAGS) $(DBGCFLAGS) $^ -o $(DBGEXEC) $(LINKAGE)

$(DBGDIR)/%.d: %.cpp
	$(CPP) $(CFLAGS) $< -MM -MT $(@:.d=.o) > $@
	@echo '\t$$(CXX) -c $$(CXXFLAGS) $$(DBGCFLAGS) -o $$@ $$<' >> $@
#
# Release rules
#
release: prep $(RELEXEC)

$(RELEXEC): $(RELOBJ)
	$(CXX) $(CXXFLAGS) $(RELCFLAGS) $^ -o $(RELEXEC) $(LINKAGE)

$(RELDIR)/%.d: %.cpp
	$(CPP) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@
	@echo '\t$$(CXX) -c $$(CXXFLAGS) $$(RELCFLAGS) -o $$@ $$<' >> $@

#
# Misc
#
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
