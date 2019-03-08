#-----------------------------------------------------
# Name:         Jose Munoz
# NetID:        jam151830@utdallas.edu
# Course:       CS4348
# File:         Makefile
# Project:      Project 3 - Disk Allocation Methods 
#---------------------------------------------------

# Set up info for C++ implicit rule
CXX = g++
CXXFLAGS = 
CPPFLAGS = -Wall 
#
# Set up any Linker Flags
LDFLAGS = 
LDLIBS= 

#
# We choose the project name.  This is used in building the file name for the backup target
PROJECTNAME = CS4348.Project3

#
# We choose the source files to include and name the output
SRCS = main.cc Disk.cc

#
# We choose the name of the executable to be created
EXEC = project_3

#
# You normally don't need to change anything below here.
# ======================================================
#
OBJS = $(SRCS:cc=o)

all: $(EXEC)

clean:
	rm -f $(OBJS) *.d *~ \#* $(EXEC)

Makefile: $(SRCS:.cc=.d)

# Pattern for .d files.
%.d:%.cc
	@echo Updating .d Dependency File
	@set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

#  This is a rule to link the files.  Pretty standard
$(EXEC): $(OBJS)
	$(CXX) -o $(EXEC) $(OBJS) $(LDFLAGS) $(LDLIBS) 


# Backup Target
backup: clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!

# Include the dependency files
-include $(SRCS:.cc=.d)
