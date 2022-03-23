fill ~10 ~ ~ ~10 ~ ~ bedrock 0 replace repeating_command_block 0

#fill ~ ~1 ~ ~ ~1 ~ air 0 replace water 0
fill ~ ~1 ~ ~ ~1 ~ repeating_command_block 0 keep {Command:"/function exxabite:glass_normal",auto:1b}

fill ~-10 ~ ~ ~-10 ~ ~ air 0 replace bedrock 0
fill ~-10 ~ ~ ~-10 ~ ~ repeating_command_block 0 keep {Command:"/function exxabite:glass_west",auto:1b}

fill ~ ~ ~10 ~ ~ ~10 air 0 replace bedrock 0
fill ~ ~ ~10 ~ ~ ~10 repeating_command_block 0 keep {Command:"/function exxabite:glass_south",auto:1b}

fill ~ ~ ~-10 ~ ~ ~-10 air 0 replace bedrock 0
fill ~ ~ ~-10 ~ ~ ~-10 repeating_command_block 0 keep {Command:"/function exxabite:glass_north",auto:1b}

fill ~-200 ~ ~ ~-200 ~250 ~ redstone_block 0 replace tnt 0