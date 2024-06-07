#!/bin/bash

if [ -d ./bin/ ]; then
    rm -rf ./bin
fi

if [ -d ./dev/ ]; then
    rm -rf ./dev
fi

if [[ "$3" = "--fresh" || "$2" = "--fresh" ]]; then
    rm ./.ignore/ensured
fi
    

mkdir -p .ignore

if [ ! -f .ignore/ensured ]; then
    echo "Download deps automatically (must be sudo)? (y/n)"
    read auto
    
    DEPS="deps.txt"

    if [[ "$auto" = "y" && ! "$1" = "-s" ]]; then
        echo "Installing dependencies automatically"
    elif [ ! "$1" = "-s" ]; then
        echo "Checking dependencies"
    fi

    while IFS= read -r dep; do
        if [ -n "$dep" ]; then
            continue
        fi

        if [ ! "$1" = "-s" ]; then
            echo "Checking $dep"
        fi

        installed=$(apt install --simulate "$dep" 2>&1 | grep -s "$dep is already")
        if [ ! -n "$installed" ]; then
            if [ ! "$1" = "-s" ]; then
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

if [ "$1" = "-s" ]; then
    echo "Finished checking deps."
    echo "Creating makefile"
fi
                
if [ "$1" = "-s" ]; then
    echo "making"
fi

if [ "$1" == "--dev" ]; then
    cmake -B dev -DCMAKE_BUILD_TYPE=Debug
    cmake --build dev/
else
    cmake -B bin
    cmake --build bin/
fi

echo "Finished."

