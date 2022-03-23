fill ~-1 ~ ~ ~-1 ~ ~ concrete 14 replace redstone_block 0
fill ~1 ~ ~ ~1 ~ ~ concrete 14 replace redstone_block 0
fill ~ ~ ~-1 ~ ~ ~-1 concrete 14 replace redstone_block 0
fill ~ ~ ~1 ~ ~ ~1 concrete 14 replace redstone_block 0
setblock ~ ~ ~ tnt

#fill ~ ~ ~ ~ ~ ~ air 0 replace repeating_command_block
#fill ~ ~ ~ ~ ~ ~ repeating_command_block 0 keep {Command:"/function exxabite:redstone_block",auto:1b}
#fill ~ ~1 ~ ~ ~1 ~ repeating_command_block 0 keep {Command:"/function exxabite:blow_up",auto:1b}

function exxabite:blow_up_more
