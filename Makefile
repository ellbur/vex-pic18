TARGET    = $(BUILD_DIR)/vex_fw.hex
MCCPATH   = /opt/mcc18-2.4
BUILD_DIR = build
CC        = wine $(MCCPATH)/bin/mcc18.exe
LD        = wine $(MCCPATH)/bin/mplink.exe
RM        = rm -f
VEX_LIB   = Vex_library.lib
CFLAGS    = /i"$(MCCPATH)/h" -p=18F8520
LDFLAGS   = 18f8520user.lkr $(VEX_LIB) /l"$(MCCPATH)/lib" /a INHX32 /o
SOURCE    = ifi_startup.c\
            ifi_utilities.c\
            main.c\
            printf_lib.c\
            user_routines_fast.c\
            user_routines.c
HEADERS    = delays.h\
            ifi_aliases.h\
            ifi_default.h\
            ifi_picdefs.h\
            ifi_utilities.h\
            printf_lib.h\
            user_routines.h
OBJECTS   = $(patsubst %, $(BUILD_DIR)/%, $(SOURCE:.c=.o))

vpath %.c ./
vpath %.o $(BUILD_DIR)

.SECONDARY :

all : $(TARGET) | $(BUILD_DIR)
.PHONY : all

.PHONY : install
install : $(TARGET)
	@vexctl upload $<

.PHONY : clean
clean :
	@echo "CLEAN"
	@$(RM) $(OBJECTS) $(OBJECTS:.o=.err)\
	       $(TARGET)  $(TARGET:.hex=.cod) $(TARGET:.hex=.lst)

$(BUILD_DIR) :
	@mkdir $@

%.hex : $(OBJECTS)
	@echo "HEX $(@F)"
	@$(LD) $(LDFLAGS) $(TARGET) $^

%.o : $(@F:.o=.c) $(HEADERS)
	@echo "OBJ $(@F)"
	@$(CC) $(CFLAGS) $< -fo=$@ -fe=$(@:.o=.err)


