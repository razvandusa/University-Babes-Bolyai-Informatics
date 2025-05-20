#!/bin/bash

echo Command : $0
echo First four arguments : $1 $2 $3 $4
echo All arguments : $@
echo Arguments count : $#

shift
echo Some other arguments : $1 $2 $3 $4
echo All arguments : $@
echo Arguments count : $#

shift 4
echo Some other arguments : $1 $2 $3 $4
echo All arguments : $@
echo Arguments count : $#
