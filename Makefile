
MCCPATH   = /opt/mcc18
MPCC      = $(MCCPATH)/bin/mcc18
MPLD      = $(MCCPATH)/bin/mplink
RM        = rm -f

HEX       = $(HEX_DIR)/vex.hex

BUILD_DIR     = build
HEX_DIR       = hex

DIRS      = $(BUILD_DIR) $(HEX_DIR)

VEX_LIB     = Vex_alltimers_auton_test.lib
MPCFLAGS    = /i "$(MCCPATH)/h" -p=18F8520 -DPIC=1
LIBPATH     = "$(MCCPATH)/lib/"
MPLDFLAGS   = 18f8520user.lkr $(VEX_LIB) /l "$(LIBPATH)" /a INHX32 /o

include PicSources
include UserSources

HEADERS   = $(wildcard *.h)

USER_PIC_OBJECTS  = $(patsubst %, $(BUILD_DIR)/%, $(USER_SOURCES:.c=.o))
PIC_OBJECTS   = $(patsubst %, $(BUILD_DIR)/%, $(PIC_SOURCES:.c=.o)) $(USER_PIC_OBJECTS)

.SECONDARY :

all : $(HEX) | $(DIRS)
.PHONY : all

pre : $(DIRS) ;
.PHONY : pre

.PHONY : clean
clean :
	@echo "CLEAN"
	@-$(RM) $(BUILD_DIR)/* $(HEX_DIR)/*

$(DIRS):
	@mkdir $@

$(HEX): $(PIC_OBJECTS)
	@echo "HEX $(@F)"
	$(MPLD) $(MPLDFLAGS) $(HEX) $^
	@$(RM) $(HEX_DIR)/*.cod $(HEX_DIR)/*.lst

$(BUILD_DIR)/%.o : %.c $(HEADERS)
	@echo "OBJ $(@F)"
	@$(MPCC) $(MPCFLAGS) $< -fo=$@ -fe=$(@:.o=.err)
	