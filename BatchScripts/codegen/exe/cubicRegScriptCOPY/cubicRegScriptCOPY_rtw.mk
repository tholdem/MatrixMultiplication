###########################################################################
## Makefile generated for MATLAB file/project 'cubicRegScriptCOPY'. 
## 
## Makefile     : cubicRegScriptCOPY_rtw.mk
## Generated on : Wed Jul 08 16:30:08 2020
## MATLAB Coder version: 5.0 (R2020a)
## 
## Build Info:
## 
## Final product: C:/Users/bryan/Documents/GitHub/MatrixMultiplication/BatchScripts/cubicRegScriptCOPY.exe
## Product type : executable
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# COMPILER_COMMAND_FILE   Compiler command listing model reference header paths
# CMD_FILE                Command file

PRODUCT_NAME              = cubicRegScriptCOPY
MAKEFILE                  = cubicRegScriptCOPY_rtw.mk
MATLAB_ROOT               = C:/PROGRA~1/MATLAB/R2020a
MATLAB_BIN                = C:/PROGRA~1/MATLAB/R2020a/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/win64
MASTER_ANCHOR_DIR         = 
START_DIR                 = C:/Users/bryan/Documents/GitHub/MatrixMultiplication/BatchScripts/codegen/exe/cubicRegScriptCOPY
TGT_FCN_LIB               = None
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 
RELATIVE_PATH_TO_ANCHOR   = .
COMPILER_COMMAND_FILE     = cubicRegScriptCOPY_rtw_comp.rsp
CMD_FILE                  = cubicRegScriptCOPY_rtw.rsp
C_STANDARD_OPTS           = -fwrapv
CPP_STANDARD_OPTS         = -fwrapv

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          MinGW64 | gmake (64-bit Windows)
# Supported Version(s):    6.x
# ToolchainInfo Version:   2020a
# Specification Revision:  1.0
# 
#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# C_STANDARD_OPTS
# CPP_STANDARD_OPTS
# MINGW_ROOT
# MINGW_C_STANDARD_OPTS

#-----------
# MACROS
#-----------

WARN_FLAGS            = -Wall -W -Wwrite-strings -Winline -Wstrict-prototypes -Wnested-externs -Wpointer-arith -Wcast-align
WARN_FLAGS_MAX        = $(WARN_FLAGS) -Wcast-qual -Wshadow
CPP_WARN_FLAGS        = -Wall -W -Wwrite-strings -Winline -Wpointer-arith -Wcast-align
CPP_WARN_FLAGS_MAX    = $(CPP_WARN_FLAGS) -Wcast-qual -Wshadow
MW_EXTERNLIB_DIR      = $(MATLAB_ROOT)/extern/lib/win64/mingw64
SHELL                 = %SystemRoot%/system32/cmd.exe

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = -lws2_32

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: GNU C Compiler
CC_PATH = $(MINGW_ROOT)
CC = "$(CC_PATH)/gcc"

# Linker: GNU Linker
LD_PATH = $(MINGW_ROOT)
LD = "$(LD_PATH)/g++"

# C++ Compiler: GNU C++ Compiler
CPP_PATH = $(MINGW_ROOT)
CPP = "$(CPP_PATH)/g++"

# C++ Linker: GNU C++ Linker
CPP_LD_PATH = $(MINGW_ROOT)
CPP_LD = "$(CPP_LD_PATH)/g++"

# Archiver: GNU Archiver
AR_PATH = $(MINGW_ROOT)
AR = "$(AR_PATH)/ar"

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)/mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%/bin/win64
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
RM                  = @del
ECHO                = @echo
MV                  = @move
RUN                 =

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              = ruvs
CFLAGS               = -c $(MINGW_C_STANDARD_OPTS) -m64 \
                       -O3 -fno-loop-optimize -fno-aggressive-loop-optimizations
CPPFLAGS             = -c $(CPP_STANDARD_OPTS) -m64 -std=c++11 \
                       -O3 -fno-loop-optimize -fno-aggressive-loop-optimizations
CPP_LDFLAGS          = -Wl,-rpath,"$(MATLAB_ARCH_BIN)",-L"$(MATLAB_ARCH_BIN)" -static -m64
CPP_SHAREDLIB_LDFLAGS  = -shared -Wl,-rpath,"$(MATLAB_ARCH_BIN)",-L"$(MATLAB_ARCH_BIN)" -Wl,--no-undefined \
                         -Wl,--out-implib,$(basename $(PRODUCT)).lib
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = -Wl,-rpath,"$(MATLAB_ARCH_BIN)",-L"$(MATLAB_ARCH_BIN)" -static -m64
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -shared -Wl,-rpath,"$(MATLAB_ARCH_BIN)",-L"$(MATLAB_ARCH_BIN)" -Wl,--no-undefined \
                       -Wl,--out-implib,$(basename $(PRODUCT)).lib



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = C:/Users/bryan/Documents/GitHub/MatrixMultiplication/BatchScripts/cubicRegScriptCOPY.exe
PRODUCT_TYPE = "executable"
BUILD_TYPE = "Executable"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = 

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_ = -DHAVE_LAPACK_CONFIG_H -DLAPACK_COMPLEX_STRUCTURE -DLAPACK_ILP64 -D__USE_MINGW_ANSI_STDIO=1 -DMODEL=cubicRegScriptCOPY
DEFINES_CUSTOM = 
DEFINES_STANDARD = -DMODEL=cubicRegScriptCOPY

DEFINES = $(DEFINES_) $(DEFINES_CUSTOM) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/rt_nonfinite.c $(START_DIR)/rtGetNaN.c $(START_DIR)/rtGetInf.c C:/Users/bryan/Documents/GitHub/MatrixMultiplication/BatchScripts/main.c $(START_DIR)/cubicRegScriptCOPY_rtwutil.c $(START_DIR)/cubicRegScriptCOPY_data.c $(START_DIR)/cubicRegScriptCOPY_initialize.c $(START_DIR)/cubicRegScriptCOPY_terminate.c $(START_DIR)/cubicRegScriptCOPY.c $(START_DIR)/eml_rand_mt19937ar_stateful.c $(START_DIR)/randn.c $(START_DIR)/cubicRegCOPY.c $(START_DIR)/norm.c $(START_DIR)/evalPenaltyFcn_CP.c $(START_DIR)/sum.c $(START_DIR)/minOrMax.c $(START_DIR)/eig.c $(START_DIR)/ishermitian.c $(START_DIR)/triu.c $(START_DIR)/tensorHessianOptimized.c $(START_DIR)/cat.c $(START_DIR)/eye.c $(START_DIR)/kron.c $(START_DIR)/ARCSubproblem.c $(START_DIR)/relop.c $(START_DIR)/mldivide.c $(START_DIR)/roots.c $(START_DIR)/cubicRegScriptCOPY_emxutil.c

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = rt_nonfinite.obj rtGetNaN.obj rtGetInf.obj main.obj cubicRegScriptCOPY_rtwutil.obj cubicRegScriptCOPY_data.obj cubicRegScriptCOPY_initialize.obj cubicRegScriptCOPY_terminate.obj cubicRegScriptCOPY.obj eml_rand_mt19937ar_stateful.obj randn.obj cubicRegCOPY.obj norm.obj evalPenaltyFcn_CP.obj sum.obj minOrMax.obj eig.obj ishermitian.obj triu.obj tensorHessianOptimized.obj cat.obj eye.obj kron.obj ARCSubproblem.obj relop.obj mldivide.obj roots.obj cubicRegScriptCOPY_emxutil.obj

ALL_OBJS = $(OBJS)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = $(MATLAB_ROOT)/bin/glnxa64/libmwlapack.lib

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_BASIC = $(DEFINES) $(INCLUDES) @$(COMPILER_COMMAND_FILE)

CFLAGS += $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_BASIC = $(DEFINES) $(INCLUDES) @$(COMPILER_COMMAND_FILE)

CPPFLAGS += $(CPPFLAGS_BASIC)

#---------------------
# MEX C++ Compiler
#---------------------

MEX_CPP_Compiler_BASIC =  @$(COMPILER_COMMAND_FILE)

MEX_CPPFLAGS += $(MEX_CPP_Compiler_BASIC)

#-----------------
# MEX Compiler
#-----------------

MEX_Compiler_BASIC =  @$(COMPILER_COMMAND_FILE)

MEX_CFLAGS += $(MEX_Compiler_BASIC)

###########################################################################
## INLINED COMMANDS
###########################################################################


MINGW_C_STANDARD_OPTS = $(C_STANDARD_OPTS)


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


download : $(PRODUCT)


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
	$(LD) $(LDFLAGS) -o $(PRODUCT) @$(CMD_FILE) -Wl,--start-group $(LIBS) -Wl,--end-group $(SYSTEM_LIBS) $(TOOLCHAIN_LIBS)
	@echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.obj : %.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.obj : %.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.obj : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.obj : $(START_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.obj : C:/Users/bryan/Documents/GitHub/MatrixMultiplication/BatchScripts/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.obj : C:/Users/bryan/Documents/GitHub/MatrixMultiplication/BatchScripts/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


rt_nonfinite.obj : $(START_DIR)/rt_nonfinite.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rtGetNaN.obj : $(START_DIR)/rtGetNaN.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rtGetInf.obj : $(START_DIR)/rtGetInf.c
	$(CC) $(CFLAGS) -o "$@" "$<"


main.obj : C:/Users/bryan/Documents/GitHub/MatrixMultiplication/BatchScripts/main.c
	$(CC) $(CFLAGS) -o "$@" "$<"


cubicRegScriptCOPY_rtwutil.obj : $(START_DIR)/cubicRegScriptCOPY_rtwutil.c
	$(CC) $(CFLAGS) -o "$@" "$<"


cubicRegScriptCOPY_data.obj : $(START_DIR)/cubicRegScriptCOPY_data.c
	$(CC) $(CFLAGS) -o "$@" "$<"


cubicRegScriptCOPY_initialize.obj : $(START_DIR)/cubicRegScriptCOPY_initialize.c
	$(CC) $(CFLAGS) -o "$@" "$<"


cubicRegScriptCOPY_terminate.obj : $(START_DIR)/cubicRegScriptCOPY_terminate.c
	$(CC) $(CFLAGS) -o "$@" "$<"


cubicRegScriptCOPY.obj : $(START_DIR)/cubicRegScriptCOPY.c
	$(CC) $(CFLAGS) -o "$@" "$<"


eml_rand_mt19937ar_stateful.obj : $(START_DIR)/eml_rand_mt19937ar_stateful.c
	$(CC) $(CFLAGS) -o "$@" "$<"


randn.obj : $(START_DIR)/randn.c
	$(CC) $(CFLAGS) -o "$@" "$<"


cubicRegCOPY.obj : $(START_DIR)/cubicRegCOPY.c
	$(CC) $(CFLAGS) -o "$@" "$<"


norm.obj : $(START_DIR)/norm.c
	$(CC) $(CFLAGS) -o "$@" "$<"


evalPenaltyFcn_CP.obj : $(START_DIR)/evalPenaltyFcn_CP.c
	$(CC) $(CFLAGS) -o "$@" "$<"


sum.obj : $(START_DIR)/sum.c
	$(CC) $(CFLAGS) -o "$@" "$<"


minOrMax.obj : $(START_DIR)/minOrMax.c
	$(CC) $(CFLAGS) -o "$@" "$<"


eig.obj : $(START_DIR)/eig.c
	$(CC) $(CFLAGS) -o "$@" "$<"


ishermitian.obj : $(START_DIR)/ishermitian.c
	$(CC) $(CFLAGS) -o "$@" "$<"


triu.obj : $(START_DIR)/triu.c
	$(CC) $(CFLAGS) -o "$@" "$<"


tensorHessianOptimized.obj : $(START_DIR)/tensorHessianOptimized.c
	$(CC) $(CFLAGS) -o "$@" "$<"


cat.obj : $(START_DIR)/cat.c
	$(CC) $(CFLAGS) -o "$@" "$<"


eye.obj : $(START_DIR)/eye.c
	$(CC) $(CFLAGS) -o "$@" "$<"


kron.obj : $(START_DIR)/kron.c
	$(CC) $(CFLAGS) -o "$@" "$<"


ARCSubproblem.obj : $(START_DIR)/ARCSubproblem.c
	$(CC) $(CFLAGS) -o "$@" "$<"


relop.obj : $(START_DIR)/relop.c
	$(CC) $(CFLAGS) -o "$@" "$<"


mldivide.obj : $(START_DIR)/mldivide.c
	$(CC) $(CFLAGS) -o "$@" "$<"


roots.obj : $(START_DIR)/roots.c
	$(CC) $(CFLAGS) -o "$@" "$<"


cubicRegScriptCOPY_emxutil.obj : $(START_DIR)/cubicRegScriptCOPY_emxutil.c
	$(CC) $(CFLAGS) -o "$@" "$<"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(COMPILER_COMMAND_FILE) $(MAKEFILE)


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
	$(RM) $(subst /,\,$(PRODUCT))
	$(RM) $(subst /,\,$(ALL_OBJS))
	$(ECHO) "### Deleted all derived files."


