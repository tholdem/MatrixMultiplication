###########################################################################
## Makefile generated for MATLAB file/project 'cubicRegScript'. 
## 
## Makefile     : cubicRegScript_rtw.mk
## Generated on : Wed Jul 15 15:01:46 2020
## MATLAB Coder version: 4.1 (R2018b)
## 
## Build Info:
## 
## Final product: /home/zhwa9431/matrixMulti/batchScripts/cubicRegScript
## Product type : executable
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# COMPUTER                Computer type. See the MATLAB "computer" command.

PRODUCT_NAME              = cubicRegScript
MAKEFILE                  = cubicRegScript_rtw.mk
COMPUTER                  = GLNXA64
MATLAB_ROOT               = /curc/sw/matlab/R2018b
MATLAB_BIN                = /curc/sw/matlab/R2018b/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/glnxa64
MASTER_ANCHOR_DIR         = 
START_DIR                 = /home/zhwa9431/matrixMulti/batchScripts/codegen/exe/cubicRegScript
ARCH                      = glnxa64
RELATIVE_PATH_TO_ANCHOR   = .
C_STANDARD_OPTS           = -std=c99 -pedantic -fwrapv
CPP_STANDARD_OPTS         = -fwrapv

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          GNU gcc/g++ | gmake (64-bit Linux)
# Supported Version(s):    
# ToolchainInfo Version:   R2018b
# Specification Revision:  1.0
# 
#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# C_STANDARD_OPTS
# CPP_STANDARD_OPTS

#-----------
# MACROS
#-----------

WARN_FLAGS         = -Wall -W -Wwrite-strings -Winline -Wstrict-prototypes -Wnested-externs -Wpointer-arith -Wcast-align
WARN_FLAGS_MAX     = $(WARN_FLAGS) -Wcast-qual -Wshadow
CPP_WARN_FLAGS     = -Wall -W -Wwrite-strings -Winline -Wpointer-arith -Wcast-align
CPP_WARN_FLAGS_MAX = $(CPP_WARN_FLAGS) -Wcast-qual -Wshadow

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: GNU C Compiler
CC = gcc

# Linker: GNU Linker
LD = g++

# C++ Compiler: GNU C++ Compiler
CPP = g++

# C++ Linker: GNU C++ Linker
CPP_LD = g++

# Archiver: GNU Archiver
AR = ar

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)/mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%/bin/glnxa64
MAKE = "$(MAKE_PATH)/gmake"


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -g
C_OUTPUT_FLAG       = -o
LDDEBUG             = -g
OUTPUT_FLAG         = -o
CPPDEBUG            = -g
CPP_OUTPUT_FLAG     = -o
CPPLDDEBUG          = -g
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG =
MEX_DEBUG           = -g
RM                  = @rm -f
ECHO                = @echo
MV                  = @mv
RUN                 =

#----------------------------------------
# "Faster Builds" Build Configuration
#----------------------------------------

ARFLAGS              = ruvs
CFLAGS               = -c $(C_STANDARD_OPTS) -fPIC \
                       -O0
CPPFLAGS             = -c $(CPP_STANDARD_OPTS) -fPIC \
                       -O0
CPP_LDFLAGS          = -Wl,-rpath,"$(MATLAB_ARCH_BIN)",-L"$(MATLAB_ARCH_BIN)"
CPP_SHAREDLIB_LDFLAGS  = -shared -Wl,-rpath,"$(MATLAB_ARCH_BIN)",-L"$(MATLAB_ARCH_BIN)" -Wl,--no-undefined
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = -Wl,-rpath,"$(MATLAB_ARCH_BIN)",-L"$(MATLAB_ARCH_BIN)"
MEX_CPPFLAGS         = -R2018a -MATLAB_ARCH=$(ARCH) $(INCLUDES) \
                         \
                       CXXOPTIMFLAGS="$(C_STANDARD_OPTS)  \
                       -O0 \
                        $(DEFINES)" \
                         \
                       -silent
MEX_CPPLDFLAGS       = LDFLAGS=='$$LDFLAGS'
MEX_CFLAGS           = -R2018a -MATLAB_ARCH=$(ARCH) $(INCLUDES) \
                         \
                       COPTIMFLAGS="$(C_STANDARD_OPTS)  \
                       -O0 \
                        $(DEFINES)" \
                         \
                       -silent
MEX_LDFLAGS          = LDFLAGS=='$$LDFLAGS'
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -shared -Wl,-rpath,"$(MATLAB_ARCH_BIN)",-L"$(MATLAB_ARCH_BIN)" -Wl,--no-undefined

#--------------------
# File extensions
#--------------------

H_EXT               = .h
OBJ_EXT             = .o
C_EXT               = .c
EXE_EXT             =
SHAREDLIB_EXT       = .so
HPP_EXT             = .hpp
OBJ_EXT             = .o
CPP_EXT             = .cpp
EXE_EXT             =
SHAREDLIB_EXT       = .so
STATICLIB_EXT       = .a
MEX_EXT             = .mexa64
MAKE_EXT            = .mk


###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = /home/zhwa9431/matrixMulti/batchScripts/cubicRegScript
PRODUCT_TYPE = "executable"
BUILD_TYPE = "Executable"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(START_DIR) -I/home/zhwa9431/matrixMulti/batchScripts -I$(MATLAB_ROOT)/extern/include -I$(MATLAB_ROOT)/simulink/include -I$(MATLAB_ROOT)/rtw/c/src -I$(MATLAB_ROOT)/rtw/c/src/ext_mode/common -I$(MATLAB_ROOT)/rtw/c/ert -I/curc/sw/intel/17.4/mkl/include

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_ = -DMODEL=cubicRegScript -DHAVESTDIO -DUSE_RTMODEL -DUNIX -DHAVE_LAPACK_CONFIG_H -DLAPACK_COMPLEX_STRUCTURE -DLAPACK_ILP64
DEFINES_STANDARD = -DMODEL=cubicRegScript -DHAVESTDIO -DUSE_RTMODEL -DUNIX

DEFINES = $(DEFINES_) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/cubicRegScript_rtwutil.c $(START_DIR)/cubicRegScript_data.c $(START_DIR)/cubicRegScript_initialize.c $(START_DIR)/cubicRegScript_terminate.c $(START_DIR)/cubicRegScript.c $(START_DIR)/eml_rand_mt19937ar_stateful.c $(START_DIR)/randn.c $(START_DIR)/cubicReg4Coder.c $(START_DIR)/ktensorOptimized.c $(START_DIR)/khatriraoOptimized.c $(START_DIR)/kron.c $(START_DIR)/norm.c $(START_DIR)/cat.c $(START_DIR)/tensorHessianOptimized.c $(START_DIR)/triu.c $(START_DIR)/eye.c $(START_DIR)/sum.c $(START_DIR)/eig.c $(START_DIR)/anyNonFinite.c $(START_DIR)/schur.c $(START_DIR)/xgehrd.c $(START_DIR)/xhseqr.c $(START_DIR)/xdlanv2.c $(START_DIR)/diag.c $(START_DIR)/ARCSubproblem.c $(START_DIR)/mldivide.c $(START_DIR)/xgetrf.c $(START_DIR)/xgeqp3.c $(START_DIR)/dot.c $(START_DIR)/fclose.c $(START_DIR)/fileManager.c $(START_DIR)/fwrite.c $(START_DIR)/cubicRegScript_emxutil.c $(START_DIR)/rt_nonfinite.c $(START_DIR)/rtGetNaN.c $(START_DIR)/rtGetInf.c /home/zhwa9431/matrixMulti/batchScripts/main.c

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = cubicRegScript_rtwutil.o cubicRegScript_data.o cubicRegScript_initialize.o cubicRegScript_terminate.o cubicRegScript.o eml_rand_mt19937ar_stateful.o randn.o cubicReg4Coder.o ktensorOptimized.o khatriraoOptimized.o kron.o norm.o cat.o tensorHessianOptimized.o triu.o eye.o sum.o eig.o anyNonFinite.o schur.o xgehrd.o xhseqr.o xdlanv2.o diag.o ARCSubproblem.o mldivide.o xgetrf.o xgeqp3.o dot.o fclose.o fileManager.o fwrite.o cubicRegScript_emxutil.o rt_nonfinite.o rtGetNaN.o rtGetInf.o main.o

ALL_OBJS = $(OBJS)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = /curc/sw/intel/17.4/mkl/lib/intel64/libmkl_intel_ilp64.so

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS =  -lm

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_ = -DMKL_ILP64
CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_) $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_ = -DMKL_ILP64
CPPFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CPPFLAGS += $(CPPFLAGS_) $(CPPFLAGS_BASIC)

#---------------
# C++ Linker
#---------------

CPP_LDFLAGS_ = -L/curc/sw/intel/17.4/mkl/lib/intel64 -L/curc/sw/intel/17.4/lib/intel64 -liomp5 -lmkl_intel_ilp64 -lmkl_intel_thread -lmkl_core -lpthread

CPP_LDFLAGS += $(CPP_LDFLAGS_)

#------------------------------
# C++ Shared Library Linker
#------------------------------

CPP_SHAREDLIB_LDFLAGS_ = -L/curc/sw/intel/17.4/mkl/lib/intel64 -L/curc/sw/intel/17.4/lib/intel64 -liomp5 -lmkl_intel_ilp64 -lmkl_intel_thread -lmkl_core -lpthread

CPP_SHAREDLIB_LDFLAGS += $(CPP_SHAREDLIB_LDFLAGS_)

#-----------
# Linker
#-----------

LDFLAGS_ = -L/curc/sw/intel/17.4/mkl/lib/intel64 -L/curc/sw/intel/17.4/lib/intel64 -liomp5 -lmkl_intel_ilp64 -lmkl_intel_thread -lmkl_core -lpthread

LDFLAGS += $(LDFLAGS_)

#--------------------------
# Shared Library Linker
#--------------------------

SHAREDLIB_LDFLAGS_ = -L/curc/sw/intel/17.4/mkl/lib/intel64 -L/curc/sw/intel/17.4/lib/intel64 -liomp5 -lmkl_intel_ilp64 -lmkl_intel_thread -lmkl_core -lpthread

SHAREDLIB_LDFLAGS += $(SHAREDLIB_LDFLAGS_)

###########################################################################
## INLINED COMMANDS
###########################################################################

###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build buildobj clean info prebuild download execute


all : build
	@echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


buildobj : prebuild $(OBJS) $(PREBUILT_OBJS) $(LIBS)
	@echo "### Successfully generated all binary outputs."


prebuild : 


download : build


execute : download
	@echo "### Invoking postbuild tool "Execute" ..."
	$(EXECUTE) $(EXECUTE_FLAGS)
	@echo "### Done invoking postbuild tool."


###########################################################################
## FINAL TARGET
###########################################################################

#-------------------------------------------
# Create a standalone executable            
#-------------------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS) $(LIBS)
	@echo "### Creating standalone executable "$(PRODUCT)" ..."
	$(LD) $(LDFLAGS) -o $(PRODUCT) $(OBJS) $(LIBS) $(SYSTEM_LIBS) $(TOOLCHAIN_LIBS)
	@echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.o : %.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : %.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/rtw/c/src/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/rtw/c/src/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : /home/zhwa9431/matrixMulti/batchScripts/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : /home/zhwa9431/matrixMulti/batchScripts/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@echo "### PRODUCT = $(PRODUCT)"
	@echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@echo "### BUILD_TYPE = $(BUILD_TYPE)"
	@echo "### INCLUDES = $(INCLUDES)"
	@echo "### DEFINES = $(DEFINES)"
	@echo "### ALL_SRCS = $(ALL_SRCS)"
	@echo "### ALL_OBJS = $(ALL_OBJS)"
	@echo "### LIBS = $(LIBS)"
	@echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	@echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@echo "### CFLAGS = $(CFLAGS)"
	@echo "### LDFLAGS = $(LDFLAGS)"
	@echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@echo "### CPPFLAGS = $(CPPFLAGS)"
	@echo "### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	@echo "### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	@echo "### ARFLAGS = $(ARFLAGS)"
	@echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	@echo "### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@echo "### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	$(RM) $(PRODUCT)
	$(RM) $(ALL_OBJS)
	$(ECHO) "### Deleted all derived files."


