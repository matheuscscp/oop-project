#------------------------------------------------------------------------------
#			Domino RAXASSAUM Makefile
#
#	(2011)	Matheus Pimenta <matheuscscp@gmail.com>
#	(2011)	Alexandre Dantas (kure) <kurebisubarudo@gmail.com>
#	
#
#	Commandlines:
#		V		Verbose mode, off by default.
#				To turn on, add 'V=1' on the commandline OR
#				uncomment the line specified below
#		DESTDIR		Installs the package on a custom directory
#		CXX		Changes the CPP flags used on compilation
#
#	Targets:
#		all:		Compiles the binary
#		clean:		Removes the binary and the *.o files
#		install:	Installs the package
#		uninstall:	Uninstalls the package
#		purge:		Uninstalls the package and removes config files
#		dist:		Creates the 'tarball' for distribution
#
#		run:		Compiles and runs the binary
#		dox:		Generates doxygen documentation
#		doxclean:	Removes the doxygen documentation
#
#------------------------------------------------------------------------------

#	Uncomment to tun on the verbose mode
#V	= 1;

SHELL	= /bin/sh

#-------General Info------------------------------------------------------------
PACKAGE = Domino_RAXASSAUM
VERSION = 1.0

#-------Compile-----------------------------------------------------------------
CXX = g++
CXXFLAGS = -ansi -pedantic -Wall -Wextra -g

EXE	= $(PACKAGE)
CDEBUG	=

BINDIR = bin
DOCDIR = doc
SRCDIR = src

OBJ	= obj/model/peca.o obj/model/jogador.o obj/model/mesa.o obj/view/view.o obj/view/engine.o obj/view/imagem.o obj/controller/main.o obj/controller/partida.o
DEFINES	= -DVERSION=\"$(VERSION)\"


#-------Distribute--------------------------------------------------------------
TARNAME = $(PACKAGE)
DISTDIR = $(TARNAME)-$(VERSION)

#-------Verbose Mode------------------------------------------------------------

ifdef V
MUTE =
VTAG = -v
else
MUTE = @
endif

#-------Standard Makes----------------------------------------------------------

all: $(EXE)
	@echo "* Ready to Play!"

#	To make the executable file
$(EXE): $(OBJ)
	@echo "* Linking..."
	$(MUTE)$(CXX) -o $(BINDIR)/$(EXE) $(OBJ) lib/*/*.so

#	All the object files
obj/%.o: src/%.cpp
	@echo "* Compiling $<..."
	$(MUTE)$(CXX) $(CXXFLAGS) -c $< -o $@

#	Make the 'tarball'
dist: $(DISTDIR).tar.gz


$(DISTDIR).tar.gz: $(DISTDIR)
	$(MUTE)tar czf $(DISTDIR).tar.gz $(DISTDIR)
	$(MUTE)rm -rf $(DISTDIR)
	$(MUTE)cp $(DISTDIR).tar.gz ..
	$(MUTE)rm -f $(DISTDIR).tar.gz

$(DISTDIR):
	$(MUTE)mkdir -p $(DISTDIR)/src $(DISTDIR)/doc
	$(MUTE)mkdir -p $(DISTDIR)/bin $(DISTDIR)/lib
	-$(MUTE)cp Makefile Doxyfile README ChangeLog TODO -t $(DISTDIR)
	-$(MUTE)cp -r src/* $(DISTDIR)/src
	-$(MUTE)cp -r bin/* $(DISTDIR)/bin
	-$(MUTE)cp -r doc/* $(DISTDIR)/doc

#-------Custom Makes-----------------------------------------------------------

# The only difference between those two is that the backup is made
#  on the previous directory, while the above one is temporarily created
#  in the current directory.
# TODO Somehow mix those two
backup:
	$(MUTE)mkdir -p ../$(DISTDIR)/src ../$(DISTDIR)/doc
	$(MUTE)mkdir -p ../$(DISTDIR)/bin ../$(DISTDIR)/lib
	-$(MUTE)cp Makefile Doxyfile README ChangeLog TODO -t ../$(DISTDIR)
	-$(MUTE)cp -r src/* ../$(DISTDIR)/src
	-$(MUTE)cp -r bin/* ../$(DISTDIR)/bin
	-$(MUTE)cp -r doc/* ../$(DISTDIR)/doc

#-------Phonys-----------------------------------------------------------------
run:
	@echo "* Running..."
	$(MUTE)$(BINDIR)/$(EXE)

clean:
	@echo "* Cleaning..."
	$(MUTE)rm $(VTAG) -rf obj/*/* $(BINDIR)/$(EXE) cerr.txt

dox:
	@echo "* Documenting..."
	$(MUTE)doxygen Doxyfile

doxclean:
	@echo "* Removing documentation..."
	$(MUTE)rm -rf $(DOCDIR)/html $(DOCDIR)/latex

.PHONY: clean dox doxclean backup

#------------------------------------------------------------------------------
