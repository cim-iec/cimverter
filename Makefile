# This is the makefile for the libxml++ parser

# Project Name
PROJECT_NAME = CIM2Mod

# Set compiler
CXX = clang++

# Set BOOST and CTEMPLATE installation directory
CTEMPLATE_INSTALL_DIR=/usr/local
BOOST_INSTALL_DIR=/usr/local
LIBCONFIG_INSTALL_DIR=/usr/local

# CIMParser
CIMPARSER_DIR = /usr/local

# CIM Generated Code
GENERATED_CODE_DIR = /usr/local/include/CIMParser

# Include directories
INCDIR = \
	-I$(GENERATED_CODE_DIR) \
	-I$(BOOST_INSTALL_DIR)/include \
	-I$(CTEMPLATE_INSTALL_DIR)/include \
	-I$(LIBCONFIG_INSTALL_DIR)/include

# Libraries directories
LIBDIR = \
				-L$(CIMPARSER_DIR)/lib \
				-L$(BOOST_INSTALL_DIR)/lib \
                -L$(CTEMPLATE_INSTALL_DIR)/lib \
                -L$(LIBCONFIG_INSTALL_DIR)/lib

LIBS = \
                $(CLANG_LIBS) \
				-lboost_filesystem -lboost_system -lctemplate

# Conifg flags
LIBCONFIGS = \
				-lconfig++

# CFLAGS
CFLAGS = -Wall -Wno-inconsistent-missing-override -g -DDEBUG -std=c++11 \
	$(shell pkg-config --cflags libxml++-2.6)

LDFLAGS = \
		$(LIBDIR) $(LIBS) $(LIBCONFIGS) \
		-L$(CIMPARSER_DIR)/lib -lCIMParser \
	$(shell pkg-config --libs libxml++-2.6)

# Directories
PROJDIR = .
SRCDIR = $(PROJDIR)/src
OBJDIR = $(PROJDIR)/obj
BINDIR = $(PROJDIR)/build/bin
DOCDIR = $(PROJDIR)/documentation
TEMPDIR = $(PROJDIR)/modelica_templates

# Objects
OBJ = $(OBJDIR)/main.o $(OBJDIR)/CIMObjectHandler.o $(OBJDIR)/ConfigManager.o \
	  $(OBJDIR)/ModBaseClass.o $(OBJDIR)/Connection.o $(OBJDIR)/System.o $(OBJDIR)/Slack.o \
	  $(OBJDIR)/Battery.o \
	  $(OBJDIR)/Transformer.o $(OBJDIR)/BusBar.o $(OBJDIR)/ConnectivityNode.o $(OBJDIR)/PQLoad.o \
	  $(OBJDIR)/PiLine.o $(OBJDIR)/RxLine.o $(OBJDIR)/ZLoad.o \
	  $(OBJDIR)/GenericGenerator.o $(OBJDIR)/SolarGenerator.o $(OBJDIR)/WindGenerator.o \
	  $(OBJDIR)/Household.o


BIN = $(BINDIR)/$(PROJECT_NAME)
DOXYFILE = $(PROJDIR)/Doxyfile

# First target which should be called to build
default: directories $(BIN) resource

# Build all including documentation
all: directories $(BIN) documentation resource

# Directories target
.PHONY: directories
directories:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)

# Clean target
.PHONY: clean
clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(BINDIR)
	@rm -rf $(DOCDIR)
	@rm -f $(DOXYFILE)
	@echo Finished cleaning up

# Documentation target
documentation: $(DOCDIR)/html/index.html
$(DOCDIR)/html/index.html: $(SRCDIR)/* $(DOXYFILE)
	doxygen $(DOXYFILE)

# Doxyfile
$(DOXYFILE):
	@echo PROJECT_NAME = "$(PROJECT_NAME)" > $(DOXYFILE)
	@echo OUTPUT_DIRECTORY = $(DOCDIR) >> $(DOXYFILE)
	@echo INPUT = $(SRCDIR) >> $(DOXYFILE)
	@echo GENERATE_LATEX = NO >> $(DOXYFILE)
	@echo QUIET = YES >> $(DOXYFILE)
	@echo Generated Doxyfile

# Pattern rule for source
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@$(CXX) $(CFLAGS) $(INCDIR) -c -o $@ $<
	@echo "Compiled $@"

$(OBJDIR)/%.o: $(SRCDIR)/ModelicaWorkshop/%.cpp
	@$(CXX) $(CFLAGS) $(INCDIR) -c -o $@ $<
	@echo "Compiled $@"

$(OBJDIR)/%.o: $(SRCDIR)/ModelicaWorkshop/ModPowerSystems/%.cpp
	@$(CXX) $(CFLAGS) $(INCDIR) -c -o $@ $<
	@echo "Compiled $@"

$(OBJDIR)/%.o: $(SRCDIR)/ModelicaWorkshop/ModPowerSystems/SinglePhase/Connections/%.cpp
	@$(CXX) $(CFLAGS) $(INCDIR) -c -o $@ $<
	@echo "Compiled $@"

$(OBJDIR)/%.o: $(SRCDIR)/ModelicaWorkshop/ModPowerSystems/SinglePhase/Lines/%.cpp
	@$(CXX) $(CFLAGS) $(INCDIR) -c -o $@ $<
	@echo "Compiled $@"

$(OBJDIR)/%.o: $(SRCDIR)/ModelicaWorkshop/ModPowerSystems/SinglePhase/Loads/%.cpp
	@$(CXX) $(CFLAGS) $(INCDIR) -c -o $@ $<
	@echo "Compiled $@"

$(OBJDIR)/%.o: $(SRCDIR)/ModelicaWorkshop/ModPowerSystems/SinglePhase/Sources/%.cpp
	@$(CXX) $(CFLAGS) $(INCDIR) -c -o $@ $<
	@echo "Compiled $@"

$(OBJDIR)/%.o: $(SRCDIR)/ModelicaWorkshop/ModPowerSystems/SinglePhase/Generations/%.cpp
	@$(CXX) $(CFLAGS) $(INCDIR) -c -o $@ $<
	@echo "Compiled $@"

$(OBJDIR)/%.o: $(SRCDIR)/ModelicaWorkshop/ModPowerSystems/SinglePhase/Transformers/%.cpp
	@$(CXX) $(CFLAGS) $(INCDIR) -c -o $@ $<
	@echo "Compiled $@"

$(OBJDIR)/%.o: $(SRCDIR)/ModelicaWorkshop/ModPowerSystems/SinglePhase/Storage/%.cpp
	@$(CXX) $(CFLAGS) $(INCDIR) -c -o $@ $<
	@echo "Compiled $@"

$(OBJDIR)/%.o: $(SRCDIR)/ModelicaWorkshop/ModPowerSystems/SinglePhase/Households/%.cpp
	@$(CXX) $(CFLAGS) $(INCDIR) -c -o $@ $<
	@echo "Compiled $@"

# Linking pattern
$(BIN): $(OBJ)
	@$(CXX) $(OBJ) $(LDFLAGS) -o $(BIN)
	@echo "Linked all objects to $@"

# Resource
resource:
	@mkdir -p $(BINDIR)/resource
	@cp -f $(TEMPDIR)/*.tpl $(BINDIR)/resource
	@cp -f $(SRCDIR)/*.cfg $(BINDIR)
