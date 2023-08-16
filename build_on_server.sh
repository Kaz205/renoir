#!/bin/bash

build_mode=$1
echo $build_mode | grep -q "clean\|dirty"
if [ $? = 1 ]
then
    echo "Please specify whether to clean build or dirty build"
    exit 1
fi

if [ $build_mode = "clean" ]
then
    ssh kazuki@192.168.13.165 "rm -rf /home/kazuki/renoir/out"
fi

# Build
ssh -tt kazuki@192.168.13.165 "cd renoir && git pull origin && git reset --hard FETCH_HEAD && bash build_kernel.sh"
if [ $? != 0 ]
then
    echo $?
    echo -e "\e[0;31mBuild failed, exiting... \e[0m"
    exit 1
fi

# SSH to server then list zips by date then cut and parse zip name
server_file=$(ssh kazuki@192.168.13.165 "cd /home/kazuki/AnyKernel3 && ls -altr" | rg zip | tail -1 - | awk '{print $NF}')

scp kazuki@192.168.13.165:/home/kazuki/AnyKernel3/$server_file ~/AnyKernel3/$server_file
