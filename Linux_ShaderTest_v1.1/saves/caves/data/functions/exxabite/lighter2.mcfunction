fill ~-1 ~ ~ ~1 ~ ~ air 0 replace glowstone 0
fill ~ ~-1 ~ ~ ~1 ~ air 0 replace glowstone 0
fill ~ ~ ~-1 ~ ~ ~1 air 0 replace glowstone 0
fill ~-1 ~ ~ ~1 ~ ~ glowstone 0 replace wool 0
fill ~ ~-1 ~ ~ ~1 ~ glowstone 0 replace wool 0
fill ~ ~ ~-1 ~ ~ ~1 glowstone 0 replace wool 0
setblock ~ ~ ~ air 0
fill ~ ~ ~ ~ ~ ~ repeating_command_block 0 keep {Command:"/function exxabite:clean_glowstone",auto:1b}




