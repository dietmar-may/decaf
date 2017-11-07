#!/bin/bash -e
# ------------------------------------------------------------------------
# Licensed to the Apache Software Foundation (ASF) under one or more
# contributor license agreements.  See the NOTICE file distributed with
# this work for additional information regarding copyright ownership.
# The ASF licenses this file to You under the Apache License, Version 2.0
# (the "License"); you may not use this file except in compliance with
# the License.  You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ------------------------------------------------------------------------

# load the user supplied build configuration file if present.
if [ -f "./build.conf" ] ; then
  . ./build.conf
fi

# load user decaf build configuration
if [ -f "$HOME/.decafrc" ] ; then
  . "$HOME/.decafrc"
fi

# This is where we run all the build steps, configure, make, etc.
if [ -z "$DECAF_BUILD_DIR" ] ; then
   DECAF_BUILD_DIR="$PWD/build"
fi

check_Configure() {

    # No Configure script means we have to run autogen, which in turn means
    # we need to run a new Configure on the project.
    if [ -x "./configure" ] ; then

        # even if we have a configure script, if the template has been updated we should
        # run it again to account for the changes, which also means we need to run a autogen
        # to create the actual script and associated autoconf artifacts.
        if [ "./configure.ac" -ot "./configure" ] && [ -d $DECAF_BUILD_DIR ] ; then
            runconfigure=false
        else
            runconfigure=true
        fi

    fi

    if [ "x$runconfigure" -ne x ] ; then
        run_Configure
    fi

}

run_Configure() {

    if [ -z "$DECAF_DISABLE_SHARED" ] ; then
        DECAF_DISABLE_SHARED=false;
    fi
    if [ -z "$DECAF_DISABLE_STATIC" ] ; then
        DECAF_DISABLE_STATIC=false;
    fi

    ./autogen.sh

    local args

    if ! [ -d "$DECAF_BUILD_DIR" ] ; then
        mkdir -p $DECAF_BUILD_DIR
    fi

    if [ -n "$DECAF_INSTALL_PREFIX" ] ; then
        args="$args --prefix=$DECAF_INSTALL_PREFIX"
    fi

    if [ -n "$DECAF_LIBDIR" ] ; then
        args="$args --libdir=$DECAF_LIBDIR"
    fi

    if [ -n "$DECAF_APR_DIST" ] ; then
        args="$args --with-apr=$DECAF_APR_DIST"
    fi

    if [ -n "$DECAF_APU_DIST" ] ; then
        args="$args --with-aprutil=$DECAF_APU_DIST"
    fi

    if [ -n "$DECAF_CPPUNIT_DIST" ] ; then
        args="$args --with-cppunit=$DECAF_CPPUNIT_DIST"
    fi

    if [ -n "$DECAF_CPPUNIT_EXECDIR" ] ; then
        args="$args --with-cppunit-exec=$DECAF_CPPUNIT_EXECDIR"
    fi

    if $DECAF_DISABLE_SHARED && $DECAF_DISABLE_STATIC ; then
        echo "ERROR: DECAF_DISABLE_SHARED and DECAF_DISABLE_STATIC can't both be set to true."
        exit 1
    fi

    if $DECAF_DISABLE_SHARED ; then
        args="$args --enable-shared=no"
    fi

    if $DECAF_DISABLE_STATIC ; then
        args="$args --enable-static=no"
    fi

    pushd $DECAF_BUILD_DIR
    ../configure $args
    popd
    exit
}

run_Clean() {
    rm -rf $DECAF_BUILD_DIR
    exit
}

run_Make() {
    check_Configure
    pushd $DECAF_BUILD_DIR
    make -j 8
    popd
    exit
}

run_Check() {
    check_Configure
    pushd $DECAF_BUILD_DIR
    make check -j 8
    popd
    exit
}

run_Doxygen() {
    check_Configure
    pushd $DECAF_BUILD_DIR
    make doxygen-run
    popd
    exit
}

case "$1" in
configure)
    run_Configure
    ;;
compile)
    run_Make
    ;;
test)
    run_Check
    ;;
clean)
    run_Clean
    ;;
doxygen)
    run_Doxygen
    ;;
*)
    echo "Usage: $0 {configure,compile,clean,test,doxygen}"
    exit 1
esac

exit 0

