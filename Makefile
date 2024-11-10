CC ?= cc
C_FLAGS := -std=c99 $\
					 -O2 -march=native -pipe $\
					 -Wall -Wextra -Wpedantic $\
					 -Iinclude
LD_FLAGS := ${C_FLAGS}

OBJECT_FILES := $(patsubst src/%.c,$\
									build/%.o,$\
									$(shell find src -name '*.c'))

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

all: sysmon

sysmon: ${OBJECT_FILES}
	$(info Linking $@)
	@${CC} $< ${LD_FLAGS} -o $@

build/%.o: src/%.c
	$(info Compiling $@)
	@${CC} -c $< ${C_FLAGS} -o $@

clean:
	$(call REMOVE,sysmon)
	$(call REMOVE_LIST,${OBJECT_FILES})

.PHONY: all clean
