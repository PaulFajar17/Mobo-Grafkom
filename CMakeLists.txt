cmake_minimum_required(VERSION 3.10)
project(OpenGLSetup)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_definitions(-DGL_SILENCE_DEPRECATION)

# Find GLFW
find_package(glfw3 3.3 REQUIRED)

# Include directories
include_directories(include)
include_directories(glm)

# Add executable
add_executable(OpenGLSetup src/main.cpp src/glad.c)

# Link libraries
# Link libraries
target_link_libraries(OpenGLSetup glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Exercise 1
add_executable(Exercise1 src/exercise1.cpp src/glad.c)
target_link_libraries(Exercise1 glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Exercise 2
add_executable(Exercise2 src/exercise2.cpp src/glad.c)
target_link_libraries(Exercise2 glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Exercise 3
add_executable(Exercise3 src/exercise3.cpp src/glad.c)
target_link_libraries(Exercise3 glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Shader Exercise 1
add_executable(ShaderExercise1 src/shader_exercise1.cpp src/glad.c)
target_link_libraries(ShaderExercise1 glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Shader Exercise 2
add_executable(ShaderExercise2 src/shader_exercise2.cpp src/glad.c)
target_link_libraries(ShaderExercise2 glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Shader Exercise 3
add_executable(ShaderExercise3 src/shader_exercise3.cpp src/glad.c)
target_link_libraries(ShaderExercise3 glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# GLM (local header-only library)

# Transform Main (Latihan Utama - Transformations)
add_executable(TransformMain src/transform_main.cpp src/glad.c)
target_link_libraries(TransformMain glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Transform Exercise 1 (Swap Transform Order)
add_executable(TransformExercise1 src/transform_exercise1.cpp src/glad.c)
target_link_libraries(TransformExercise1 glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Transform Exercise 2 (Second Container with Sin Scale)
add_executable(TransformExercise2 src/transform_exercise2.cpp src/glad.c)
target_link_libraries(TransformExercise2 glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Texture Main (Latihan Utama - Textures)
add_executable(TextureMain src/texture_main.cpp src/glad.c)
target_link_libraries(TextureMain glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Texture Exercise 1 (Flip Happy Face)
add_executable(TextureExercise1 src/texture_exercise1.cpp src/glad.c)
target_link_libraries(TextureExercise1 glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Texture Exercise 2 (Wrapping Modes)
add_executable(TextureExercise2 src/texture_exercise2.cpp src/glad.c)
target_link_libraries(TextureExercise2 glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Texture Exercise 3 (Center Pixels Only)
add_executable(TextureExercise3 src/texture_exercise3.cpp src/glad.c)
target_link_libraries(TextureExercise3 glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Texture Exercise 4 (Mix with Arrow Keys)
add_executable(TextureExercise4 src/texture_exercise4.cpp src/glad.c)
target_link_libraries(TextureExercise4 glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Coordinate Systems Main
add_executable(CoordinateSystemsMain src/coordinate_systems_main.cpp src/glad.c)
target_link_libraries(CoordinateSystemsMain glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Coordinate Systems Exercise 1
add_executable(CoordinateSystemsExercise1 src/coordinate_systems_exercise1.cpp src/glad.c)
target_link_libraries(CoordinateSystemsExercise1 glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Coordinate Systems Exercise 2
add_executable(CoordinateSystemsExercise2 src/coordinate_systems_exercise2.cpp src/glad.c)
target_link_libraries(CoordinateSystemsExercise2 glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Coordinate Systems Exercise 3
add_executable(CoordinateSystemsExercise3 src/coordinate_systems_exercise3.cpp src/glad.c)
target_link_libraries(CoordinateSystemsExercise3 glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Camera Main
add_executable(CameraMain src/camera_main.cpp src/glad.c)
target_link_libraries(CameraMain glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Camera Exercise 1 (FPS Camera)
add_executable(CameraExercise1 src/camera_exercise1.cpp src/glad.c)
target_link_libraries(CameraExercise1 glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Camera Exercise 2 (Custom LookAt)
add_executable(CameraExercise2 src/camera_exercise2.cpp src/glad.c)
target_link_libraries(CameraExercise2 glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Tugas Mandiri: Persegi
add_executable(TugasPersegi src/tugas_persegi.cpp src/glad.c)
target_link_libraries(TugasPersegi glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Basic Lighting Main
add_executable(BasicLightingMain src/basic_lighting_main.cpp src/glad.c)
target_link_libraries(BasicLightingMain glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Basic Lighting Exercise 1 (Moving Light)
add_executable(BasicLightingExercise1 src/basic_lighting_exercise1.cpp src/glad.c)
target_link_libraries(BasicLightingExercise1 glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Basic Lighting Exercise 2 (Different Strengths)
add_executable(BasicLightingExercise2 src/basic_lighting_exercise2.cpp src/glad.c)
target_link_libraries(BasicLightingExercise2 glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Basic Lighting Exercise 3 (View Space)
add_executable(BasicLightingExercise3 src/basic_lighting_exercise3.cpp src/glad.c)
target_link_libraries(BasicLightingExercise3 glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Basic Lighting Exercise 4 (Gouraud Shading)
add_executable(BasicLightingExercise4 src/basic_lighting_exercise4.cpp src/glad.c)
target_link_libraries(BasicLightingExercise4 glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Materials Main
add_executable(MaterialsMain src/materials_main.cpp src/glad.c)
target_link_libraries(MaterialsMain glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Materials Exercise 1
add_executable(MaterialsExercise1 src/materials_exercise1.cpp src/glad.c)
target_link_libraries(MaterialsExercise1 glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Materials Exercise 2 (Cyan Plastic)
add_executable(MaterialsExercise2 src/materials_exercise2.cpp src/glad.c)
target_link_libraries(MaterialsExercise2 glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Lighting Maps Main
add_executable(LightingMapsMain src/lighting_maps_main.cpp src/glad.c)
target_link_libraries(LightingMapsMain glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Lighting Maps Exercise 1 (Invert Specular)
add_executable(LightingMapsExercise1 src/lighting_maps_exercise1.cpp src/glad.c)
target_link_libraries(LightingMapsExercise1 glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Lighting Maps Exercise 2 (Colored Specular)
add_executable(LightingMapsExercise2 src/lighting_maps_exercise2.cpp src/glad.c)
target_link_libraries(LightingMapsExercise2 glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Lighting Maps Exercise 3 (Emission Map)
add_executable(LightingMapsExercise3 src/lighting_maps_exercise3.cpp src/glad.c)
target_link_libraries(LightingMapsExercise3 glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Multiple Lights Exercise 1 (Atmospheres)
add_executable(MultipleLightsExercise1 src/multiple_lights_exercise1.cpp src/glad.c)
target_link_libraries(MultipleLightsExercise1 glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

# Find Assimp
find_package(assimp REQUIRED)

# Model Loading Main
add_executable(ModelLoadingMain src/model_loading_main.cpp src/glad.c)
target_link_libraries(ModelLoadingMain glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL" assimp::assimp)

# Tugas Akhir
add_executable(TugasAkhir src/tugas_akhir.cpp src/glad.c)
target_link_libraries(TugasAkhir glfw "-framework IOKit" "-framework Cocoa" "-framework OpenGL" assimp::assimp)
