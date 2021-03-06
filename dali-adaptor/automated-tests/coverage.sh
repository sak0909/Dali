#!/bin/bash

( cd ../build/tizen ; make cov_data )

for i in `find . -name Makefile` ; do
    (
        cd $(dirname $i)
        echo `pwd`
        covs=( `ls *.gcda 2>/dev/null` )
        if [[ $? -eq 0 ]]
        then
            make coverage
        fi
    )
done

(
    cd .. ;
    genhtml -o build/tizen/doc/coverage `find . -name dali.info ! -size 0`
)


