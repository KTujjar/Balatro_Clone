cmake_minimum_required(VERSION 3.16)
project(Balatro_Clone)
set(CMAKE_CXX_STANDARD 17)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# --------------------------
# FreeType (vendored)
# --------------------------
set(FT_DISABLE_HARFBUZZ TRUE CACHE BOOL "Disable HarfBuzz" FORCE)
add_subdirectory(vendored/freetype EXCLUDE_FROM_ALL)

set(FREETYPE_INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}/vendored/freetype/include
    ${CMAKE_BINARY_DIR}/vendored/freetype/include
    CACHE STRING "" FORCE
)

# Make an alias target for convenience

set(FREETYPE_LIBRARIES freetype CACHE STRING "" FORCE)

add_library(Freetype::Freetype ALIAS freetype)


# --------------------------
# SDL libraries
# --------------------------
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL_ttf EXCLUDE_FROM_ALL)

# --------------------------
# Project sources
# --------------------------
set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/Card.cpp
    src/Hand.cpp
    src/Deck.cpp
    src/Button.cpp
    src/Score.cpp
)

file(GLOB TMXLITE_SOURCES
    external/tmxlite/src/*.cpp
    external/tmxlite/src/*.c
)

# Copy assets
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Create executable
add_executable(Balatro_Clone WIN32 ${SOURCES})
target_sources(Balatro_Clone PRIVATE ${TMXLITE_SOURCES})

# Include directories
target_include_directories(Balatro_Clone PRIVATE
    external/tmxlite/include
    ${FREETYPE_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(Balatro_Clone PRIVATE
    Freetype::Freetype
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
)