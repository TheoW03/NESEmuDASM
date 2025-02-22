#!/bin/bash

build() {

    # mkdir -p ./src/unitTests/TestRoms/
    mkdir -p ./games/
    RomList=(
        "nya~"
        "./src/TestRoms/TestRom1.s -o ./games/TestRom1.nes"

    )

    echo ""

    # Iterate over each command in the RomList
    for p in "${RomList[@]}"; do
        # Split the command string into an array
        args=($p)
        
        # Run the cl65 command with the appropriate arguments
        if cl65 --target nes "${args[@]}"; then
            echo "Built ${args[2]} successfully"
        else
            echo "Built ${args[2]} unsuccessfully"
        fi

        echo ""
    done
}
build