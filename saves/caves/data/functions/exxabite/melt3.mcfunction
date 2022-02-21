setblock ~ ~ ~ gold_block 0 replace
#setblock ~ ~ ~ sand 0 replace
#fill ~-1 ~-1 ~-1 ~1 ~1 ~1 air 0 replace stone 0
fill ~-1 ~-1 ~-1 ~1 ~ ~1 repeating_command_block 0 keep {Command:"/function exxabite:melt",auto:1b}
