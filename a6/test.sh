#!/bin/bash

# Constants
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
CODE_DIR=~gerald/public/html/cs368/assignments/a6
LIB_DIR=/p/course/cs368-gerald/public/libraries
VALID_ARGS=("BasicTest" "PushPerformanceTest" "PopTest" "ReserveTest" "ClearTest" "IteratorTest" "BracketAtTest" "CopyConstructorTest" "CopyAssignmentTest" "SelfAssignmentTest")

cd "$DIR"

if (($# == 0)); then
    (<&2 echo "Warning: no arguments specified.")
    (<&2 echo "USAGE: ./test.sh <TEST1> <TEST2> ...")
    (<&2 echo "Only performing preliminary checks.")
fi

# Exit if necessary files do not exist
if [ ! -f "./Vector.hpp" ]; then
    (<&2 echo "Could not find $file")
    exit 1
fi

# Basic checks for Vector.hpp
CSTDIO_COUNT=$(grep -o "<cstdio>" ./Vector.hpp | wc -l)
IOSTREAM_COUNT=$(grep -o "<iostream>" ./Vector.hpp | wc -l)
STDEXCEPT_COUNT=$(grep -o "<stdexcept>" ./Vector.hpp | wc -l)
VECTOR_COUNT=$(grep -o "<vector>" ./Vector.hpp | wc -l)
INCLUDE_COUNT=$(grep -o "#include" ./Vector.hpp | wc -l)
BEGIN_COUNT=$(grep -o "/\* If you want to add methods, add them below this line \*/" ./Vector.hpp | wc -l)
END_COUNT=$(grep -o "/\* If you want to add methods, add them above this line \*/" ./Vector.hpp | wc -l)
PRIVATE_COUNT=$(grep -o "private" ./Vector.hpp | wc -l)
PUBLIC_COUNT=$(grep -o "public" ./Vector.hpp | wc -l)
MUTABLE_COUNT=$(grep -o "mutable" ./Vector.hpp | wc -l)
VOLATILE_COUNT=$(grep -o "volatile" ./Vector.hpp | wc -l)
flag=0
if ((CSTDIO_COUNT == 0)); then
    (<&2 echo "There are 0 occurrences of the word \"<cstdio>\" in Vector.hpp")
    flag=1
fi
if ((CSTDIO_COUNT > 1)); then
    (<&2 echo "There is more than 1 occurrence of the word \"<cstdio>\" in Vector.hpp")
    flag=1
fi
if ((IOSTREAM_COUNT == 0)); then
    (<&2 echo "There are 0 occurrences of the word \"<iostream>\" in Vector.hpp")
    flag=1
fi
if ((IOSTREAM_COUNT > 1)); then
    (<&2 echo "There is more than 1 occurrence of the word \"<iostream>\" in Vector.hpp")
    flag=1
fi
if ((STDEXCEPT_COUNT == 0)); then
    (<&2 echo "There are 0 occurrences of the word \"<stdexcept>\" in Vector.hpp")
    flag=1
fi
if ((STDEXCEPT_COUNT > 1)); then
    (<&2 echo "There is more than 1 occurrence of the word \"<stdexcept>\" in Vector.hpp")
    flag=1
fi
if ((VECTOR_COUNT > 0)); then
    (<&2 echo "There are more than 0 occurrences of the word \"<vector>\" in Vector.hpp")
    flag=1
fi
if ((INCLUDE_COUNT < 3)); then
    (<&2 echo "There are less than 3 occurrences of \"\#include\" in Vector.hpp")
    flag=1
fi
if ((INCLUDE_COUNT > 3)); then
    (<&2 echo "There are more than 3 occurrences of \"\#include\" in Vector.hpp")
    flag=1
fi
if ((BEGIN_COUNT == 0)); then
    (<&2 echo "There are 0 occurrences of the comment /* If you want to add methods, add them below this line */ in Vector.hpp")
    flag=1
fi
if ((BEGIN_COUNT > 1)); then
    (<&2 echo "There is more than 1 occurrence of the comment /* If you want to add methods, add them below this line */ in Vector.hpp")
    flag=1
fi
if ((END_COUNT == 0)); then
    (<&2 echo "There are 0 occurrences of the comment /* If you want to add methods, add them above this line */ in Vector.hpp")
    flag=1
fi
if ((END_COUNT > 1)); then
    (<&2 echo "There is more than 1 occurrence of the comment /* If you want to add methods, add them above this line */ in Vector.hpp")
    flag=1
fi
if ((PRIVATE_COUNT == 0)); then
    (<&2 echo "There are 0 occurrences of the word \"private\" in Vector.hpp")
    flag=1
fi
if ((PRIVATE_COUNT > 1)); then
    (<&2 echo "There is more than 1 occurrence of the word \"private\" in Vector.hpp")
    flag=1
fi
if ((PUBLIC_COUNT == 0)); then
    (<&2 echo "There are 0 occurrences of the word \"public\" in Vector.hpp")
    flag=1
fi
if ((PUBLIC_COUNT > 1)); then
    (<&2 echo "There is more than 1 occurrence of the word \"public\" in Vector.hpp")
    flag=1
fi
if ((MUTABLE_COUNT > 0)); then
    (<&2 echo "There are more than 0 occurrences of the word \"mutable\" in Vector.hpp")
    flag=1
fi
if ((VOLATILE_COUNT > 0)); then
    (<&2 echo "There are more than 0 occurrences of the word \"volatile\" in Vector.hpp")
    flag=1
fi
if ((flag == 1)); then
    (<&2 echo "Please fix the above errors in Vector.hpp, exiting")
    exit 1
fi

# More advanced checks for Vector.hpp
cmp <(grep -v "^//" "$CODE_DIR/Vector.hpp" | head -n13) <(grep -v "^//" ./Vector.hpp | head -n13 | tr -d "\r") > /dev/null 2>&1
status=$?
if ((status != 0)); then
    (<&2 echo "Warning: changes to first 13 lines of code in Vector.hpp")
fi

# Exit if Vector.hpp does not compile
g++ -std=c++11 ./Vector.hpp -o ./test
status=$?
if ((status != 0)); then
    (<&2 echo "Could not compile Vector.hpp, exiting")
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
            ./test --gtest_filter="A6Test.$arg"
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
