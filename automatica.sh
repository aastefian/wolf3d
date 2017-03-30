#!/bin/bash

### Set initial time of file
HANDLERS_BEFORE_TIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/handlers.c`
MAIN_BEFORE_TIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/main.c`
MAP_PROCESSING_BEFORE_TIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/map_processing.c`
MAP_EDITOR_BEFORE_TIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/map_editor.c`
PLAYER_MOVEMENT_BEFORE_TIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/player_movement.c`



while true    
do
   HANDLERS_AFTER_TIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/handlers.c`
   MAIN_AFTER_TIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/main.c`
   MAP_PROCESSING_AFTER_TIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/map_processing.c`
   MAP_EDITOR_AFTER_TIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/map_editor.c`  
   PLAYER_MOVEMENT_AFTER_TIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/player_movement.c`   
   
   

   if [[ ("$HANDLERS_BEFORE_TIME" != "$HANDLERS_AFTER_TIME" ) || ("$MAIN_BEFORE_TIME" != "$MAIN_AFTER_TIME") || ("$MAP_PROCESSING_BEFORE_TIME" != "$MAP_PROCESSING_AFTER_TIME") || ("$MAP_EDITOR_BEFORE_TIME" != "$MAP_EDITOR_AFTER_TIME") || ( "$PLAYER_MOVEMENT_BEFORE_TIME" != "$PLAYER_MOVEMENT_AFTER_TIME") ]]
   then    
       make run   
       norminette includes/*.h
       norminette srcs/*.c
       HANDLERS_BEFORE_TIME=$HANDLERS_AFTER_TIME
       MAIN_BEFORE_TIME=$MAIN_AFTER_TIME
       MAP_PROCESSING_BEFORE_TIME=$MAP_PROCESSING_AFTER_TIME
       MAP_EDITOR_BEFORE_TIME=$MAP_EDITOR_AFTER_TIME
       PLAYER_MOVEMENT_BEFORE_TIME=$PLAYER_MOVEMENT_AFTER_TIME
   fi
   sleep 1
done