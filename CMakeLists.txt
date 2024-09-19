cmake_minimum_required(VERSION 3.30.1)
project(Profiler)
set(CMAKE_CXX_STANDARD 23)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

set(TESTS_ROOT "${PROJECT_SOURCE_DIR}/tests")
set(SRC_ROOT "${PROJECT_SOURCE_DIR}/src")
set(RESOURCES_ROOT "${PROJECT_SOURCE_DIR}/resources")
set(RESOURCES_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/resources")
set(SHADER_COMPILER_DIR "C:/VulkanSDK/1.3.261.1/Bin/glslc.exe")
set(SHADER_ROOT "${SRC_ROOT}/shaders")
set(SHADER_OUTPUT_DIR "${RESOURCES_OUTPUT_DIR}/shaders")

set(CMAKE_EXE_LINKER_FLAGS "-static")

set(SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/include/imgui/imgui_tables.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/imgui/imgui.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/imgui/imgui_draw.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/imgui/imgui_widgets.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/imgui/imgui_impl_glfw.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/imgui/imgui_impl_vulkan.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/imgui/imgui_demo.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/implot/implot.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/implot/implot_items.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/implot/implot_demo.cpp"
)

set(SHADERS
)

set(RESOURCES
)

file(MAKE_DIRECTORY ${TESTS_ROOT} ${SRC_ROOT} ${RESOURCES_ROOT} ${RESOURCES_OUTPUT_DIR} ${SHADER_ROOT} ${SHADER_OUTPUT_DIR})

# SHADERS
foreach(SHADER ${SHADERS})
    string(REPLACE "${SHADER_ROOT}/" "" SHADER_NAME "${SHADER}")
    add_custom_command(
        OUTPUT "${SHADER_OUTPUT_DIR}/${SHADER_NAME}.spv"
        COMMAND "${SHADER_COMPILER_DIR}" "${SHADER}" -I"${CMAKE_CURRENT_SOURCE_DIR}/include" -o "${SHADER_OUTPUT_DIR}/${SHADER_NAME}.spv"
        DEPENDS "${SHADER}"
        COMMENT "Compiling Shader: ${SHADER_NAME}.spv"
    )
    list(APPEND SHADER_DEPEND "${SHADER_OUTPUT_DIR}/${SHADER_NAME}.spv")
endforeach()

add_custom_target(Shaders ALL DEPENDS ${SHADER_DEPEND})

# RESOURCES
foreach(RESOURCE ${RESOURCES})
    string(REPLACE "${RESOURCES_ROOT}/" "" RESOURCE_NAME "${RESOURCE}")
    add_custom_command(
        OUTPUT "${RESOURCES_OUTPUT_DIR}/${RESOURCE_NAME}"
        COMMAND ${CMAKE_COMMAND} -E copy "${RESOURCE}" "${RESOURCES_OUTPUT_DIR}/${RESOURCE_NAME}"
        DEPENDS "${RESOURCE}"
        COMMENT "Copying resource: ${RESOURCE_NAME}"
    )
    list(APPEND RESOURCE_DEPEND "${RESOURCES_OUTPUT_DIR}/${RESOURCE_NAME}")
endforeach()

add_custom_target(Resources ALL DEPENDS ${RESOURCE_DEPEND})

# ProfilerHost
add_executable(ProfilerHost WIN32 ${SRC} ${TESTS_ROOT}/Host.cpp)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(ProfilerHost PRIVATE VGraphics-d glfw3)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_link_libraries(ProfilerHost PRIVATE VGraphics glfw3)
endif()

target_precompile_headers(ProfilerHost PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/VG/VG.h")

target_include_directories(ProfilerHost PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_link_directories(ProfilerHost PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/"
)
add_dependencies(ProfilerHost Shaders Resources)

# ProfilerClient
add_executable(ProfilerClient ${TESTS_ROOT}/Client.cpp)

target_include_directories(ProfilerClient PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_link_directories(ProfilerClient PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/"
)

add_custom_target(ServerAndClient
    COMMAND start $<TARGET_FILE:ProfilerHost> && start $<TARGET_FILE:ProfilerClient>
    DEPENDS ProfilerHost ProfilerClient
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)