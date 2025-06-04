CXXFLAGS = -O3 -ffinite-math-only -funsafe-math-optimizations -masm=intel \
	-MMD -MT $@ -MF $(DEPS_DIR)/$*.d

SOURCES_DIR := src
OUTPUT_DIR := out
OBJECTS_DIR := $(OUTPUT_DIR)/obj
DEPS_DIR := $(OUTPUT_DIR)/dep

DIFF_SCRIPT := tools/diff.py
GENERATE_LINKER_SCRIPT_SCRIPT := tools/generate_linker_script.py
GET_IGNORED_SYMBOLS_SCRIPT := tools/get_ignored_symbols.py

SOURCES := $(addprefix $(SOURCES_DIR)/,bounding_box.cpp critical_section.cpp error.cpp flash_movie_clip.cpp flash_timeline.cpp matrix4x4.cpp system.cpp vector2.cpp)
OBJECTS := $(patsubst src/%.cpp,$(OBJECTS_DIR)/%.o,$(SOURCES))
DEPS := $(patsubst src/%.cpp,$(DEPS_DIR)/%.d,$(SOURCES))
LINKER_SCRIPT_TEMPLATE := script.ld.template
LINKER_SCRIPT := $(OUTPUT_DIR)/script.ld
BINARY := $(OUTPUT_DIR)/SuperMeatBoy

ORIGINAL_BINARY ?= SuperMeatBoy

.PHONY: all
all: $(BINARY)

$(OBJECTS_DIR) $(DEPS_DIR):
	mkdir -p $@

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.cpp | $(OBJECTS_DIR) $(DEPS_DIR)
	gcc-4.6 -c $< $(CXXFLAGS) -o $@

include $(wildcard $(DEPS))

$(LINKER_SCRIPT): $(GENERATE_LINKER_SCRIPT_SCRIPT) $(LINKER_SCRIPT_TEMPLATE) $(OBJECTS)
	$(GENERATE_LINKER_SCRIPT_SCRIPT) \
		-i $(LINKER_SCRIPT_TEMPLATE) \
		-o $(LINKER_SCRIPT) \
		-b $(OBJECTS)

$(BINARY): $(OBJECTS) $(LINKER_SCRIPT) $(GET_IGNORED_SYMBOLS_SCRIPT)
	mkdir -p $(dir $(BINARY))
	ld -T $(LINKER_SCRIPT) $(OBJECTS) -o $(BINARY)
	strip $(BINARY) --strip-debug $(addprefix -N ,$(shell $(GET_IGNORED_SYMBOLS_SCRIPT) $(OBJECTS)))

.PHONY: clean
clean:
	rm -r $(OUTPUT_DIR)

.PHONY: diff
diff: $(DIFF_SCRIPT) $(BINARY)
	$(DIFF_SCRIPT) -c $(BINARY) -o $(ORIGINAL_BINARY)
