TARGET    := vex_fw
MCCPATH   := ../mcc18
BUILD_DIR := build
CC        := wine $(MCCPATH)/bin/mcc18.exe
LD        := wine $(MCCPATH)/bin/mplink.exe
CFLAGS    := /i"$(MCCPATH)/h" -p=18F8520
LDFLAGS   := 18f8520user.lkr Vex_library.lib /l"$(MCCPATH)/lib" /o
SOURCE    := ifi_startup.c\
             ifi_utilities.c\
             main.c\
             printf_lib.c\
             user_routines_fast.c\
             user_routines.c
OBJECTS   := $(patsubst %, $(BUILD_DIR)/%, $(SOURCE:.c=.o))

all : $(TARGET)

$(TARGET): $(OBJECTS)
	@$(LD) $(LDFLAGS) $(BUILD_DIR)/$(TARGET).hex $(OBJECTS)

clean :
	@rm -f $(OBJECTS) $(OBJECTS:.o=.err) $(BUILD_DIR)/$(TARGET).hex\
	       $(OBJECTS:.o=.lst) $(OBJECTS:.o=.cod) $(BUILD_DIR)/$(TARGET).cod \
	       $(BUILD_DIR)/$(TARGET).lst

install :
	@vexctl upload $(BUILD_DIR)/$(TARGET).hex

$(BUILD_DIR)/%.o : %.c
	@$(CC) $(CFLAGS) $< -fo=$@ -fe=$(BUILD_DIR)/$*.err
