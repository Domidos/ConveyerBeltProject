# Wind River Workbench generated Makefile.
# Do not edit!!!
#
# The file ".wrmakefile" is the template used by the Wind River Workbench to
# generate the makefiles of this project. Add user-specific build targets and
# make rules only(!) in this project's ".wrmakefile" file. These will then be
# automatically dumped into the makefiles.

WIND_HOME := $(subst \,/,$(WIND_HOME))
WIND_BASE := $(subst \,/,$(WIND_BASE))
WIND_USR := $(subst \,/,$(WIND_USR))
WRVX_COMPBASE := $(subst \,/,$(WRVX_COMPBASE))

all : pre_build main_all post_build

_clean ::
	@echo "make: removing targets and objects of `pwd`"

TRACE=0
TRACEON=$(TRACE:0=@)
TRACE_FLAG=$(TRACEON:1=)

JOBS?=1
TARGET_JOBS?=$(JOBS)

MAKEFILE := Makefile

FLEXIBLE_BUILD := 1

BUILD_SPEC = SIMNTdiab
DEBUG_MODE = 1
ifeq ($(DEBUG_MODE),1)
MODE_DIR := Debug
else
MODE_DIR := NonDebug
endif
OBJ_DIR := .
WS_ROOT_DIR := C:/_HP_2Sem
PRJ_ROOT_DIR := $(WS_ROOT_DIR)/StateMachine



#Global Build Macros
PROJECT_TYPE = DKM
DEFINES = 
EXPAND_DBG = 0


#BuildSpec specific Build Macros
VX_CPU_FAMILY = simpc
CPU = SIMNT
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tX86LH:vxworks69
VSB_DIR = $(WIND_BASE)/target/lib
VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 

IDE_LIBRARIES = 

IDE_DEFINES = -DCPU=_VX_$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\"   -DIP_PORT_VXWORKS=69 



#BuildTool flags
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
DEBUGFLAGS_C++-Compiler = -g
DEBUGFLAGS_Linker = -g
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_C-Compiler =  -XO -Xsize-opt 
DEBUGFLAGS_C++-Compiler =  -XO -Xsize-opt 
DEBUGFLAGS_Linker =  -XO -Xsize-opt 
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler =  -XO -Xsize-opt 
endif


#Project Targets
PROJECT_TARGETS = StateMachine/$(MODE_DIR)/StateMachine.out \
	 StateMachine_partialImage/$(MODE_DIR)/StateMachine_partialImage.o


#Rules

# StateMachine
ifeq ($(DEBUG_MODE),1)
StateMachine/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
StateMachine/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
StateMachine/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
StateMachine/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
StateMachine/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
StateMachine/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
StateMachine/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler =  -XO -Xsize-opt 
StateMachine/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler =  -XO -Xsize-opt 
StateMachine/$(MODE_DIR)/% : DEBUGFLAGS_Linker =  -XO -Xsize-opt 
StateMachine/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
StateMachine/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
StateMachine/$(MODE_DIR)/% : DEBUGFLAGS_Assembler =  -XO -Xsize-opt 
endif
StateMachine/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
StateMachine/$(MODE_DIR)/% : IDE_LIBRARIES = 
StateMachine/$(MODE_DIR)/% : IDE_DEFINES = -DCPU=_VX_$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\"   -DIP_PORT_VXWORKS=69 
StateMachine/$(MODE_DIR)/% : PROJECT_TYPE = DKM
StateMachine/$(MODE_DIR)/% : DEFINES = 
StateMachine/$(MODE_DIR)/% : EXPAND_DBG = 0
StateMachine/$(MODE_DIR)/% : VX_CPU_FAMILY = simpc
StateMachine/$(MODE_DIR)/% : CPU = SIMNT
StateMachine/$(MODE_DIR)/% : TOOL_FAMILY = diab
StateMachine/$(MODE_DIR)/% : TOOL = diab
StateMachine/$(MODE_DIR)/% : TOOL_PATH = 
StateMachine/$(MODE_DIR)/% : CC_ARCH_SPEC = -tX86LH:vxworks69
StateMachine/$(MODE_DIR)/% : VSB_DIR = $(WIND_BASE)/target/lib
StateMachine/$(MODE_DIR)/% : VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
StateMachine/$(MODE_DIR)/% : LIBPATH = 
StateMachine/$(MODE_DIR)/% : LIBS = 
StateMachine/$(MODE_DIR)/% : OBJ_DIR := StateMachine/$(MODE_DIR)

OBJECTS_StateMachine = StateMachine_partialImage/$(MODE_DIR)/StateMachine_partialImage.o

ifeq ($(TARGET_JOBS),1)
StateMachine/$(MODE_DIR)/StateMachine.out : $(OBJECTS_StateMachine)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";rm -f "$@";ddump -Ng $(OBJECTS_StateMachine) | tclsh $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c pentium -tags $(VSB_DIR)/tags/simpc/SIMNT/common/dkm.tags > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)dcc $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -Xdollar-in-ident -ei1518,4177,4223,4301,4550,5409,1606 -ei4193,4826,4381,4237,1573,4007,4082,4177,4223,4260,4550,5361,5828,2273,5387,5388 -ei1522,4092,4111,4152,4167,4171,4174,4186,4188,4191,4192,4223,4231,4236,4284,4375,4494,4513,5152,5457 -Xforce-declarations  $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES)  $(IDE_DEFINES) $(DEFINES) -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)dld -tX86LH:vxworks69 -X -r5 -f 0x90,1,1 -r4 -o "$@" $(OBJ_DIR)/ctdt.o $(OBJECTS_StateMachine) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

else
StateMachine/$(MODE_DIR)/StateMachine.out : StateMachine/$(MODE_DIR)/StateMachine.out_jobs

endif
StateMachine/$(MODE_DIR)/StateMachine_compile_file : $(FILE) ;

_clean :: StateMachine/$(MODE_DIR)/StateMachine_clean

StateMachine/$(MODE_DIR)/StateMachine_clean : 
	$(TRACE_FLAG)if [ -d "StateMachine" ]; then cd "StateMachine"; rm -rf $(MODE_DIR); fi


# StateMachine_partialImage
ifeq ($(DEBUG_MODE),1)
StateMachine_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
StateMachine_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
StateMachine_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
StateMachine_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
StateMachine_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
StateMachine_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
StateMachine_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler =  -XO -Xsize-opt 
StateMachine_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler =  -XO -Xsize-opt 
StateMachine_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker =  -XO -Xsize-opt 
StateMachine_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
StateMachine_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
StateMachine_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler =  -XO -Xsize-opt 
endif
StateMachine_partialImage/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
StateMachine_partialImage/$(MODE_DIR)/% : IDE_LIBRARIES = 
StateMachine_partialImage/$(MODE_DIR)/% : IDE_DEFINES = -DCPU=_VX_$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\"   -DIP_PORT_VXWORKS=69 
StateMachine_partialImage/$(MODE_DIR)/% : PROJECT_TYPE = DKM
StateMachine_partialImage/$(MODE_DIR)/% : DEFINES = 
StateMachine_partialImage/$(MODE_DIR)/% : EXPAND_DBG = 0
StateMachine_partialImage/$(MODE_DIR)/% : VX_CPU_FAMILY = simpc
StateMachine_partialImage/$(MODE_DIR)/% : CPU = SIMNT
StateMachine_partialImage/$(MODE_DIR)/% : TOOL_FAMILY = diab
StateMachine_partialImage/$(MODE_DIR)/% : TOOL = diab
StateMachine_partialImage/$(MODE_DIR)/% : TOOL_PATH = 
StateMachine_partialImage/$(MODE_DIR)/% : CC_ARCH_SPEC = -tX86LH:vxworks69
StateMachine_partialImage/$(MODE_DIR)/% : VSB_DIR = $(WIND_BASE)/target/lib
StateMachine_partialImage/$(MODE_DIR)/% : VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
StateMachine_partialImage/$(MODE_DIR)/% : LIBPATH = 
StateMachine_partialImage/$(MODE_DIR)/% : LIBS = 
StateMachine_partialImage/$(MODE_DIR)/% : OBJ_DIR := StateMachine_partialImage/$(MODE_DIR)

StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/TCPClient.o : $(PRJ_ROOT_DIR)/TCPClient.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP -ei1518,4177,4223,4301,4550,5409,1606 -ei4193,4826,4381,4237,1573,4007,4082,4177,4223,4260,4550,5361,5828,2273,5387,5388 -ei1522,4092,4111,4152,4167,4171,4174,4186,4188,4191,4192,4223,4231,4236,4284,4375,4494,4513,5152,5457 -Xforce-declarations   -Xmake-dependency=0xd $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/TCPServer.o : $(PRJ_ROOT_DIR)/TCPServer.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP -ei1518,4177,4223,4301,4550,5409,1606 -ei4193,4826,4381,4237,1573,4007,4082,4177,4223,4260,4550,5361,5828,2273,5387,5388 -ei1522,4092,4111,4152,4167,4171,4174,4186,4188,4191,4192,4223,4231,4236,4284,4375,4494,4513,5152,5457 -Xforce-declarations   -Xmake-dependency=0xd $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/TelnetServer.o : $(PRJ_ROOT_DIR)/TelnetServer.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP -ei1518,4177,4223,4301,4550,5409,1606 -ei4193,4826,4381,4237,1573,4007,4082,4177,4223,4260,4550,5361,5828,2273,5387,5388 -ei1522,4092,4111,4152,4167,4171,4174,4186,4188,4191,4192,4223,4231,4236,4284,4375,4494,4513,5152,5457 -Xforce-declarations   -Xmake-dependency=0xd $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/diaTimer.o : $(PRJ_ROOT_DIR)/diaTimer.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP -ei1518,4177,4223,4301,4550,5409,1606 -ei4193,4826,4381,4237,1573,4007,4082,4177,4223,4260,4550,5361,5828,2273,5387,5388 -ei1522,4092,4111,4152,4167,4171,4174,4186,4188,4191,4192,4223,4231,4236,4284,4375,4494,4513,5152,5457 -Xforce-declarations   -Xmake-dependency=0xd $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/disp.o : $(PRJ_ROOT_DIR)/disp.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP -Xc-new -Xdialect-c89  -ei1518,4177,4223,4301,4550,5409,1606 -ei4193,4826,4381,4237,1573,4007,4082,4177,4223,4260,4550,5361,5828,2273,5387,5388 -ei1522,4092,4111,4152,4167,4171,4174,4186,4188,4191,4192,4223,4231,4236,4284,4375,4494,4513,5152,5457 -Xforce-declarations   -Xmake-dependency=0xd $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/hwFunc.o : $(PRJ_ROOT_DIR)/hwFunc.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP -Xc-new -Xdialect-c89  -ei1518,4177,4223,4301,4550,5409,1606 -ei4193,4826,4381,4237,1573,4007,4082,4177,4223,4260,4550,5361,5828,2273,5387,5388 -ei1522,4092,4111,4152,4167,4171,4174,4186,4188,4191,4192,4223,4231,4236,4284,4375,4494,4513,5152,5457 -Xforce-declarations   -Xmake-dependency=0xd $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/kbd.o : $(PRJ_ROOT_DIR)/kbd.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP -Xc-new -Xdialect-c89  -ei1518,4177,4223,4301,4550,5409,1606 -ei4193,4826,4381,4237,1573,4007,4082,4177,4223,4260,4550,5361,5828,2273,5387,5388 -ei1522,4092,4111,4152,4167,4171,4174,4186,4188,4191,4192,4223,4231,4236,4284,4375,4494,4513,5152,5457 -Xforce-declarations   -Xmake-dependency=0xd $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/keyboard.o : $(PRJ_ROOT_DIR)/keyboard.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP -ei1518,4177,4223,4301,4550,5409,1606 -ei4193,4826,4381,4237,1573,4007,4082,4177,4223,4260,4550,5361,5828,2273,5387,5388 -ei1522,4092,4111,4152,4167,4171,4174,4186,4188,4191,4192,4223,4231,4236,4284,4375,4494,4513,5152,5457 -Xforce-declarations   -Xmake-dependency=0xd $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/main.o : $(PRJ_ROOT_DIR)/main.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP -ei1518,4177,4223,4301,4550,5409,1606 -ei4193,4826,4381,4237,1573,4007,4082,4177,4223,4260,4550,5361,5828,2273,5387,5388 -ei1522,4092,4111,4152,4167,4171,4174,4186,4188,4191,4192,4223,4231,4236,4284,4375,4494,4513,5152,5457 -Xforce-declarations   -Xmake-dependency=0xd $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/setMyIP.o : $(PRJ_ROOT_DIR)/setMyIP.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP -ei1518,4177,4223,4301,4550,5409,1606 -ei4193,4826,4381,4237,1573,4007,4082,4177,4223,4260,4550,5361,5828,2273,5387,5388 -ei1522,4092,4111,4152,4167,4171,4174,4186,4188,4191,4192,4223,4231,4236,4284,4375,4494,4513,5152,5457 -Xforce-declarations   -Xmake-dependency=0xd $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/stateMachine.o : $(PRJ_ROOT_DIR)/stateMachine.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP -ei1518,4177,4223,4301,4550,5409,1606 -ei4193,4826,4381,4237,1573,4007,4082,4177,4223,4260,4550,5361,5828,2273,5387,5388 -ei1522,4092,4111,4152,4167,4171,4174,4186,4188,4191,4192,4223,4231,4236,4284,4375,4494,4513,5152,5457 -Xforce-declarations   -Xmake-dependency=0xd $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/stateTable.o : $(PRJ_ROOT_DIR)/stateTable.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP -ei1518,4177,4223,4301,4550,5409,1606 -ei4193,4826,4381,4237,1573,4007,4082,4177,4223,4260,4550,5361,5828,2273,5387,5388 -ei1522,4092,4111,4152,4167,4171,4174,4186,4188,4191,4192,4223,4231,4236,4284,4375,4494,4513,5152,5457 -Xforce-declarations   -Xmake-dependency=0xd $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/systemManager.o : $(PRJ_ROOT_DIR)/systemManager.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP -ei1518,4177,4223,4301,4550,5409,1606 -ei4193,4826,4381,4237,1573,4007,4082,4177,4223,4260,4550,5361,5828,2273,5387,5388 -ei1522,4092,4111,4152,4167,4171,4174,4186,4188,4191,4192,4223,4231,4236,4284,4375,4494,4513,5152,5457 -Xforce-declarations   -Xmake-dependency=0xd $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


OBJECTS_StateMachine_partialImage = StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/TCPClient.o \
	 StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/TCPServer.o \
	 StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/TelnetServer.o \
	 StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/diaTimer.o \
	 StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/disp.o \
	 StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/hwFunc.o \
	 StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/kbd.o \
	 StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/keyboard.o \
	 StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/main.o \
	 StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/setMyIP.o \
	 StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/stateMachine.o \
	 StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/stateTable.o \
	 StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/systemManager.o

ifeq ($(TARGET_JOBS),1)
StateMachine_partialImage/$(MODE_DIR)/StateMachine_partialImage.o : $(OBJECTS_StateMachine_partialImage)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dld -tX86LH:vxworks69 -X -r5 -f 0x90,1,1  -o "$@" $(OBJECTS_StateMachine_partialImage) $(ADDED_OBJECTS) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

else
StateMachine_partialImage/$(MODE_DIR)/StateMachine_partialImage.o : StateMachine_partialImage/$(MODE_DIR)/StateMachine_partialImage.o_jobs

endif
StateMachine_partialImage/$(MODE_DIR)/StateMachine_partialImage_compile_file : $(FILE) ;

_clean :: StateMachine_partialImage/$(MODE_DIR)/StateMachine_partialImage_clean

StateMachine_partialImage/$(MODE_DIR)/StateMachine_partialImage_clean : 
	$(TRACE_FLAG)if [ -d "StateMachine_partialImage" ]; then cd "StateMachine_partialImage"; rm -rf $(MODE_DIR); fi

force : 

TARGET_JOBS_RULE?=echo "Update the makefile template via File > Import > Build Settings : Update makefile template";exit 1
%_jobs : 
	$(TRACE_FLAG)$(TARGET_JOBS_RULE)

DEP_FILES := StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/TCPClient.d StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/TCPServer.d StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/TelnetServer.d \
	 StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/diaTimer.d StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/disp.d StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/hwFunc.d \
	 StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/kbd.d StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/keyboard.d StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/main.d \
	 StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/setMyIP.d StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/stateMachine.d StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/stateTable.d \
	 StateMachine_partialImage/$(MODE_DIR)/Objects/StateMachine/systemManager.d
-include $(DEP_FILES)


WIND_SCOPETOOLS_BASE := $(subst \,/,$(WIND_SCOPETOOLS_BASE))

clean_scopetools :
	$(TRACE_FLAG)rm -rf $(PRJ_ROOT_DIR)/.coveragescope/db

CLEAN_STEP := clean_scopetools


-include $(PRJ_ROOT_DIR)/*.makefile

-include *.makefile

TARGET_JOBS_RULE=$(MAKE) -f $(MAKEFILE) --jobs $(TARGET_JOBS) $(MFLAGS) $* TARGET_JOBS=1
ifeq ($(JOBS),1)
main_all : external_build  $(PROJECT_TARGETS)
	@echo "make: built targets of `pwd`"
else
main_all : external_build 
	@$(MAKE) -f $(MAKEFILE) --jobs $(JOBS) $(MFLAGS) $(PROJECT_TARGETS) TARGET_JOBS=1 &&\
	echo "make: built targets of `pwd`"
endif 

# entry point for extending the build
external_build ::
	@echo ""

# main entry point for pre processing prior to the build
pre_build :: $(PRE_BUILD_STEP) generate_sources
	@echo ""

# entry point for generating sources prior to the build
generate_sources ::
	@echo ""

# main entry point for post processing after the build
post_build :: $(POST_BUILD_STEP) deploy_output
	@echo ""

# entry point for deploying output after the build
deploy_output ::
	@echo ""

clean :: external_clean $(CLEAN_STEP) _clean

# entry point for extending the build clean
external_clean ::
	@echo ""
