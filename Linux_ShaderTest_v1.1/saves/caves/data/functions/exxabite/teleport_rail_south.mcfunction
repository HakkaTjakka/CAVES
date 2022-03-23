 fill ~-1 ~ ~ ~1 ~3 ~ air 0 replace

#fill ~ ~ ~ ~ ~ ~ redstone_block 0
#fill ~ ~ ~-1 ~ ~ ~ concrete 14

#fill ~1 ~ ~ ~1 ~ ~ concrete 0
#fill ~-1 ~ ~ ~-1 ~ ~ concrete 0

 fill ~1 ~ ~ ~1 ~ ~ stained_glass 0
 fill ~-1 ~ ~ ~-1 ~ ~ stained_glass 0

#fill ~ ~1 ~ ~ ~1 ~ golden_rail 0

 setblock ~ ~ ~1 air 0
 fill ~ ~ ~1 ~ ~ ~1 repeating_command_block 0 keep {Command:"/function exxabite:teleport_south",auto:1b}

