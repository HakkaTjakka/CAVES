fill ~ ~ ~ ~ ~ ~ air 0 replace repeating_command_block

#fill ~ ~ ~ ~ ~ ~ repeating_command_block 0 keep {Command:"/function exxabite:place_physics_bomb",auto:1b}

fill ~ ~ ~ ~ ~ ~ xplosives:physics_bomb 0 replace repeating_command_block

fill ~-1 ~ ~-1 ~1 ~ ~1 concrete 0 replace glowstone 0
#fill ~ ~1 ~ ~ ~1 ~ repeating_command_block 0 keep {Command:"/function exxabite:blow_up",auto:1b}
function exxabite:blow_up_more
