#fill ~-1 ~ ~-1 ~1 ~ ~1 air 0 replace concrete 0
#fill ~ ~ ~-1 ~ ~ ~-1 air 0 replace concrete 0
#fill ~ ~ ~1 ~ ~ ~1 air 0 replace concrete 0
#fill ~1 ~ ~ ~1 ~ ~ air 0 replace concrete 0
#fill ~-1 ~ ~ ~-1 ~ ~ air 0 replace concrete 0

fill ~-1 ~ ~-1 ~1 ~ ~1 repeating_command_block 0 keep {Command:"/function exxabite:blow_edge",auto:1b}
#fill ~ ~ ~-1 ~ ~ ~-1 repeating_command_block 0 keep {Command:"/function exxabite:blow_edge",auto:1b}
#fill ~ ~ ~1 ~ ~ ~1 repeating_command_block 0 keep {Command:"/function exxabite:blow_edge",auto:1b}
#fill ~-1 ~ ~ ~-1 ~ ~ repeating_command_block 0 keep {Command:"/function exxabite:blow_edge",auto:1b}
#fill ~1 ~ ~ ~1 ~ ~ repeating_command_block 0 keep {Command:"/function exxabite:blow_edge",auto:1b}

#fill ~-1 ~ ~ ~1 ~ ~ tnt 0 replace concrete 0
#fill ~ ~ ~-1 ~ ~ ~1 tnt 0 replace concrete 0

#setblock ~ ~ ~ air 0
setblock ~ ~ ~ tnt 0
function exxabite:blow_up_more

