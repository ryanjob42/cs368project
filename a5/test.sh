#!/bin/bash

# Constants
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
CODE_DIR=~gerald/public/html/cs368/assignments/a5
LIB_DIR=/p/course/cs368-gerald/public/libraries
VALID_ARGS=("IntTest" "ComplexTest" "BasicExceptionTest" "InheritExceptionTest" "InvalidDimensionTest" "IndexOutOfBoundsTest" "IncompatibleMatricesTest")

cd "$DIR"

if (($# == 0)); then
    (<&2 echo "Warning: no arguments specified.")
    (<&2 echo "USAGE: ./test.sh <TEST1> <TEST2> ...")
    (<&2 echo "Only performing preliminary checks.")
fi

# Exit if necessary files do not exist
if [ ! -f "./Matrix.hpp" ]; then
    (<&2 echo "Could not find $file")
    exit 1
fi

# Basic checks for Matrix.hpp
MUTABLE_COUNT=$(grep -o "mutable" ./Matrix.hpp | wc -l)
VOLATILE_COUNT=$(grep -o "volatile" ./Matrix.hpp | wc -l)
flag=0
if ((MUTABLE_COUNT > 0)); then
    (<&2 echo "There are more than 0 occurrences of the word \"mutable\" in Matrix.hpp")
    flag=1
fi
if ((VOLATILE_COUNT > 0)); then
    (<&2 echo "There are more than 0 occurrences of the word \"volatile\" in Matrix.hpp")
    flag=1
fi
if ((flag == 1)); then
    (<&2 echo "Please fix the above errors in Matrix.hpp, exiting")
    exit 1
fi

# Exit if Matrix.hpp does not compile
g++ -std=c++11 ./Matrix.hpp -o ./test
status=$?
if ((status != 0)); then
    (<&2 echo "Could not compile Matrix.hpp, exiting")
    exit 1
fi
rm -rf ./test

# Compile and run unit tests
INCLUDE="$LIB_DIR/googletest/googletest/include/"
FILES="./test.c $LIB_DIR/libgtest.a"
passed_test_count=0
test_count=0
for arg in "$@"; do
    flag=0
    for valid_arg in ${VALID_ARGS[@]}; do
        if [ "$arg" == "$valid_arg" ]; then
            ((test_count += 1))
            flag=1
        fi
    done
    if ((flag == 0)); then
        echo "$arg is not a valid test, ignoring"
    else
        g++ -std=c++11 -D "Run$arg" -isystem $INCLUDE -pthread $FILES -o ./test
        status=$?
        if ((status != 0)); then
            (<&2 echo "Could not compile $arg, ignoring")
        else
            ./test --gtest_filter="A5Test.$arg"
            status=$?
            if ((status == 0)); then
                ((passed_test_count += 1))
            fi
        fi
        rm -rf ./test
    fi
    echo
done

# Success (possibly)
echo "$passed_test_count/$test_count tests passed"
if (($passed_test_count < $test_count)); then
    exit 1
else
    exit 0
fi
