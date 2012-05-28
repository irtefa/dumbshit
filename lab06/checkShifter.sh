#!/bin/bash
for image in frames/*.png
do
    diff $image soln_$image
    if [ $? -ne 0 ]; then
        exit 1
    fi
done
exit 0
