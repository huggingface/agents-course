idf_component_register(
    SRCS "main.c" "i2s_config.c" "wake_word_detector.c"
    INCLUDE_DIRS "."
    REQUIRES esp-sr
)
