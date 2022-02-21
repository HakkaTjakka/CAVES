#fill ~-1 ~ ~ ~-1 ~ ~ repeating_command_block 0 keep {Command:"/function exxabite:fill",auto:1b}
#fill ~1 ~ ~ ~1 ~ ~ repeating_command_block 0 keep {Command:"/function exxabite:fill",auto:1b}
#fill ~ ~ ~-1 ~ ~ ~-1 repeating_command_block 0 keep {Command:"/function exxabite:fill",auto:1b}
#fill ~ ~ ~1 ~ ~ ~1 repeating_command_block 0 keep {Command:"/function exxabite:fill",auto:1b}
#fill ~ ~-1 ~ ~ ~-1 ~ repeating_command_block 0 keep {Command:"/function exxabite:fill",auto:1b}
##fill ~ ~1 ~ ~ ~1 ~ repeating_command_block 0 keep {Command:"/function exxabite:fill",auto:1b}

#setblock ~ ~ ~ planks
#setblock ~ ~ ~ flowing_water
setblock ~ ~ ~ concrete 5
#setblock ~ ~ ~ stone 0
#setblock ~ ~ ~ flowing_water

#fill ~-1 ~-1 ~-1 ~1 ~-1 ~1 xplosives:physics_bomb 0 replace glowstone 0

#fill ~-1 ~ ~ ~1 ~ ~ planks 0 replace air 0
#fill ~ ~-1 ~ ~ ~1 ~ planks 0 replace air 0
#fill ~ ~ ~-1 ~ ~ ~1 planks 0 replace air 0
#fill ~-1 ~ ~ ~1 ~ ~ air 0 replace glowstone 0
#fill ~ ~-1 ~ ~ ~1 ~ air 0 replace glowstone 0
#fill ~ ~ ~-1 ~ ~ ~1 air 0 replace glowstone 0
##fill ~-1 ~ ~ ~1 ~ ~ repeating_command_block 0 keep {Command:"/function exxabite:place_physics_bomb",auto:1b}
##fill ~ ~-1 ~ ~ ~1 ~ repeating_command_block 0 keep {Command:"/function exxabite:place_physics_bomb",auto:1b}
##fill ~ ~ ~-1 ~ ~ ~1 repeating_command_block 0 keep {Command:"/function exxabite:place_physics_bomb",auto:1b}
#fill ~-1 ~ ~ ~1 ~ ~ xplosives:physics_bomb 0 keep
#fill ~ ~-1 ~ ~ ~1 ~ xplosives:physics_bomb 0 keep
#fill ~ ~ ~-1 ~ ~ ~1 xplosives:physics_bomb 0 keep
#fill ~-1 ~ ~ ~1 ~ ~ air 0 replace planks 0
#fill ~ ~-1 ~ ~ ~1 ~ air 0 replace planks 0
#fill ~ ~ ~-1 ~ ~ ~1 air 0 replace planks 0

