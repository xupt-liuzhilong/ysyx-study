TOPNAME = top

# ==================== RTL Sources ====================

VSRCS = $(shell find $(abspath ./vsrc) -name "*.v")

# ==================== Verilator Simulation ====================

SIM_CSRC = $(abspath ./csrc/main.cpp)
SIM_BIN = obj_dir/V$(TOPNAME)

SIM_FLAGS = --cc --exe --build -j 0 -Wall \
            --trace-fst \
            --top-module $(TOPNAME)

sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	verilator $(SIM_FLAGS) $(SIM_CSRC) $(VSRCS)
	./$(SIM_BIN)

# ==================== NVBoard ====================

NXDC_FILES = constr/top.nxdc

NV_BUILD_DIR = ./build
NV_OBJ_DIR = $(NV_BUILD_DIR)/obj_dir
NV_BIN = $(NV_BUILD_DIR)/$(TOPNAME)

NVBOARD_CSRC = $(abspath ./csrc/nvboard_main.cpp)

SRC_AUTO_BIND = $(abspath $(NV_BUILD_DIR)/auto_bind.cpp)

$(shell mkdir -p $(NV_BUILD_DIR))

$(SRC_AUTO_BIND): $(NXDC_FILES)
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@

include $(NVBOARD_HOME)/scripts/nvboard.mk

INCFLAGS = $(addprefix -I, $(INC_PATH))
CXXFLAGS += $(INCFLAGS)

NV_VERILATOR_FLAGS = -MMD --build -cc \
                     -O3 --x-assign fast --x-initial fast --noassert

$(NV_BIN): $(VSRCS) $(NVBOARD_CSRC) $(SRC_AUTO_BIND) $(NVBOARD_ARCHIVE)
	@rm -rf $(NV_OBJ_DIR)
	verilator $(NV_VERILATOR_FLAGS) \
		--top-module $(TOPNAME) $^ \
		$(addprefix -CFLAGS , $(CXXFLAGS)) \
		$(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(NV_OBJ_DIR) \
		--exe -o $(abspath $(NV_BIN))

nvboard: $(NV_BIN)
	@$(NV_BIN)

# ==================== Other ====================

all: sim

clean:
	rm -rf obj_dir build wave.fst

.PHONY: all sim nvboard clean

include ../Makefile
