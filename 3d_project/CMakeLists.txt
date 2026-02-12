cmake_minimum_required(VERSION 3.15)
project(OpenGLTest)

set(CMAKE_TOOLCHAIN_FILE "C:/Users/admin/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Явно указываем пути к установленным библиотекам
set(VCPKG_INSTALLED_DIR "C:/Users/admin/vcpkg/installed/x64-windows")

# Включаем директории
include_directories(
    ${VCPKG_INSTALLED_DIR}/include
)

# Директории для библиотек  
link_directories(
    ${VCPKG_INSTALLED_DIR}/lib
)

add_executable(opengl_test src/main.cpp)

# Связываем конкретные библиотеки (именно так они называются в Windows)
target_link_libraries(opengl_test 
    opengl32
    glu32
    glfw3
    glew32
    gdi32
)