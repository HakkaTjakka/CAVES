setblock ~ ~ ~ air 0 replace

fill ~ ~ ~ ~ ~ ~ repeating_command_block 0 replace {Command:"function exxabite:spiral_east_west_starter_01",auto:1b}
setblock ~-1 ~ ~ air 0 replace
fill ~-1 ~ ~ ~-1 ~ ~ repeating_command_block 0 replace {Command:"function exxabite:spiral_south_north_east_west",auto:1b}

#fill ~2 ~7 ~-3 ~2 ~7 ~-3 repeating_command_block 0 replace {Command:"function exxabite:spiral_east_07",auto:1b}
#fill ~ ~8 ~ ~ ~8 ~ repeating_command_block 0 replace {Command:"function exxabite:spiral_west_01",auto:1b}
