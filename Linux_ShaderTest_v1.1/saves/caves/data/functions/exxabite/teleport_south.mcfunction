setblock ~ ~ ~ air 0
fill ~ ~ ~-1 ~ ~ ~-1 redstone_block 0
fill ~ ~1 ~-1 ~ ~1 ~-1 golden_rail 0

fill ~ ~ ~ ~ ~ ~ repeating_command_block 0 keep {Command:"/function exxabite:teleport_rail_south",auto:1b}
