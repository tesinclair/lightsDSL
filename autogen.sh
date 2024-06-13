#!/bin/bash

if [[ "$1" = "--help" ]]; then
    echo "=-=-=-=-=-=-=-=-="
    echo "|     USAGE     |"
    echo "=-=-=-=-=-=-=-=-="
    echo ""
    echo "Options:"
    echo "    - [--fresh]: Removes '.ignore/ensured' and runs a fresh install"
    echo "                 Use this, if you have updated and the file still exists"
    echo ""
    echo "    - [--lib]:   adds lights-dsl.h to package-config path (must have pkg-config"
    echo "                 for this to work) for development"
    echo ""
    echo "    - [-s]:      Silent: do everything, but keep your mouth shut"
    echo ""
    echo "    - [--dev]:   Build into ./dev/ with developer flags"
    echo ""
    echo "    - [--help]:  Display usage info"
    echo ""
    
    exit 0
fi

fresh=false
lib=false
s=false
dev=false

for arg in "$@"; do
    if [ "$arg" = "--fresh" ]; then
        fresh=true
    fi
    if [ "$arg" = "--lib" ]; then
        lib=true
    fi
    if [ "$arg" = "-s" ]; then
        s=true
    fi
    if [ "$arg" = "--dev" ]; then
        dev=true
    fi
done

if [[ "$dev" = false ]]; then
    if [ -d ./bin/ ]; then
        rm -rf ./bin
    fi
else
    if [ -d ./dev/ ]; then
        rm -rf ./dev/
    fi
fi

if [[ "$fresh" = true ]]; then
    rm ./.ignore/ensured
fi

if [[ "$lib" = true ]]; then
    pkg_conf="/usr/include"
    cp ./include/lights-dsl.pc "$pkg_conf"
fi

mkdir -p .ignore

if [ ! -f .ignore/ensured ]; then
    echo "Download deps automatically (must be sudo)? (y/n)"
    read auto
    
    DEPS="deps.txt"

    if [[ "$auto" = "y" && $s = false ]]; then
        echo "Installing dependencies automatically"
    elif [ ! "$s" = true ]; then
        echo "Checking dependencies"
    fi

    while IFS= read -r dep; do
        if [ -n "$dep" ]; then
            continue
        fi

        if [ $s = false ]; then
            echo "Checking $dep"
        fi

        installed=$(apt install --simulate "$dep" 2>&1 | grep -s "$dep is already")
        if [ ! -n "$installed" ]; then
            if [ $s = false ]; then
                echo "Not found."
            fi
            
            if [ "$auto" = "y" ]; then
                err=$(apt install -y "$dep" 2>&1 | grep -s "E:")

                if [ -n "$err" ]; then
                    echo "Failed to install $dep automatically"
                    exit 1
                fi
            else
                echo "Aborting. $dep needs to be installed"
                exit 1
            fi
        fi
    done < "$DEPS"

    touch .ignore/ensured
fi

if [ $s = false ]; then
    echo "Finished checking deps."
    echo "Creating files now."
fi
                
if [ $dev == true ]; then
    cmake -B dev -DCMAKE_BUILD_TYPE=Debug
    cmake --build dev/
else
    cmake -B bin
    cmake --build bin/
fi

echo "Done."
echo "You can find the executable in bin/, or dev/"

