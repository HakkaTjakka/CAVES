#setblock ~ ~1 ~ minecraft:repeating_command_block 0 replace {Command:"/function exxabite:test",auto:1b}
#setblock ~ ~-1 ~ minecraft:repeating_command_block 0 concrete  {Command:"/function exxabite:test",auto:1b}
fill ~ ~ ~1 ~ ~ ~2 command_block 0 replace {Command:"/function exxabite:test",auto:1b}
#setblock ~ ~ ~-1 command_block 0 replace {Command:"/function exxabite:test",auto:1b} 
#setblock ~1 ~ ~ command_block 0 replace {Command:"/function exxabite:goed",auto:1b}
#setblock ~-1 ~ ~ command_block 0 replace {Command:"/function exxabite:test",auto:1b}
#setblock ~ ~ ~-1 command_block 0 replace {Command:"/setblock ~ ~ ~-1 water",auto:1b}
#setblock ~ ~ ~ command_block 0 replace {Command:"/setblock ~ ~ ~ water",auto:1b}
setblock ~ ~ ~ water


