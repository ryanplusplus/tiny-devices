add_library(tiny_devices INTERFACE)

target_sources(tiny_devices INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/src/aip1640_8x8_matrix.c
  ${CMAKE_CURRENT_LIST_DIR}/src/async_sht30.c
  ${CMAKE_CURRENT_LIST_DIR}/src/eeprom_24lc32.c
)

target_include_directories(tiny_devices INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

# Pull in pico libraries that we need
target_link_libraries(tiny_devices INTERFACE)
