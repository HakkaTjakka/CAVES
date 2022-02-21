fill ~-1 ~ ~ ~1 ~ ~ planks 0 replace air 0
fill ~ ~-1 ~ ~ ~1 ~ planks 0 replace air 0
fill ~ ~ ~-1 ~ ~ ~1 planks 0 replace air 0

fill ~-1 ~ ~ ~1 ~ ~ air 0 replace glass 0
fill ~ ~-1 ~ ~ ~1 ~ air 0 replace glass 0
fill ~ ~ ~-1 ~ ~ ~1 air 0 replace glass 0

fill ~ ~ ~-1 ~ ~ ~1 air 0 replace glass 0

fill ~1 ~ ~ ~1 ~ ~ repeating_command_block 0 keep {Command:"/function exxabite:hoppa_1",auto:1b}
fill ~ ~1 ~ ~ ~1 ~ repeating_command_block 0 keep {Command:"/function exxabite:hoppa_2",auto:1b}
fill ~ ~ ~1 ~ ~ ~1 repeating_command_block 0 keep {Command:"/function exxabite:hoppa_3",auto:1b}
fill ~-1 ~ ~ ~-1 ~ ~ repeating_command_block 0 keep {Command:"/function exxabite:hoppa_4",auto:1b}
fill ~ ~-1 ~ ~ ~-1 ~ repeating_command_block 0 keep {Command:"/function exxabite:hoppa_5",auto:1b}
fill ~ ~ ~-1 ~ ~ ~-1 repeating_command_block 0 keep {Command:"/function exxabite:hoppa_6",auto:1b}

fill ~-1 ~ ~ ~1 ~ ~ air 0 replace planks 0
fill ~ ~-1 ~ ~ ~1 ~ air 0 replace planks 0
fill ~ ~ ~-1 ~ ~ ~1 air 0 replace planks 0

setblock ~ ~ ~ wool 0