#! /bin/bash

if [ $# -lt 2 ];
then
    echo "Please pass in two arguments."
	exit 1
fi

if [ ! -d $1 ];
then
    echo "The first argument is not a directory."
	exit 1
fi

TOTAL_FILES=$(find -L ${1} -type f -printf "%f\n" 2> /dev/null | wc -l)
TOTAL_MATCHED=$(grep -Rn "${2}" "${1}" 2> /dev/null | uniq | wc -l)

#echo "total files:   ${TOTAL_FILES}"
#echo "total matched: ${TOTAL_MATCHED}"

echo "The number of files are ${TOTAL_FILES} and the number of matching lines are ${TOTAL_MATCHED}."
