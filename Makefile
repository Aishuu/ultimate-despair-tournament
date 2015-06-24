PWD         = $(shell pwd)
SRCDIR      = src
OBJDIR      = obj
BINDIR      = bin

GAMEDIR     = game

PLY1        = TheDemos
PLY2        = Aishuu

CC          = gcc
CFLAGS      = -Wall -DPLAYER1=\"$(PLY1)\" -DPLAYER2=\"$(PLY2)\"
EXEC_NAME   = tournament
INCLUDES    = -I$(PWD)/$(SRCDIR)
LIBS        = -lSDL2 -lm

SRC_FILES   = $(shell find $(SRCDIR) -type f -name '*.c')

OBJ_FILES   = $(SRC_FILES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all : $(BINDIR)/$(EXEC_NAME)

.PHONEY: clean

clean :
	rm -f $(BINDIR)/$(EXEC_NAME) $(OBJ_FILES)

$(BINDIR)/$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(BINDIR)/$(EXEC_NAME) $(OBJ_FILES) $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<
