
TARGET    = $(BUILD_DIR)/vex_fw.hex
MCCPATH   = /opt/mcc18
BUILD_DIR = build
CC        = $(MCCPATH)/bin/mcc18
LD        = $(MCCPATH)/bin/mplink
RM        = rm -f
VEX_LIB   = Vex_alltimers_auton_test.lib
CFLAGS    = /i "$(MCCPATH)/h" -p=18F8520
LIBPATH   = "$(MCCPATH)/lib/"
LDFLAGS   = 18f8520user.lkr $(VEX_LIB) /l "$(LIBPATH)" /a INHX32 /o
#LD_FILTER = grep -v '^Copyright (c) [0-2][0-9][0-9][0-9] Microchip Technology Inc.'\
	    | grep -v '^MP2HEX 3.90, COFF to HEX File Converter'\
	    | grep -v '^MP2COD 3.90, COFF to COD File Converter'\
	    | grep -v '^MPLINK 3.90, Linker'\
	    | grep -v '^Errors    : 0'

include Sources

SOURCE    = $(SOURCES)
HEADERS   = $(wildcard *.h)
OBJECTS   = $(patsubst %, $(BUILD_DIR)/%, $(SOURCE:.c=.o))

.SECONDARY :

all : $(TARGET) | $(BUILD_DIR)
.PHONY : all

.PHONY : install
install : $(TARGET)
	@vexctl upload $<

.PHONY : clean
clean :
	@echo "CLEAN"
	@-$(RM) $(BUILD_DIR)/*

$(BUILD_DIR) :
	@mkdir $@

%.hex : $(OBJECTS)
	@echo "HEX $(@F)"
	@$(LD) $(LDFLAGS) $(TARGET) $^ #| $(LD_FILTER)

$(BUILD_DIR)/%.o : %.c $(HEADERS)
	@echo "OBJ $(@F)"
	@$(CC) $(CFLAGS) $< -fo=$@ -fe=$(@:.o=.err)


