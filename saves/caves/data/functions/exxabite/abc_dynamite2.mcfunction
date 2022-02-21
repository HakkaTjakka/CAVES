fill ~-1 ~ ~ ~1 ~ ~ planks 0 replace air 0
fill ~ ~-1 ~ ~ ~1 ~ planks 0 replace air 0
fill ~ ~ ~-1 ~ ~ ~1 planks 0 replace air 0

fill ~-1 ~ ~ ~1 ~ ~ air 0 replace concrete 13
fill ~ ~-1 ~ ~ ~1 ~ air 0 replace concrete 13
fill ~ ~ ~-1 ~ ~ ~1 air 0 replace concrete 13

fill ~-1 ~ ~ ~1 ~ ~ repeating_command_block 0 keep {Command:"/function exxabite:abc_dynamite2",auto:1b}
fill ~ ~-1 ~ ~ ~1 ~ repeating_command_block 0 keep {Command:"/function exxabite:abc_dynamite2",auto:1b}
fill ~ ~ ~-1 ~ ~ ~1 repeating_command_block 0 keep {Command:"/function exxabite:abc_dynamite2",auto:1b}

fill ~-1 ~ ~ ~1 ~ ~ air 0 replace planks 0
fill ~ ~-1 ~ ~ ~1 ~ air 0 replace planks 0
fill ~ ~ ~-1 ~ ~ ~1 air 0 replace planks 0

setblock ~ ~ ~ tnt 0
fill ~1 ~1 ~1 ~-1 ~-1 ~-1 xplosives:physics_bomb 0 replace concrete 15
