CC ?= cc
C_FLAGS := -std=gnu11 $\
					 -O2 -march=native -pipe $\
					 -Wall -Wextra -Wpedantic $\
					 -Iinclude
LD_FLAGS := ${C_FLAGS}

OBJECT_FILES := $(patsubst src/%.c,$\
									build/%.o,$\
									$(shell find src -name '*.c'))
PROCESSED_HEADER_FILES := $(subst .h,$\
														$(if $(findstring clang,${CC}),$\
															.h.pch,$\
															.h.gch),$\
														$(shell find include -name '*.h'))

define REMOVE
	$(if $(wildcard $(1)),$\
		$(info Removing $(1))$\
		$(shell rm $(1)))
endef
define REMOVE_LIST
	$(foreach ITEM,$\
		$(1),$\
		$(call REMOVE,${ITEM}))
endef

all: pidmon

pidmon: ${PROCESSED_HEADER_FILES} ${OBJECT_FILES}
	$(info Linking $@)
	@${CC} ${OBJECT_FILES} ${LD_FLAGS} -o $@

%.h.gch: %.h
	$(info Compiling $@)
	@${CC} $< ${C_FLAGS} -o $@
%.h.pch: %.h
	$(info Compiling $@)
	@${CC} $< ${C_FLAGS} -o $@

build/%.o: src/%.c
	$(info Compiling $@)
	@${CC} -c $< ${C_FLAGS} -o $@

clean:
	$(call REMOVE,pidmon)
	$(call REMOVE_LIST,${OBJECT_FILES})

.PHONY: all clean
