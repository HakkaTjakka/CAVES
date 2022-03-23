fill ~-1 ~ ~ ~-1 ~ ~ repeating_command_block 0 keep {Command:"/function exxabite:glass_normal",auto:1b}
fill ~1 ~ ~ ~1 ~ ~ repeating_command_block 0 keep {Command:"/function exxabite:glass_normal",auto:1b}
fill ~ ~ ~-1 ~ ~ ~-1 repeating_command_block 0 keep {Command:"/function exxabite:glass_normal",auto:1b}
fill ~ ~ ~1 ~ ~ ~1 repeating_command_block 0 keep {Command:"/function exxabite:glass_normal",auto:1b}
fill ~ ~-1 ~ ~ ~-1 ~ repeating_command_block 0 keep {Command:"/function exxabite:glass_normal",auto:1b}

setblock ~ ~ ~ water 0
#fill ~ ~-1 ~ ~ ~-1 ~ concrete 0 replace bedrock 0

fill ~-10 ~-1 ~ ~-10 ~-1 ~ air 0 replace bedrock 0
fill ~-10 ~-1 ~ ~-10 ~-1 ~ repeating_command_block 0 keep {Command:"/function exxabite:glass_west",auto:1b}

fill ~10 ~-1 ~ ~10 ~-1 ~ air 0 replace bedrock 0
fill ~10 ~-1 ~ ~10 ~-1 ~ repeating_command_block 0 keep {Command:"/function exxabite:glass_east",auto:1b}

fill ~ ~-1 ~-10 ~ ~-1 ~-20 air 0 replace bedrock 0
fill ~ ~-1 ~-10 ~ ~-1 ~-20 repeating_command_block 0 keep {Command:"/function exxabite:glass_north",auto:1b}

fill ~ ~-1 ~10 ~ ~-1 ~20 air 0 replace bedrock 0
fill ~ ~-1 ~10 ~ ~-1 ~20 repeating_command_block 0 keep {Command:"/function exxabite:glass_south",auto:1b}
