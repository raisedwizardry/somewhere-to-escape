PROJECT_NAME = somewheretoescape
TITLE = "Somewhere to Escape"

BUILD_DIR = build
ASSETS_DIR = assets
FILESYSTEM_DIR = filesystem

include $(N64_INST)/include/n64.mk
include $(N64_INST)/include/t3d.mk
include $(N64_INST)/include/bullet.mk

N64_CXXFLAGS += -std=gnu++20 -Os -fno-exceptions

src = $(wildcard src/*.cpp) $(wildcard src/actors/*.cpp) $(wildcard src/actors/models/*.cpp) $(wildcard src/physics/*.cpp) $(wildcard src/scene/*.cpp) $(wildcard src/utility/*.cpp)

assets_png = $(wildcard $(ASSETS_DIR)/*.png)
assets_gtf = $(wildcard $(ASSETS_DIR)/*.gltf)
assets_ttf = $(wildcard $(ASSETS_DIR)/*.ttf)
assets_mp3 = $(wildcard $(ASSETS_DIR)/*.mp3)
assets_wav = $(wildcard $(ASSETS_DIR)/*.wav)

assets_conv = $(addprefix $(FILESYSTEM_DIR)/,$(notdir $(assets_png:%.png=%.sprite))) \
			  $(addprefix $(FILESYSTEM_DIR)/,$(notdir $(assets_gtf:%.gltf=%.t3dm))) \
			  $(addprefix $(FILESYSTEM_DIR)/,$(notdir $(assets_ttf:%.ttf=%.font64))) \
			  $(addprefix $(FILESYSTEM_DIR)/,$(notdir $(assets_mp3:%.mp3=%.wav64))) \
			  $(addprefix $(FILESYSTEM_DIR)/,$(notdir $(assets_wav:%.wav=%.wav64))) \

all: $(PROJECT_NAME).z64

$(FILESYSTEM_DIR)/%.sprite: $(ASSETS_DIR)/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	$(N64_MKSPRITE) $(MKSPRITE_FLAGS) -o $(dir $@) "$<"

$(FILESYSTEM_DIR)/%.font64: $(ASSETS_DIR)/%.ttf
	@mkdir -p $(dir $@)
	@echo "    [FONT] $@"
	$(N64_MKFONT) $(MKFONT_FLAGS) -o $(dir $@) "$<"

$(FILESYSTEM_DIR)/%.t3dm: $(ASSETS_DIR)/%.glb
	@mkdir -p $(dir $@)
	@echo "    [T3D-MODEL] $@"
	$(T3D_GLTF_TO_3D) $(T3DM_FLAGS) "$<" $@
	$(N64_BINDIR)/mkasset -c 2 -o $(dir $@) $@

$(FILESYSTEM_DIR)/%.t3dm: $(ASSETS_DIR)/%.gltf
	@mkdir -p $(dir $@)
	@echo "    [T3D-MODEL] $@"
	$(T3D_GLTF_TO_3D) $(T3DM_FLAGS) "$<" $@
	$(N64_BINDIR)/mkasset -c 2 -o $(dir $@) $@

AUDIOCONV_FLAGS = --wav-resample 22050 --wav-mono

$(FILESYSTEM_DIR)/%.wav64: $(ASSETS_DIR)/%.wav
	@mkdir -p $(dir $@)
	@echo "    [SFX] $@"
	$(N64_AUDIOCONV) $(AUDIOCONV_FLAGS) --wav-compress 0 -o $(dir $@) "$<"

$(FILESYSTEM_DIR)/%.wav64: $(ASSETS_DIR)/%.mp3
	@mkdir -p $(dir $@)
	@echo "    [SFX] $@"
	$(N64_AUDIOCONV) $(AUDIOCONV_FLAGS) -o $(dir $@) "$<"

$(FILESYSTEM_DIR)/%.xm64: $(ASSETS_DIR)/%.xm
	@mkdir -p $(dir $@)
	@echo "    [XM] $@"
	$(N64_AUDIOCONV) $(AUDIOCONV_FLAGS) -o $(dir $@) "$<"

$(BUILD_DIR)/$(PROJECT_NAME).dfs: $(assets_conv)
$(BUILD_DIR)/$(PROJECT_NAME).elf: $(src:%.cpp=$(BUILD_DIR)/%.o)

$(PROJECT_NAME).z64: N64_ROM_TITLE=$(TITLE)
$(PROJECT_NAME).z64: $(BUILD_DIR)/$(PROJECT_NAME).dfs

clean:
	rm -rf $(BUILD_DIR) $(FILESYSTEM_DIR) $(PROJECT_NAME).z64

-include $(wildcard $(BUILD_DIR)/src/*.d)

.PHONY: all clean
