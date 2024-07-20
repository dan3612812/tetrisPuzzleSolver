# AUTHOR:BYS

CC?=gcc
CFLAGS?=-g -I ./inc -Wall -lpthread
LDFLAGS?=
SRCDIR:=./src
OBJDIR:=./obj
BINDIR:=./bin
MODDIR:=./mod

SRC:=$(foreach x,$(SRCDIR),$(wildcard $(addprefix $(x)/*,.c)))
OBJ:=$(addprefix $(OBJDIR)/,$(addsuffix .o,$(notdir $(basename $(SRC)))))
MOD:=$(foreach x,$(MODDIR),$(wildcard $(addprefix $(x)/*,.c)))
OBJ+=$(addprefix $(OBJDIR)/,$(addsuffix .o,$(notdir $(basename $(MOD)))))
LIB:=
BIN:= main

.PHONY:all
all: prepare $(BIN)


.PHONY:prepare
prepare:
	@mkdir -p $(OBJDIR) $(BINDIR)

$(BIN): $(OBJ)
	$(CC) -o $(BINDIR)/$(BIN) $? $(CFLAGS) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $? -o $@ $(CFLAGS)
$(OBJDIR)/%.o: $(MODDIR)/%.c
	$(CC) -c $? -o $@ $(CFLAGS)


.PHONY:run
run: all
	@echo "====START===="
	@$(BINDIR)/$(BIN)
	@echo "=====END====="

.PHONY:clean
clean:
	@rm -rf $(OBJDIR) $(BINDIR)