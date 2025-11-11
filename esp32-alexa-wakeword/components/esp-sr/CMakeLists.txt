# ESP-SR Component Placeholder
# 
# To use real ESP-SR library:
# 1. Clone ESP-SR: git clone https://github.com/espressif/esp-sr.git
# 2. Replace this directory with the cloned esp-sr
# 3. Or add esp-sr as a git submodule

idf_component_register(
    SRCS "esp_sr_placeholder.c"
    INCLUDE_DIRS "include"
)
