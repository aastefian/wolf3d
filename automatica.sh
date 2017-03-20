#!/bin/bash

### Set initial time of file
LTIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/handlers.c`

while true    
do
   ATIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/handlers.c`

   if [[ "$ATIME" != "$LTIME" ]]
   then    
       make run
       LTIME=$ATIME
   fi
   sleep 1
done