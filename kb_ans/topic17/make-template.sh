#!/bin/bash

TEMP_NAME=$1

function check_param()
{
    if [ "${TEMP_NAME}x" == "x" ];
    then
        echo "usage: make-template.sh project_name"
        exit 1
    fi
}

function check_dir()
{
    if [ -d $TEMP_NAME ];
    then
        rm -rf $TEMP_NAME
    fi

    mkdir $TEMP_NAME
}

function fill_hpp_file() {
    DATE=`date +"%Y%m%d"`
    HPP_DIR="${TEMP_NAME}/${TEMP_NAME}.hpp"
    echo "#ifndef _${TEMP_NAME}_${DATE}_" > $HPP_DIR
    echo "#define _${TEMP_NAME}_${DATE}_" >> $HPP_DIR
    sed -i 's/-/_/g' $HPP_DIR
    echo "#include <algorithm>" >> $HPP_DIR
    echo "#include <assert.h>" >> $HPP_DIR
    echo "#include <cmath>" >> $HPP_DIR
    echo "#include <cstdio>" >> $HPP_DIR
    echo "#include <cstdlib>" >> $HPP_DIR
    echo "#include <cstring>" >> $HPP_DIR
    echo "#include <functional>" >> $HPP_DIR
    echo "#include <iostream>" >> $HPP_DIR
    echo "#include <map>" >> $HPP_DIR
    echo "#include <numeric>" >> $HPP_DIR
    echo "#include <queue>" >> $HPP_DIR
    echo "#include <set>" >> $HPP_DIR
    echo "#include <sstream>" >> $HPP_DIR
    echo "#include <stack>" >> $HPP_DIR
    echo "#include <string>" >> $HPP_DIR
    echo "#include <vector>" >> $HPP_DIR
    #echo "#include <unordered_map>" >> $HPP_DIR
    #echo "#include <unordered_set>" >> $HPP_DIR
    echo "using namespace std;" >> $HPP_DIR
    echo '#define DEBUG' >> $HPP_DIR
    echo '#ifdef DEBUG' >> $HPP_DIR
    echo '#define DEBUG_CMD(cmd)                                                                             \' >> $HPP_DIR
    echo '    do {                                                                                           \' >> $HPP_DIR
    echo '        cmd;                                                                                       \' >> $HPP_DIR
    echo '    } while (false)' >> $HPP_DIR
    echo '#else' >> $HPP_DIR
    echo '#define DEBUG_CMD(cmd)                                                                             \' >> $HPP_DIR
    echo '    do {                                                                                           \' >> $HPP_DIR
    echo '        ;                                                                                          \' >> $HPP_DIR
    echo '    } while (false)' >> $HPP_DIR
    echo '#endif' >> $HPP_DIR
    echo '#define _DEBUG_CMD(cmd)                                                                            \' >> $HPP_DIR
    echo '    do {                                                                                           \' >> $HPP_DIR
    echo '        ;                                                                                          \' >> $HPP_DIR
    echo '    } while (false)' >> $HPP_DIR

    echo "" >> $HPP_DIR
    echo "int main(int argc, char **argv) {" >> $HPP_DIR
    echo "    return 0;" >> $HPP_DIR
    echo "};" >> $HPP_DIR
    echo "" >> $HPP_DIR
    echo "#endif" >> $TEMP_NAME/${TEMP_NAME}.hpp

    #touch $TEMP_NAME/${TEMP_NAME}.cpp
    echo "#include <limits.h>" > $TEMP_NAME/${TEMP_NAME}_unittest.cpp
    echo "#include \"${TEMP_NAME}.hpp\"" >> $TEMP_NAME/${TEMP_NAME}_unittest.cpp
    echo "#include \"gtest/gtest.h\"" >> $TEMP_NAME/${TEMP_NAME}_unittest.cpp
}

function fill_make_file() {
    RC_LOC="CXX=g++
GTEST_DIR=/home/zhangxianwen/package/googletest-release-1.7.0
USER_DIR=./"

    #[ -f "${RC_LOC}" ] || { echo "no ${RC_LOC} here"; exit -1; }
    echo "${RC_LOC}"  >  $TEMP_NAME/Makefile
    cat ./Makefile >> $TEMP_NAME/Makefile

    sed -i "s/sample1_unittest/${TEMP_NAME}_unittest/g" $TEMP_NAME/Makefile
    sed -i "s/\<sample1\>/${TEMP_NAME}/g" $TEMP_NAME/Makefile
}

function fill_py_file() {
	find_err_path="$TEMP_NAME/find_err.py"
	make_rdn_testcase_path="$TEMP_NAME/make_rdn_testcase.py"
	cat ./find_err.py >> $find_err_path
	cat ./_make_rdn_testcase.py >> $make_rdn_testcase_path
	sed -i "s/project_sed_flag/${TEMP_NAME}/g" $find_err_path
    chmod +x $make_rdn_testcase_path
    chmod +x $find_err_path
}

function fill_dir()
{
    fill_hpp_file
    fill_make_file
    fill_py_file
}

check_param

check_dir

fill_dir
