# This file is based on the
# EasyFlash 3 CPLD Firmware
# (C) Thomas 'skoe' Giesel
# see Licence.md

here 		:= $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
synth_dir 	:= $(here)/synth
src_dir		:= $(here)/src
vhdlprj		:= mucarex

# this file list is for dependencies only, keep in sync with $(src_dir)/$(vhdlprj).prj
src 		:= $(src_dir)/$(vhdlprj).vhdl

uc  := $(src_dir)/$(vhdlprj).ucf

xst_cfg    := $(src_dir)/$(vhdlprj).xst
project    := $(src_dir)/$(vhdlprj).prj

netlist		:= $(synth_dir)/$(vhdlprj).ngc

gen_db     := $(synth_dir)/$(vhdlprj).ngd
fit        := $(synth_dir)/$(vhdlprj).vm6
jedec      := $(here)/$(vhdlprj).jed
svf       := $(here)/$(vhdlprj).svf

dev_type   := xc9572xl
dev_pkg    := pc44
dev_speed  := 10
device     := $(dev_type)-$(dev_pkg)-$(dev_speed)
device_fit := $(dev_type)-$(dev_speed)-$(dev_pkg)

fit_flags  := -p $(device_fit) -ofmt abel -log fitter.log -optimize density
fit_flags  += -power low -slew slow -keepio
fit_filter_output := "^CS: block property:\|^$$"

# directories to be created
dirs       := $(synth_dir) $(here)/log

.PHONY: all
all: $(svf)

################################################################################
.PHONY: netlist
netlist: $(netlist)
$(netlist): $(xst_cfg) $(src) $(project) | $(dirs)
	mkdir -p $(synth_dir)/xst/tmp/
	xst -intstyle silent -ifn $<
	mv $(vhdlprj).srp log/netlist.$(vhdlprj).srp

################################################################################
.PHONY: gen_db
gen_db: $(gen_db)
$(gen_db): $(netlist) $(uc) | $(dirs)
	mkdir -p synth/ngdbuild/tmp/
	cd $(synth_dir) && ngdbuild -p $(device) -uc $(uc) -quiet \
		-intstyle silent -dd $(synth_dir)/ngdbuild/tmp/ $<
	mv $(synth_dir)/$(vhdlprj).bld log/ngd.$(vhdlprj).bld

################################################################################
.PHONY: fit
fit: $(fit)
$(fit): $(gen_db) | $(dirs)
	cd $(synth_dir) && cpldfit $(fit_flags) $< | grep -v $(fit_filter_output)
	mv $(synth_dir)/$(vhdlprj).rpt log/fitter.$(vhdlprj).rpt

################################################################################
.PHONY: jedec
jedec: $(jedec)
$(jedec): $(fit)
	hprep6 -i $<

################################################################################
.PHONY: svf
svf: $(svf)
$(svf): $(jedec)
	cat impact.batch | impact -batch
	mv _impactbatch.log log/

################################################################################
.PHONY: usbprog
usbprog: $(svf)
	svfplayer $<

################################################################################
.PHONY: prog
prog: $(svf)
	openocd -l log/prog.log -d 1 -f interface/openocd-usb.cfg -c "adapter_khz 100" -c init -c "svf $<"

################################################################################
$(dirs):
	mkdir -p $@

################################################################################
.PHONY: clean
clean:
	rm -rf synth
	rm -rf log
	rm -f $(vhdlprj).jed
	rm -f tmperr.err
	rm -rf _xmsgs
	rm -f mucarex.svf
