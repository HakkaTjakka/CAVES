fill ~-1 ~ ~ ~-1 ~ ~ air 0 replace water 0
fill ~1 ~ ~ ~1 ~ ~ air 0 replace water 0
fill ~ ~ ~-1 ~ ~ ~-1 air 0 replace water 0
fill ~ ~ ~1 ~ ~ ~1 air 0 replace water 0

fill ~-1 ~ ~ ~-1 ~ ~ repeating_command_block 0 keep {Command:"/function exxabite:w2",auto:1b}
fill ~1 ~ ~ ~1 ~ ~ repeating_command_block 0 keep {Command:"/function exxabite:w2",auto:1b}
fill ~ ~ ~-1 ~ ~ ~-1 repeating_command_block 0 keep {Command:"/function exxabite:w2",auto:1b}
fill ~ ~ ~1 ~ ~ ~1 repeating_command_block 0 keep {Command:"/function exxabite:w2",auto:1b}
fill ~ ~-1 ~ ~ ~-1 ~ repeating_command_block 0 keep {Command:"/function exxabite:w2",auto:1b}

setblock ~ ~ ~ concrete 0

fill ~-40 ~ ~ ~-40 ~ ~ air 0 replace bedrock 0
fill ~-40 ~ ~ ~-40 ~ ~ air 0 replace water 0
fill ~-40 ~ ~ ~-40 ~ ~ repeating_command_block 0 keep {Command:"/function exxabite:w2",auto:1b}
fill ~40 ~ ~ ~40 ~ ~ air 0 replace bedrock 0
fill ~40 ~ ~ ~40 ~ ~ air 0 replace water 0
fill ~40 ~ ~ ~40 ~ ~ repeating_command_block 0 keep {Command:"/function exxabite:w2",auto:1b}
fill ~40 ~ ~ ~40 ~ ~ air 0 replace bedrock 0
fill ~40 ~ ~ ~40 ~ ~ air 0 replace water 0
fill ~ ~ ~-40 ~ ~ ~-40 repeating_command_block 0 keep {Command:"/function exxabite:w2",auto:1b}
fill ~40 ~ ~ ~40 ~ ~ air 0 replace bedrock 0
fill ~40 ~ ~ ~40 ~ ~ air 0 replace water 0
fill ~ ~ ~40 ~ ~ ~40 repeating_command_block 0 keep {Command:"/function exxabite:w2",auto:1b}
