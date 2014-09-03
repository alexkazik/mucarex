
CC = gcc
LD = gcc
XXD = xxd

CFLAGS = -MD
LDFLAGS = 

DEPDIR = .deps

SRCS = main.c launcher.c launcher_bin.c directory.c mdir.c binary.c md5.c

OBJS = $(SRCS:.c=.o)


all: vectrexpack

%.o: %.c | $(DEPDIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@cp $*.d $(DEPDIR)/$*.P; \
		sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $(DEPDIR)/$*.P; \
		rm -f $*.d

launcher_bin.c: launcher.bin
	$(XXD) -i $< $@

vectrexpack: $(OBJS)
	$(LD) -o $@ $^ $(LDFLAGS)

clean:
	@rm $(OBJS) launcher_bin.c vectrexpack $(DEPDIR)/*.P 2>/dev/null ; true
	@rmdir $(DEPDIR) 2>/dev/null ; true

$(DEPDIR):
	mkdir -p $(DEPDIR)

-include $(DEPDIR)/*.P
