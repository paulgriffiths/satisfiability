# satisfiability makefile
# =======================
# Copyright 2017 Paul Griffiths
# Email: mail@paulgriffiths.net
#
# Distributed under the terms of the GNU General Public License.
# http://www.gnu.org/licenses/


prog		 	:= satisfy
sources      	:= $(wildcard *.c)
objects       	 = $(subst .c,.o,$(sources))
depends       	 = $(subst .c,.d,$(sources))

CFLAGS  = -std=c99 -pedantic -Wall -Wextra -ggdb

default: main

# clean - removes ancilliary files from working directory
.PHONY: clean
clean:
	-@rm $(objects) $(depends) $(prog) 2>/dev/null

# tags - makes tags file
.PHONY: tags
tags:
	@ctags *.c *.g


# Executable targets section
# ==========================

# Main executable
.PHONY: main
main: $(prog)

$(prog): $(objects)
	@echo "Building program..."
	$(CC) -o $@ $^
	@echo "Done."


# Dependencies
# ============

-include $(depends)

%.d: %.c
	@echo "Building dependencies for $<..."
	@$(CC) -M $(CFLAGS) $< > $@.tmp; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.tmp > $@; \
		rm -f $@.tmp

