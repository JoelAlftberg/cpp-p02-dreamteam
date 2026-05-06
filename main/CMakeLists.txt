idf_component_register(
    SRCS
        "source/main.cpp"
        "source/driver/adc/esp32s3.cpp"
        "source/driver/factory/esp32s3.cpp"
        "source/driver/gpio/esp32s3.cpp"
        "source/driver/serial/esp32s3.cpp"
        "source/driver/tempsensor/esp32s3.cpp"
        "source/driver/timer/esp32s3.cpp"
    INCLUDE_DIRS
        "include"
        INCLUDE_DIRS "."
        REQUIRES esp_driver_tsens
        )
