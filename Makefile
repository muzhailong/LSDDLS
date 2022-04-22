#
# OMNeT++/OMNEST Makefile for ddp_sim
#
# This file was generated with the command:
#  opp_makemake -f --deep -O out -I/data/home/muzhailong/ucx/build/include -I/data/home/muzhailong/omnetpp-5.0/include -I/data/home/muzhailong/cudnn/include -I/data/home/muzhailong/devs/protobuf/build/include -I/usr/local/cuda-11.3/include -I/data/home/muzhailong/devs/bccl/build/include -I/data/application/guest/gcc7/gcc-7.4.0/build/include -I/data/application/guest/nccl/include -L/data/application/guest/gcc7/gcc-7.4.0/build/lib64 -L/data/application/guest/python36/lib64 -L/usr/local/cuda-11.3/lib64/ -L/usr/local/cuda-11.3/lib64/stubs -L/usr/local/cuda-11.3/lib64 -L/data/home/muzhailong/devs/bccl/build/lib -L/data/application/guest/nccl/lib -L/data/application/guest/python36/local/lib64 -L{LIBRARY_PATH}
#

# Name of target to be created (-o option)
TARGET = ddp_sim$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(QTENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)
#USERIF_LIBS = $(QTENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I/data/home/muzhailong/ucx/build/include \
    -I/data/home/muzhailong/omnetpp-5.0/include \
    -I/data/home/muzhailong/cudnn/include \
    -I/data/home/muzhailong/devs/protobuf/build/include \
    -I/usr/local/cuda-11.3/include \
    -I/data/home/muzhailong/devs/bccl/build/include \
    -I/data/application/guest/gcc7/gcc-7.4.0/build/include \
    -I/data/application/guest/nccl/include \
    -I. \
    -Idata

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L/data/application/guest/gcc7/gcc-7.4.0/build/lib64 -L/data/application/guest/python36/lib64 -L/usr/local/cuda-11.3/lib64/ -L/usr/local/cuda-11.3/lib64/stubs -L/usr/local/cuda-11.3/lib64 -L/data/home/muzhailong/devs/bccl/build/lib -L/data/application/guest/nccl/lib -L/data/application/guest/python36/local/lib64 -L{LIBRARY_PATH}
LIBS += -Wl,-rpath,`abspath /data/application/guest/gcc7/gcc-7.4.0/build/lib64` -Wl,-rpath,`abspath /data/application/guest/python36/lib64` -Wl,-rpath,`abspath /usr/local/cuda-11.3/lib64/` -Wl,-rpath,`abspath /usr/local/cuda-11.3/lib64/stubs` -Wl,-rpath,`abspath /usr/local/cuda-11.3/lib64` -Wl,-rpath,`abspath /data/home/muzhailong/devs/bccl/build/lib` -Wl,-rpath,`abspath /data/application/guest/nccl/lib` -Wl,-rpath,`abspath /data/application/guest/python36/local/lib64` -Wl,-rpath,`abspath {LIBRARY_PATH}`

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc, .msg and .sm files
OBJS = \
    $O/OCSSwitch.o \
    $O/GPU.o \
    $O/Model.o \
    $O/Utils.o \
    $O/PcieSwitch.o \
    $O/NIC.o \
    $O/SimPacket_m.o

# Message files
MSGFILES = \
    SimPacket.msg

# SM files
SMFILES =

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)
SMCOPTS =

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders smheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

%_sm.cc %_sm.h: %.sm
	$(qecho) SMC: $<
	$(Q)$(SMC) -c++ -suffix cc $(SMCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

smheaders: $(SMFILES:.sm=_sm.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f ddp_sim ddp_sim.exe libddp_sim.so libddp_sim.a libddp_sim.dll libddp_sim.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h ./*_sm.cc ./*_sm.h
	$(Q)-rm -f data/*_m.cc data/*_m.h data/*_sm.cc data/*_sm.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES) $(SM_CC_FILES)  ./*.cc data/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/GPU.o: GPU.cc \
	GPU.h \
	Model.h \
	OCSSwitch.h \
	SimPacket_m.h \
	Utils.h
$O/Model.o: Model.cc \
	Model.h \
	SimPacket_m.h \
	Utils.h
$O/NIC.o: NIC.cc \
	GPU.h \
	Model.h \
	NIC.h \
	OCSSwitch.h \
	SimPacket_m.h \
	Utils.h
$O/OCSSwitch.o: OCSSwitch.cc \
	GPU.h \
	Model.h \
	OCSSwitch.h \
	SimPacket_m.h \
	Utils.h
$O/PcieSwitch.o: PcieSwitch.cc \
	GPU.h \
	Model.h \
	OCSSwitch.h \
	PcieSwitch.h \
	SimPacket_m.h \
	Utils.h
$O/SimPacket_m.o: SimPacket_m.cc \
	SimPacket_m.h
$O/Utils.o: Utils.cc \
	Utils.h

