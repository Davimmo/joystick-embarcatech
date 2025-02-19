# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

include(pico_sdk_import.cmake)
project(joystick-embarcatech C CXX ASM)
pico_sdk_init()

file(GLOB LIBSOURCES "include/*.c")
file(GLOB SRCSOURCES "src/*.c")

add_executable(joystick-embarcatech ${SRCSOURCES} ${LIBSOURCES} )

pico_set_program_name(joystick-embarcatech "joystick-embarcatech")
pico_set_program_version(joystick-embarcatech "0.1")


pico_enable_stdio_uart(joystick-embarcatech 1)
pico_enable_stdio_usb(joystick-embarcatech 1)

target_link_libraries(joystick-embarcatech
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(joystick-embarcatech PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(joystick-embarcatech 
        hardware_clocks
        hardware_pwm
        hardware_i2c
        hardware_adc
        )

pico_add_extra_outputs(joystick-embarcatech)

