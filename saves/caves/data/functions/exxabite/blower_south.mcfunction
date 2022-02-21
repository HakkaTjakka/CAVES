fill ~-1 ~-1 ~50 ~-1 ~-1 ~50 repeating_command_block 0 keep {Command:"/function exxabite:blower_south",auto:1b}

#fill ~-1 ~50 ~-1 ~-1 ~50 ~-1 repeating_command_block 0 keep {Command:"/function exxabite:blower_up",auto:1b}
fill ~-1 ~-50 ~-1 ~-1 ~-50 ~-1 repeating_command_block 0 keep {Command:"/function exxabite:blower_down",auto:1b}

setblock ~ ~ ~ air 0 replace repeating_command_block
fill ~ ~ ~ ~ ~ ~ repeating_command_block 0 keep {Command:"/function exxabite:blow_up_air",auto:1b}



