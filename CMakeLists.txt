# Add include directory
target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/drvr/inc)

# Add source files
target_sources(app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/mainTemplate.c
    ${CMAKE_CURRENT_SOURCE_DIR}/drvr/src/zbusTemplate.c
    ${CMAKE_CURRENT_SOURCE_DIR}/drvr/src/msgqTemplate.c
    ${CMAKE_CURRENT_SOURCE_DIR}/drvr/src/wdtTemplate.c
    ${CMAKE_CURRENT_SOURCE_DIR}/drvr/src/template.c
)

# Conditionally add shell source
if(CONFIG_APP_TEMPLATE_SHELL)
    target_sources(app PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/shell/src/shellTemplate.c
    )
endif()