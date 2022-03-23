#gold_block
#setblock ~ ~ ~ gold_block 0 replace
#setblock ~ ~ ~ glass 0 replace
setblock ~ ~ ~ stained_glass 0 replace
#setblock ~ ~ ~ quartz_block 0 replace

fill ~-1 ~-1 ~-1 ~1 ~1 ~1 repeating_command_block 0 keep {Command:"/function exxabite:layer",auto:1b}
