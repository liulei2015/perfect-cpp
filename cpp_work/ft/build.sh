#!/bin/bash

working_path=$(cd `dirname $0`; pwd)

#working_path=$PWD
#if [ ! -d "ftest" ]; then
   #cd /share/5g-uai-ran-jenkins/shared_work_space/5G-UAI-RAN/common/sps/enb/ft/ccm_main/
#fi

#working_path=$PWD

echo "try build ${working_path}"
echo "************************************************************************"
echo "start generate cmake eclipse project..."

cd ${working_path}
if [[ -d "build" && $@ =~ "full" ]]
then
	sudo rm -rf build
fi
mkdir -p build

cd build
cmake -G "Eclipse CDT4 - Unix Makefiles" -DENABLE_COVERAGE=ON -DCMAKE_BUILD_TYPE=debug ../ftest

echo "***********************************************************************"
echo "start build cmake project..."

time -p make -j4

if [ $? -ne 0 ]; then
    echo "build ${working_path} fail"
    exit 1
fi

echo "*******************************************************************************"
echo "start run tests..."

#TestCelluarMachine.celluar_machine_help_get_celluar_pos_right_up_round
./ftest --gtest_filter=*.* --gtest_color=yes $@ [-g]

if [ $? -ne 0 ]; then
    echo "build ${working_path} fail"
    exit 1
fi

cd ..

echo "*******************************************************************************"
echo "build ${working_path} succ"
echo "test gerrit fakenfs"

if [[ $@ =~ "cov" ]]; then
echo "*******************************************************************************"
echo "start to count the code coverage"
echo "*******************************************************************************"
object_path=${working_path}/build

lcov -q --directory ${object_path} --capture --output-file ${working_path}/app.info
mkdir -p coverage_result/coder_tl
genhtml -o coverage_result/coder_tl ${working_path}/app.info
fi


