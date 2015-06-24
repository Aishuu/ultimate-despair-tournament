SRCDIR      = src
OBJDIR      = obj
BINDIR      = bin

PLY1        = TheDemos
PLY2        = Aishuu

CC          = gcc
CFLAGS      = -Wall -DPLAYER1=\"$(PLY1)\" -DPLAYER2=\"$(PLY2)\"
EXEC_NAME   = tournament
INCLUDES    = 
LIBS        = -lSDL2 -lm

SRC_FILES   = $(wildcard $(SRCDIR)/*.c)
PLY1_FILES  = $(wildcard $(PLY1)/*.c)
PLY2_FILES  = $(wildcard $(PLY2)/*.c)

OBJ_FILES   = $(SRC_FILES:$(SRCDIR)/%.c=$(OBJDIR)/%.o) $(PLY1_FILES:$(PLY1)/%.c=$(OBJDIR)/$(PLY1)_%.o) $(PLY2_FILES:$(PLY2)/%.c=$(OBJDIR)/$(PLY2)_%.o)


all : $(BINDIR)/$(EXEC_NAME)

.PHONEY: clean

clean :
	rm -f $(BINDIR)/$(EXEC_NAME) $(OBJ_FILES)

$(BINDIR)/$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(BINDIR)/$(EXEC_NAME) $(OBJ_FILES) $(LIBS)

$(OBJDIR)/$(PLY1)_%.o: $(PLY1)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(OBJDIR)/$(PLY2)_%.o: $(PLY2)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<
