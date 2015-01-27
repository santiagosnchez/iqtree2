#!/bin/bash - 
#===============================================================================
#
#          FILE: compile_binary.sh
# 
#         USAGE: ./compile_binary.sh 
# 
#   DESCRIPTION: This script checkouts the last release version of IQ-TREE and the HEAD of
#                the current branch. Then it complile both version
# 
#       OPTIONS: ---
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: Tung Nguyen (nltung@gmail.com) 
#  ORGANIZATION: 
#       CREATED: 2015-01-26 13:02:57 CET
#      REVISION:  ---
#===============================================================================

set -o nounset                              # Treat unset variables as an error

require_clean_work_tree () {
    # Update the index
    git update-index -q --ignore-submodules --refresh
    err=0

    # Disallow unstaged changes in the working tree
    if ! git diff-files --quiet --ignore-submodules --
    then
        echo >&2 "cannot $0: you have unstaged changes."
        git diff-files --name-status -r --ignore-submodules -- >&2
        err=1
    fi

    # Disallow uncommitted changes in the index
    if ! git diff-index --cached --quiet HEAD --ignore-submodules --
    then
        echo >&2 "cannot $0: your index contains uncommitted changes."
        git diff-index --cached --name-status -r --ignore-submodules HEAD -- >&2
        err=1
    fi

    if [ $err = 1 ]
    then
        echo >&2 "Please commit or stash them."
        exit 1
    fi
}

#Check whether the git work tree is clean
require_clean_work_tree

#Fetch changes from server
git fetch

#Determine hash code of current branch
curBranch=`git status | grep "On branch" | awk '{print $3}'`
#Take the first 6 characters of the current head commit
commit_cur=`git log | head -n1 | awk '{print $2}' | cut -c 1-6`

#Dictionary and binary names
head_build="build_${commit_cur}"
release_build="build_release"
release_binary="iqtree_release"
#cur_binary="iqtree_${commit_cur}"
cur_binary="iqtree_test"

#Clean up 
if [ -e $head_build ]
then
  rm -rf $head_build
fi
if [ -e $release_build ]
then
  rm -rf $release_build 
fi
if [ -e $release_binary ]
then
  rm -rf $release_binary
fi
if [ -e $cur_binary ]
then
  rm -rf $cur_binary
fi

mkdir $head_build 
cmake -B${head_build} -H..
make -C ${head_build} -j4
cp ${head_build}/iqtree ${cur_binary} 
#rm -rf ${head_build}
mkdir $release_build
#Find the hash code of the most recent release in master
commit=`git log origin/master | grep -m 1 -B 4 "release version" | grep "commit" | awk '{print $2}'`
git checkout ${commit}
git submodule update
cmake -B${release_build} -H..
make -C ${release_build} -j4
cp ${release_build}/iqtree ${release_binary}
git checkout ${curBranch}
git submodule update

#Clean up
rm -rf $head_build
rm -rf $release_build 
