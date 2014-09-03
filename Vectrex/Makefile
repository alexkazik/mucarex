
AS = asl
P2BIN = p2bin
DEPDIR = .deps
df = $(DEPDIR)/$(*F)

.SECONDARY:

all: launcher.bin mds-am29f040-updater.bin mds-sst39sf040-updater.bin

allsource: $(patsubst %.asm, %.bin, $(wildcard *.asm))

launcher.p: font.lib

mds-am29f040-updater.p: mds-am29f040.bin

mds-sst39sf040-updater.p: mds-sst39sf040.bin

%.p: %.asm | $(DEPDIR)
	$(AS) -L -U -x -o $@ $<
	php mkdep.php $< $(df).P

%.bin: %.p
	$(P2BIN) -l 255 -r 0x-0x $< $@

clean:
	@rm *.bin *.p *.lst $(DEPDIR)/*.P font.png font.lib 2>/dev/null ; true
	@rmdir $(DEPDIR) 2>/dev/null ; true

$(DEPDIR):
	mkdir -p $(DEPDIR)

font.lib: font.php font_dat.php
	php font.php

-include $(DEPDIR)/*.P
