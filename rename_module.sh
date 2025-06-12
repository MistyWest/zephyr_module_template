#!/bin/bash

# This is a one time use script after cloning Zephyr Template to rename the module
# Running it a second time will have no effect

TOP_LVL_DIR="."
NEW_MODULE_NAME=$1
NEW_MODULE_NAME_UPR_CASE="${NEW_MODULE_NAME^^}"
NEW_MODULE_NAME_LWR_CASE="${NEW_MODULE_NAME,,}"
NEW_MODULE_NAME_CAP_FIRST="${NEW_MODULE_NAME_LWR_CASE^}"
NEW_MODULE_NAME_UPR_CML_CASE=$(echo "$NEW_MODULE_NAME" | awk -F'_' '{for(i=1;i<=NF;i++) printf "%s%s", toupper(substr($i,1,1)), tolower(substr($i,2))}')
NEW_MODULE_NAME_LWR_CML_CASE="${NEW_MODULE_NAME_UPR_CML_CASE,}"


DFLT_MODULE_NAME="template"
MSGQ_FILE="msgq"
ZBUS_FILE="zbus"
WDT_FILE="wdt"
SHELL_FILE="shell"

echo "NEW_MODULE_NAME":$NEW_MODULE_NAME
echo "NEW_MODULE_NAME_UPR_CASE":$NEW_MODULE_NAME_UPR_CASE
echo "NEW_MODULE_NAME_LWR_CASE":$NEW_MODULE_NAME_LWR_CASE
echo "NEW_MODULE_NAME_CAP_FIRST":$NEW_MODULE_NAME_CAP_FIRST
echo "NEW_MODULE_NAME_UPR_CML_CASE":$NEW_MODULE_NAME_UPR_CML_CASE
echo "NEW_MODULE_NAME_LWR_CML_CASE":$NEW_MODULE_NAME_LWR_CML_CASE


# Check if argument provided
if [ -z "$NEW_MODULE_NAME" ]; then
    echo "❌ Error: Usage is $0 <new_module_name>"
    exit 1
fi

cd "$TOP_LVL_DIR" || { echo "❌ Cannot cd to $TOP_LVL_DIR"; exit 1; }


#### Rename Files #####################################################################################################


# Rename the mainTemplate.c
if [ ! -f "main${DFLT_MODULE_NAME^}.c" ]; then
    echo "❌ Error: File 'main${DFLT_MODULE_NAME^}.c' does not exist in $TOP_LVL_DIR"
    exit 1
fi
mv "main${DFLT_MODULE_NAME^}.c" "main${NEW_MODULE_NAME_UPR_CML_CASE}.c"
echo "✅ Renamed: main${DFLT_MODULE_NAME^}.c ➝ main${NEW_MODULE_NAME_UPR_CML_CASE}.c"

# Rename the drvr/inc/template.h >> drvr/inc/newModuleName.h
if [ ! -f "drvr/inc/${DFLT_MODULE_NAME}.h" ]; then
    echo "❌ Error: File 'drvr/inc/${DFLT_MODULE_NAME}.h' does not exist"
    exit 1
fi
mv "drvr/inc/${DFLT_MODULE_NAME}.h" "drvr/inc/${NEW_MODULE_NAME_LWR_CML_CASE}.h"
echo "✅ Renamed: drvr/inc/${DFLT_MODULE_NAME}.h ➝ drvr/inc/${NEW_MODULE_NAME_LWR_CML_CASE}.h"

# Rename the drvr/src/template.c >> drvr/src/newModuleName.c
if [ ! -f "drvr/src/${DFLT_MODULE_NAME}.c" ]; then
    echo "❌ Error: File 'drvr/src/${DFLT_MODULE_NAME}.c' does not exist"
    exit 1
fi
mv "drvr/src/${DFLT_MODULE_NAME}.c" "drvr/src/${NEW_MODULE_NAME_LWR_CML_CASE}.c"
echo "✅ Renamed: drvr/src/${DFLT_MODULE_NAME}.c ➝ drvr/scr/${NEW_MODULE_NAME_LWR_CML_CASE}.c"

# Rename the drvr/inc/msgqTemplate.h >> drvr/inc/msgqNewModuleName.h
if [ ! -f "drvr/inc/${MSGQ_FILE}${DFLT_MODULE_NAME^}.h" ]; then
    echo "❌ Error: File 'drvr/inc/${MSGQ_FILE}${DFLT_MODULE_NAME^}.h' does not exist"
    exit 1
fi
mv "drvr/inc/${MSGQ_FILE}${DFLT_MODULE_NAME^}.h" "drvr/inc/${MSGQ_FILE}${NEW_MODULE_NAME_UPR_CML_CASE}.h"
echo "✅ Renamed: drvr/inc/${MSGQ_FILE}${DFLT_MODULE_NAME^}.h ➝ drvr/inc/${MSGQ_FILE}${NEW_MODULE_NAME_UPR_CML_CASE}.h"

# Rename the drvr/src/msgqTemplate.c >> drvr/src/msgqNewModuleName.c
if [ ! -f "drvr/src/${MSGQ_FILE}${DFLT_MODULE_NAME^}.c" ]; then
    echo "❌ Error: File 'drvr/src/${MSGQ_FILE}${DFLT_MODULE_NAME^}.c' does not exist"
    exit 1
fi
mv "drvr/src/${MSGQ_FILE}${DFLT_MODULE_NAME^}.c" "drvr/src/${MSGQ_FILE}${NEW_MODULE_NAME_UPR_CML_CASE}.c"
echo "✅ Renamed: drvr/src/${MSGQ_FILE}${DFLT_MODULE_NAME^}.c ➝ drvr/src/${MSGQ_FILE}${NEW_MODULE_NAME_UPT_CML_CASE}.c"

# Rename the drvr/inc/wdtTemplate.h >> drvr/inc/wdtNewModuleName.h
if [ ! -f "drvr/inc/${WDT_FILE}${DFLT_MODULE_NAME^}.h" ]; then
    echo "❌ Error: File 'drvr/inc/${WDT_FILE}${DFLT_MODULE_NAME^}.h' does not exist"
    exit 1
fi
mv "drvr/inc/${WDT_FILE}${DFLT_MODULE_NAME^}.h" "drvr/inc/${WDT_FILE}${NEW_MODULE_NAME_UPR_CML_CASE}.h"
echo "✅ Renamed: drvr/inc/${WDT_FILE}${DFLT_MODULE_NAME^}.h ➝ drvr/inc/${WDT_FILE}${NEW_MODULE_NAME_UPR_CML_CASE}.h"

# Rename the drvr/src/wdtTemplate.c >> drvr/src/wdtNewModuleName.c
if [ ! -f "drvr/src/${WDT_FILE}${DFLT_MODULE_NAME^}.c" ]; then
    echo "❌ Error: File 'drvr/src/${WDT_FILE}${DFLT_MODULE_NAME^}.c' does not exist"
    exit 1
fi
mv "drvr/src/${WDT_FILE}${DFLT_MODULE_NAME^}.c" "drvr/src/${WDT_FILE}${NEW_MODULE_NAME_UPR_CML_CASE}.c"
echo "✅ Renamed: drvr/src/${WDT_FILE}${DFLT_MODULE_NAME^}.c ➝ drvr/src/${WDT_FILE}${NEW_MODULE_NAME_UPR_CML_CASE}.c"

# Rename the drvr/inc/zbusTemplate.h >> drvr/inc/zbusNewModuleName.h
if [ ! -f "drvr/inc/${ZBUS_FILE}${DFLT_MODULE_NAME^}.h" ]; then
    echo "❌ Error: File 'drvr/inc/${ZBUS_FILE}${DFLT_MODULE_NAME^}.h' does not exist"
    exit 1
fi
mv "drvr/inc/${ZBUS_FILE}${DFLT_MODULE_NAME^}.h" "drvr/inc/${ZBUS_FILE}${NEW_MODULE_NAME_UPR_CML_CASE}.h"
echo "✅ Renamed: drvr/inc/${ZBUS_FILE}${DFLT_MODULE_NAME^}.h ➝ drvr/inc/${ZBUS_FILE}${NEW_MODULE_NAME_UPR_CML_CASE}.h"

# Rename the drvr/src/zbusTemplate.c >> drvr/src/zbusNewModuleName.c
if [ ! -f "drvr/src/${ZBUS_FILE}${DFLT_MODULE_NAME^}.c" ]; then
    echo "❌ Error: File 'drvr/src/${ZBUS_FILE}${DFLT_MODULE_NAME^}.c' does not exist"
    exit 1
fi
mv "drvr/src/${ZBUS_FILE}${DFLT_MODULE_NAME^}.c" "drvr/src/${ZBUS_FILE}${NEW_MODULE_NAME_UPR_CML_CASE}.c"
echo "✅ Renamed: drvr/src/${ZBUS_FILE}${DFLT_MODULE_NAME^}.c ➝ drvr/src/${ZBUS_FILE}${NEW_MODULE_NAME_UPR_CML_CASE}.c"

# Rename the host/hostTemplateTest.c >> host/hostNewModuleNameTest.c
if [ ! -f "host/host${DFLT_MODULE_NAME^}Test.sh" ]; then
    echo "❌ Error: File 'host/host${DFLT_MODULE_NAME^}Test.sh' does not exist"
    exit 1
fi
mv "host/host${DFLT_MODULE_NAME^}Test.sh" "host/host${NEW_MODULE_NAME_UPR_CML_CASE}Test.sh"
echo "✅ Renamed: host/host${DFLT_MODULE_NAME^}Test.c ➝ host/host${NEW_MODULE_NAME_UPR_CML_CASE}Test.c"

# Rename the shell/src/shellTemplate.c >> shell/src/shellNewModuleName.c
if [ ! -f "shell/src/${SHELL_FILE}${DFLT_MODULE_NAME^}.c" ]; then
    echo "❌ Error: File 'shell/src/${SHELL_FILE}${DFLT_MODULE_NAME^}.c' does not exist"
    exit 1
fi
mv "shell/src/${SHELL_FILE}${DFLT_MODULE_NAME^}.c" "shell/src/${SHELL_FILE}${NEW_MODULE_NAME_UPR_CML_CASE}.c"
echo "✅ Renamed: shell/src/${SHELL_FILE}${DFLT_MODULE_NAME^}.c ➝ shell/src/${SHELL_FILE}${NEW_MODULE_NAME_UPR_CML_CASE}.c"

# Rename the test/src/testTemplate.c
if [ ! -f "test/src/test${DFLT_MODULE_NAME^}.c" ]; then
    echo "❌ Error: File 'test/src/test${DFLT_MODULE_NAME^}.c' does not exist"
    exit 1
fi
mv "test/src/test${DFLT_MODULE_NAME^}.c" "test/src/test${NEW_MODULE_NAME_UPR_CML_CASE}.c"
echo "✅ Renamed: test/src/test${DFLT_MODULE_NAME^}.c ➝ test/src/${NEW_MODULE_NAME_UPR_CML_CASE}.c"



#### Replace Text #####################################################################################################


# Replace all occurrences of module.h with newModuleName.h
echo "🔁 Replacing all occurrences of '${DFLT_MODULE_NAME}\.h' with '${NEW_MODULE_NAME_LWR_CML_CASE}\.h' (excluding .git)..."
grep -rl --exclude-dir=.git --exclude="$(basename "$0")" "${DFLT_MODULE_NAME}\.h" | xargs sed -i "s/${DFLT_MODULE_NAME}\.h/${NEW_MODULE_NAME_LWR_CML_CASE}\.h/g"

# Replace all occurrences of module.c with newModuleName.c
echo "🔁 Replacing all occurrences of '${DFLT_MODULE_NAME}\.c' with '${NEW_MODULE_NAME_LWR_CML_CASE}\.c' (excluding .git)..."
grep -rl --exclude-dir=.git --exclude="$(basename "$0")" "${DFLT_MODULE_NAME}\.c" | xargs sed -i "s/${DFLT_MODULE_NAME}\.c/${NEW_MODULE_NAME_LWR_CML_CASE}\.c/g"

# Replace all occurrences of moduleInit with newModuleNameInit
echo "🔁 Replacing all occurrences of '${DFLT_MODULE_NAME}Init' with '${NEW_MODULE_NAME_LWR_CML_CASE}Init' (excluding .git)..."
grep -rl --exclude-dir=.git --exclude="$(basename "$0")" "${DFLT_MODULE_NAME}Init" | xargs sed -i "s/${DFLT_MODULE_NAME}Init/${NEW_MODULE_NAME_LWR_CML_CASE}Init/g"

# Replace all occurrences of moduleMain with newModuleNameMain
echo "🔁 Replacing all occurrences of '${DFLT_MODULE_NAME}Main' with '${NEW_MODULE_NAME_LWR_CML_CASE}Main' (excluding .git)..."
grep -rl --exclude-dir=.git --exclude="$(basename "$0")" "${DFLT_MODULE_NAME}Main" | xargs sed -i "s/${DFLT_MODULE_NAME}Main/${NEW_MODULE_NAME_LWR_CML_CASE}Main/g"

# Replace all occurrences of mainModule with mainNewModuleName
echo "🔁 Replacing all occurrences of 'main${DFLT_MODULE_NAME^}' with 'main${NEW_MODULE_NAME_UPR_CML_CASE}' (excluding .git)..."
grep -rl --exclude-dir=.git --exclude="$(basename "$0")" "main${DFLT_MODULE_NAME^}" | xargs sed -i "s/main${DFLT_MODULE_NAME^}/main${NEW_MODULE_NAME_UPR_CML_CASE}/g"

# Replace all occurrences of testModule with testNewModuleName
echo "🔁 Replacing all occurrences of 'test${DFLT_MODULE_NAME^}' with 'test${NEW_MODULE_NAME_UPR_CML_CASE}' (excluding .git)..."
grep -rl --exclude-dir=.git --exclude="$(basename "$0")" "test${DFLT_MODULE_NAME^}" | xargs sed -i "s/test${DFLT_MODULE_NAME^}/test${NEW_MODULE_NAME_UPR_CML_CASE}/g"

# Replace all occurrences of msgqModule with msgqNewModuleName
echo "🔁 Replacing all occurrences of '${MSGQ_FILE}${DFLT_MODULE_NAME^}' with '${MSGQ_FILE}${NEW_MODULE_NAME_UPR_CML_CASE}' (excluding .git)..."
grep -rl --exclude-dir=.git --exclude="$(basename "$0")" "${MSGQ_FILE}${DFLT_MODULE_NAME^}" | xargs sed -i "s/${MSGQ_FILE}${DFLT_MODULE_NAME^}/${MSGQ_FILE}${NEW_MODULE_NAME_UPR_CML_CASE}/g"

# Replace all occurrences of zbusModule with zbusNewModuleName
echo "🔁 Replacing all occurrences of '${ZBUS_FILE}${DFLT_MODULE_NAME^}' with '${ZBUS_FILE}${NEW_MODULE_NAME_UPR_CML_CASE}' (excluding .git)..."
grep -rl --exclude-dir=.git --exclude="$(basename "$0")" "${ZBUS_FILE}${DFLT_MODULE_NAME^}" | xargs sed -i "s/${ZBUS_FILE}${DFLT_MODULE_NAME^}/${ZBUS_FILE}${NEW_MODULE_NAME_UPR_CML_CASE}/g"

# Replace all occurrences of ZbusMsgTemplate with zbusMsgNewModuleName
echo "🔁 Replacing all occurrences of '${ZBUS_FILE^}Msg${DFLT_MODULE_NAME^}' with '${ZBUS_FILE^}Msg${NEW_MODULE_NAME_UPR_CML_CASE}' (excluding .git)..."
grep -rl --exclude-dir=.git --exclude="$(basename "$0")" "${ZBUS_FILE^}Msg${DFLT_MODULE_NAME^}" | xargs sed -i "s/${ZBUS_FILE^}Msg${DFLT_MODULE_NAME^}/${ZBUS_FILE^}Msg${NEW_MODULE_NAME_UPR_CML_CASE}/g"

# Replace all occurrences of shellTemplate with shellNewModuleName
echo "🔁 Replacing all occurrences of '${SHELL_FILE}${DFLT_MODULE_NAME^}' with '${SHELL_FILE}${NEW_MODULE_NAME_UPR_CML_CASE}' (excluding .git)..."
grep -rl --exclude-dir=.git --exclude="$(basename "$0")" "${SHELL_FILE}${DFLT_MODULE_NAME^}" | xargs sed -i "s/${SHELL_FILE}${DFLT_MODULE_NAME^}/${SHELL_FILE}${NEW_MODULE_NAME_UPR_CML_CASE}/g"

# Replace all occurrences of wdtModule with wdtNewModuleName
echo "🔁 Replacing all occurrences of '${WDT_FILE}${DFLT_MODULE_NAME^}' with '${WDT_FILE}${NEW_MODULE_NAME_UPR_CML_CASE}' (excluding .git)..."
grep -rl --exclude-dir=.git --exclude="$(basename "$0")" "${WDT_FILE}${DFLT_MODULE_NAME^}" | xargs sed -i "s/${WDT_FILE}${DFLT_MODULE_NAME^}/${WDT_FILE}${NEW_MODULE_NAME_UPR_CML_CASE}/g"

# Replace all occurrences of TEMPLATE with NEW_MODULE_NAME
echo "🔁 Replacing all occurrences of '${DFLT_MODULE_NAME^^}*' with '${NEW_MODULE_NAME_UPR_CASE}*' (excluding .git)..."
grep -rl --exclude-dir=.git --exclude="$(basename "$0")" "${DFLT_MODULE_NAME^^}" | xargs sed -i "s/${DFLT_MODULE_NAME^^}/${NEW_MODULE_NAME_UPR_CASE}/g"

# Replace all occurrences of module_main with new_module_name_main
echo "🔁 Replacing all occurrences of '${DFLT_MODULE_NAME}_main*' with '${NEW_MODULE_NAME_LWR_CASE}_main*' (excluding .git)..."
grep -rl --exclude-dir=.git --exclude="$(basename "$0")" "${DFLT_MODULE_NAME}_main" | xargs sed -i "s/${DFLT_MODULE_NAME}_main/${NEW_MODULE_NAME_LWR_CASE}_main/g"

# Replace all occurrences of MsgqModule with MsgqNewModuleName
echo "🔁 Replacing all occurrences of '${MSGQ_FILE^}${DFLT_MODULE_NAME^}*' with '${MSGQ_FILE^}${NEW_MODULE_NAME_UPR_CML_CASE}*' (excluding .git)..."
grep -rl --exclude-dir=.git --exclude="$(basename "$0")" "${MSGQ_FILE^}${DFLT_MODULE_NAME^}" | xargs sed -i "s/${MSGQ_FILE^}${DFLT_MODULE_NAME^}/${MSGQ_FILE^}${NEW_MODULE_NAME_UPR_CML_CASE}/g"

# Replace all occurrences of msg.template with msg.newModuleName
echo "🔁 Replacing all occurrences of 'msg\.${DFLT_MODULE_NAME}*' with 'msg\.${NEW_MODULE_NAME_LWR_CML_CASE}*' (excluding .git)..."
grep -rl --exclude-dir=.git --exclude="$(basename "$0")" "msg\.${DFLT_MODULE_NAME}" | xargs sed -i "s/msg\.${DFLT_MODULE_NAME}/msg\.${NEW_MODULE_NAME_LWR_CML_CASE}/g"

# Replace all occurrences of templateVal with newModuleNameVal
echo "🔁 Replacing all occurrences of '${DFLT_MODULE_NAME}Val*' with '${NEW_MODULE_NAME_LWR_CML_CASE}Val*' (excluding .git)..."
grep -rl --exclude-dir=.git --exclude="$(basename "$0")" "${DFLT_MODULE_NAME}Val" | xargs sed -i "s/${DFLT_MODULE_NAME}Val/${NEW_MODULE_NAME_LWR_CML_CASE}Val/g"

# Replace all occurrences of templateMsg with newModuleNameMsg
echo "🔁 Replacing all occurrences of '${DFLT_MODULE_NAME}Msg*' with '${NEW_MODULE_NAME_LWR_CML_CASE}Msg*' (excluding .git)..."
grep -rl --exclude-dir=.git --exclude="$(basename "$0")" "${DFLT_MODULE_NAME}Msg" | xargs sed -i "s/${DFLT_MODULE_NAME}Msg/${NEW_MODULE_NAME_LWR_CML_CASE}Msg/g"

# Replace all occurrences of template_thread_lis with newModuleName_thread_lis
echo "🔁 Replacing all occurrences of '${DFLT_MODULE_NAME}_thread_lis*' with '${NEW_MODULE_NAME_LWR_CASE}_thread_lis*' (excluding .git)..."
grep -rl --exclude-dir=.git --exclude="$(basename "$0")" "${DFLT_MODULE_NAME}_thread_lis" | xargs sed -i "s/${DFLT_MODULE_NAME}_thread_lis/${NEW_MODULE_NAME_LWR_CASE}_thread_lis/g"

# Replace all occurrences of template_shell_lis with newModuleName_shell_lis
echo "🔁 Replacing all occurrences of '${DFLT_MODULE_NAME}_shell_lis*' with '${NEW_MODULE_NAME_LWR_CASE}_shell_lis*' (excluding .git)..."
grep -rl --exclude-dir=.git --exclude="$(basename "$0")" "${DFLT_MODULE_NAME}_shell_lis" | xargs sed -i "s/${DFLT_MODULE_NAME}_shell_lis/${NEW_MODULE_NAME_LWR_CASE}_shell_lis/g"

# Replace all occurrences of template_test_lis with newModuleName_test_lis
echo "🔁 Replacing all occurrences of '${DFLT_MODULE_NAME}_test_lis*' with '${NEW_MODULE_NAME_LWR_CASE}_test_lis*' (excluding .git)..."
grep -rl --exclude-dir=.git --exclude="$(basename "$0")" "${DFLT_MODULE_NAME}_test_lis" | xargs sed -i "s/${DFLT_MODULE_NAME}_test_lis/${NEW_MODULE_NAME_LWR_CASE}_test_lis/g"

# Replace all occurrences of Template Commands with NewModuleName Commands
echo "🔁 Replacing all occurrences of '${DFLT_MODULE_NAME^} Commands*' with '${NEW_MODULE_NAME_LWR_CASE^} Commands*' (excluding .git)..."
grep -rl --exclude-dir=.git --exclude="$(basename "$0")" "${DFLT_MODULE_NAME^} Commands" | xargs sed -i "s/${DFLT_MODULE_NAME^} Commands/${NEW_MODULE_NAME_LWR_CASE^} Commands/g"

# Replace all occurrences of Test Template with Test NewModuleName
echo "🔁 Replacing all occurrences of 'Test ${DFLT_MODULE_NAME^}*' with 'Test ${NEW_MODULE_NAME_LWR_CASE^}*' (excluding .git)..."
grep -rl --exclude-dir=.git --exclude="$(basename "$0")" "Test ${DFLT_MODULE_NAME^}" | xargs sed -i "s/Test ${DFLT_MODULE_NAME^}/Test ${NEW_MODULE_NAME_LWR_CASE^}/g"

# Replace all occurrences of test_template with test_newModuleName
echo "🔁 Replacing all occurrences of 'test_${DFLT_MODULE_NAME}*' with 'test_${NEW_MODULE_NAME_LWR_CASE}*' (excluding .git)..."
grep -rl --exclude-dir=.git --exclude="$(basename "$0")" "test_${DFLT_MODULE_NAME}" | xargs sed -i "s/test_${DFLT_MODULE_NAME}/test_${NEW_MODULE_NAME_LWR_CASE}/g"

# Replace all occurrences of template.tester with NewModuleName.tester
echo "🔁 Replacing all occurrences of '${DFLT_MODULE_NAME}\.tester*' with '${NEW_MODULE_NAME_LWR_CML_CASE}\.tester*' (excluding .git)..."
grep -rl --exclude-dir=.git --exclude="$(basename "$0")" "${DFLT_MODULE_NAME}\.tester" | xargs sed -i "s/${DFLT_MODULE_NAME}\.tester/${NEW_MODULE_NAME_LWR_CML_CASE}\.tester/g"

# Replace all occurrences of shell_template with new_module_name
echo "🔁 Replacing all occurrences of 'shell_${DFLT_MODULE_NAME}*' with '${NEW_MODULE_NAME_LWR_CASE}*' (excluding .git)..."
grep -rl --exclude-dir=.git --exclude="$(basename "$0")" "shell_${DFLT_MODULE_NAME}" | xargs sed -i "s/shell_${DFLT_MODULE_NAME}/${NEW_MODULE_NAME_LWR_CASE}/g"