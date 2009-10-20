OUTFILE := out
MCCPATH := ../mcc18
BUILD   := build
OUT     := out
CC      := wine $(MCCPATH)/bin/mcc18.exe
LD      := wine $(MCCPATH)/bin/mplink.exe
CFLAGS  := /i"$(MCCPATH)/h" -p=18F8520
LDFLAGS := 18f8520user.lkr Vex_library.lib /l"$(MCCPATH)/lib"\
           /o $(BUILD)/$(OUTFILE).hex
OBJECTS := ifi_startup.o\
           ifi_utilities.o\
           main.o\
           printf_lib.o\
           user_routines_fast.o\
           user_routines.o
OBJECTS := $(patsubst %, $(BUILD)/%, $(OBJECTS))

all : $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS)

clean :
	rm -f $(BUILD)/*.o $(BUILD)/*.err $(BUILD)/*.hex $(BUILD)/*.lst\
	      $(BUILD)/*.cod

install :
	vexctl upload $(BUILD)/$(OUT).hex

$(BUILD)/%.o : %.c
	$(CC) $(CFLAGS) $< -fo=$@ -fe=$(BUILD)/$*.err
