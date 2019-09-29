
execute_process(
    COMMAND python3 index.py binding
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    OUTPUT_VARIABLE binding_sources
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND python3 index.py input
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    OUTPUT_VARIABLE input_sources
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

foreach(input_file ${input_sources})
    execute_process(
        COMMAND python3 index.py cmake_output ${input_file}
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        OUTPUT_VARIABLE input_file_target
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    list(APPEND output_sources ${CMAKE_CURRENT_BINARY_DIR}/${input_file_target})
    add_custom_command(
        OUTPUT
            ${CMAKE_CURRENT_BINARY_DIR}/${input_file_target}
        COMMAND
            python3 index.py gen ${input_file} > ${CMAKE_CURRENT_BINARY_DIR}/${input_file_target}
        VERBATIM
    )
    add_custom_target(
        target_${input_file_target}
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${input_file_target}
    )
    set_source_files_properties(
        ${CMAKE_CURRENT_BINARY_DIR}/${input_file_target}
        PROPERTIES GENERATED TRUE
    )
endforeach()

set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
    ${input_sources} ${binding_sources}
)

execute_process(
    COMMAND python3 index.py genlist ${sources_sources}
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)

add_library(SchizoMania_Binding
    ${output_sources}
)