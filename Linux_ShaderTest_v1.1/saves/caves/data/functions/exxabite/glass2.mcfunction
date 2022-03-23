fill ~-1 ~ ~ ~-1 ~ ~ repeating_command_block 0 keep {Command:"/function exxabite:glass2_normal",auto:1b}
fill ~1 ~ ~ ~1 ~ ~ repeating_command_block 0 keep {Command:"/function exxabite:glass2_normal",auto:1b}
fill ~ ~ ~-1 ~ ~ ~-1 repeating_command_block 0 keep {Command:"/function exxabite:glass2_normal",auto:1b}
fill ~ ~ ~1 ~ ~ ~1 repeating_command_block 0 keep {Command:"/function exxabite:glass2_normal",auto:1b}
fill ~ ~-1 ~ ~ ~-1 ~ repeating_command_block 0 keep {Command:"/function exxabite:glass2_normal",auto:1b}

setblock ~ ~ ~ concrete 3

fill ~-20 ~-1 ~ ~-20 ~-1 ~ air 0 replace bedrock 0
fill ~-20 ~-1 ~ ~-20 ~-1 ~ repeating_command_block 0 keep {Command:"/function exxabite:glass2_west",auto:1b}
fill ~20 ~-1 ~ ~20 ~-1 ~ air 0 replace bedrock 0
fill ~20 ~-1 ~ ~20 ~-1 ~ repeating_command_block 0 keep {Command:"/function exxabite:glass2_east",auto:1b}

fill ~ ~-1 ~-20 ~ ~-1 ~-20 air 0 replace bedrock 0
fill ~ ~-1 ~-20 ~ ~-1 ~-20 repeating_command_block 0 keep {Command:"/function exxabite:glass2_north",auto:1b}
fill ~ ~-1 ~20 ~ ~-1 ~20 air 0 replace bedrock 0
fill ~ ~-1 ~20 ~ ~-1 ~20 repeating_command_block 0 keep {Command:"/function exxabite:glass2_south",auto:1b}
