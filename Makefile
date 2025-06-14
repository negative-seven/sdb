CXXFLAGS = -O3 -std=c++0x -ffinite-math-only -funsafe-math-optimizations -masm=intel \
	-MMD -MT $@ -MF $(DEPS_DIR)/$*.d

SOURCES_DIR := src
OUTPUT_DIR := out
OBJECTS_DIR := $(OUTPUT_DIR)/obj
DEPS_DIR := $(OUTPUT_DIR)/dep

DIFF_SCRIPT := tools/diff.py
GENERATE_LINKER_SCRIPT_SCRIPT := tools/generate_linker_script.py
GET_IGNORED_SYMBOLS_SCRIPT := tools/get_ignored_symbols.py

SOURCES := $(shell find $(SOURCES_DIR) -name '*.cpp')
OBJECTS := $(patsubst src/%.cpp,$(OBJECTS_DIR)/%.o,$(SOURCES))
DEPS := $(patsubst src/%.cpp,$(DEPS_DIR)/%.d,$(SOURCES))
LINKER_SCRIPT_TEMPLATE := script.ld.template
LINKER_SCRIPT := $(OUTPUT_DIR)/script.ld
BINARY := $(OUTPUT_DIR)/SuperMeatBoy

ORIGINAL_BINARY ?= SuperMeatBoy

.PHONY: all
all: $(BINARY)

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.cpp
	mkdir -p $(dir $(DEPS_DIR)/$*.d)
	mkdir -p $(dir $(OBJECTS_DIR)/$*.d)
	g++-4.6 -c $< $(CXXFLAGS) -o $@

include $(wildcard $(DEPS))

$(LINKER_SCRIPT): $(GENERATE_LINKER_SCRIPT_SCRIPT) $(LINKER_SCRIPT_TEMPLATE) $(OBJECTS)
	$(GENERATE_LINKER_SCRIPT_SCRIPT) \
		-i $(LINKER_SCRIPT_TEMPLATE) \
		-o $(LINKER_SCRIPT) \
		-b $(OBJECTS)

$(BINARY): $(OBJECTS) $(LINKER_SCRIPT) $(GET_IGNORED_SYMBOLS_SCRIPT)
	mkdir -p $(dir $(BINARY))
	g++-4.6 -T $(LINKER_SCRIPT) $(OBJECTS) -o $(BINARY)
	strip $(BINARY) --strip-debug $(addprefix -N ,$(shell $(GET_IGNORED_SYMBOLS_SCRIPT) $(OBJECTS)))

.PHONY: clean
clean:
	rm -r $(OUTPUT_DIR)

.PHONY: diff
diff: $(DIFF_SCRIPT) $(BINARY)
	$(DIFF_SCRIPT) -c $(BINARY) -o $(ORIGINAL_BINARY)
