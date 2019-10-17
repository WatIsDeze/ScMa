
set(CMAKE_CXX_VISIBILITY_PRESET default)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 0)

execute_process(
    COMMAND /usr/local/bin/python3 index.py binding
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    OUTPUT_VARIABLE binding_sources
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND /usr/local/bin/python3 index.py input
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    OUTPUT_VARIABLE input_sources
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
    ${binding_sources}
)

execute_process(
    COMMAND /usr/local/bin/python3 index.py genlist ${sources_sources}
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)


foreach(input_file ${input_sources})
    execute_process(
        COMMAND /usr/local/bin/python3 index.py cmake_output ${input_file}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_VARIABLE input_file_target
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    get_filename_component(output_file_target ${CMAKE_CURRENT_BINARY_DIR}/${input_file_target} ABSOLUTE)

    list(APPEND output_sources ${output_file_target})
    message(">> ${input_file} => ${output_file_target} (${input_file_target})")

    add_custom_command(
        OUTPUT command_${input_file_target}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND
        /usr/local/bin/python3 index.py gen ${input_file} ${output_file_target}
        COMMENT "Preprocessing ${input_file}"
    )
    add_custom_target(
        target_${input_file_target}
        DEPENDS
            command_${input_file_target}
        VERBATIM
    )

    set_source_files_properties(
        ${output_file_target}
        PROPERTIES
            GENERATED TRUE
            DEPENDS target_${input_file_target}
            OBJECT_DEPENDS ${input_file}
    )
endforeach()

# message("output_sources ${output_sources}")

add_library(SchizoMania_Binding
    STATIC
        ${output_sources}
)
set(SchizoMania_Binding_Binary /Users/micha/dev/ScMaMike/bscriptbinding/binding/Debug/libSchizoMania_Binding.a)
# get_property(SchizoMania_Binding_Binary TARGET SchizoMania_Binding PROPERTY LOCATION)

set_target_properties(SchizoMania_Binding PROPERTIES LINKER_LANGUAGE CXX)

if (APPLE)
    target_link_options(SchizoMania_Binding PUBLIC
        SHELL:-Wl,-all_load $<TARGET_FILE:SchizoMania_Binding>
    )
elseif(LINUX)
    target_link_options(SchizoMania_Binding PUBLIC
        SHELL:-Wl,--whole-archive $<TARGET_FILE:SchizoMania_Binding> -Wl,--no-whole-archive
    )
elseif(WIN32)
    target_link_options(SchizoMania_Binding PUBLIC
        /WHOLEARCHIVE:$<TARGET_FILE:SchizoMania_Binding>
    )
endif()


target_include_directories(SchizoMania_Binding
    PRIVATE
        ../
)

target_link_libraries(SchizoMania_Binding
    PRIVATE
        SchizoMania_Shared_Client    
)

foreach(input_file ${input_sources})
    execute_process(
        COMMAND /usr/local/bin/python3 index.py cmake_output ${input_file}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_VARIABLE input_file_target
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    get_filename_component(output_file_target ${CMAKE_CURRENT_BINARY_DIR}/${input_file_target} ABSOLUTE)

    add_dependencies(SchizoMania_Binding target_${input_file_target})
endforeach()