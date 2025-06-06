cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(test_module)
zephyr_compile_definitions(PROJECT_NAME=${PROJECT_NAME})

# add location_module (the unit under test)
target_sources(app
    PRIVATE
    ../mainTemplate.c
	../drvr/src/msgqTemplate.c
	../drvr/src/wdtTemplate.c
	../drvr/src/template.c
	../drvr/src/zbusTemplate.c
	../../../common/zbusCommon.c
)

zephyr_include_directories(${ZEPHYR_BASE}/include/zephyr/)
zephyr_include_directories(${ZEPHYR_BASE}/subsys/testsuite/include)
target_include_directories(app PRIVATE ../drvr/inc)
target_include_directories(app PRIVATE ../../../common/inc)

target_link_options(app PRIVATE --whole-archive)

# add test file
target_sources(app PRIVATE src/testTemplate.c)
