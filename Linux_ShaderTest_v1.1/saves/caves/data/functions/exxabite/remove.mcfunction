#fill ~-1 ~-1 ~-1 ~1 ~1 ~1 planks 0 replace air 0
#fill ~-1 ~-1 ~-1 ~1 ~1 ~1 air 0 replace concrete 9
#fill ~-1 ~-1 ~-1 ~1 ~1 ~1 air 0 replace glowstone 0
#fill ~-1 ~-1 ~-1 ~1 ~1 ~1 xplosives:physics_bomb 0 keep

#fill ~-1 ~-1 ~-1 ~1 ~1 ~1 repeating_command_block 0 keep {Command:"/function exxabite:place_physics_bomb2",auto:1b}

fill ~-1 ~ ~ ~1 ~ ~ planks 0 replace air 0
fill ~ ~-1 ~ ~ ~1 ~ planks 0 replace air 0
fill ~ ~ ~-1 ~ ~ ~1 planks 0 replace air 0
fill ~-1 ~ ~ ~1 ~ ~ air 0 replace tnt 0
fill ~ ~-1 ~ ~ ~1 ~ air 0 replace tnt 0
fill ~ ~ ~-1 ~ ~ ~1 air 0 replace tnt 0

fill ~-1 ~ ~ ~1 ~ ~ air 0 replace gold_block 0
fill ~ ~-1 ~ ~ ~1 ~ air 0 replace gold_block 0
fill ~ ~ ~-1 ~ ~ ~1 air 0 replace gold_block 0

fill ~-1 ~ ~ ~1 ~ ~ repeating_command_block 0 keep {Command:"/function exxabite:remove",auto:1b}
fill ~ ~-1 ~ ~ ~1 ~ repeating_command_block 0 keep {Command:"/function exxabite:remove",auto:1b}
fill ~ ~ ~-1 ~ ~ ~1 repeating_command_block 0 keep {Command:"/function exxabite:remove",auto:1b}

#fill ~-1 ~-1 ~-1 ~1 ~1 ~1 repeating_command_block 0 keep {Command:"/function exxabite:remove",auto:1b}
#setblock ~ ~ ~ glass 0 replace

fill ~-1 ~ ~ ~1 ~ ~ air 0 replace planks 0
fill ~ ~-1 ~ ~ ~1 ~ air 0 replace planks 0
fill ~ ~ ~-1 ~ ~ ~1 air 0 replace planks 0


#fill ~-1 ~-1 ~-1 ~1 ~1 ~1 air 0 replace tnt 0
#fill ~-1 ~-1 ~-1 ~1 ~1 ~1 glowstone 0 replace stained_glass 14

setblock ~ ~ ~ air 0 replace
