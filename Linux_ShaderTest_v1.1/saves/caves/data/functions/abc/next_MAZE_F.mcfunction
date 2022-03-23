setblock ~ ~ ~ air 0
fill ~ ~ ~ ~ ~ ~ command_block 0 keep {Command:"/function abc:current_MAZE_E"}
fill ~-1 ~ ~-1 ~1 ~ ~1 glowstone 0 replace glowstone 0
fill ~-1 ~ ~-1 ~1 ~ ~1 glowstone 0 keep
fill ~-1 ~ ~ ~-1 ~ ~ glowstone 0 replace redstone_block 0
fill ~-6 ~-5 ~4 ~-6 ~-5 ~4 command_block 0 keep {Command:"function abc:MAZE_NEXT_A"}
setblock ~-6 ~-4 ~4 light_weighted_pressure_plate 0 keep
fill ~-5 ~-5 ~3 ~-5 ~-5 ~3 command_block 0 keep {Command:"function abc:MAZE_NEXT_B"}
setblock ~-5 ~-4 ~3 light_weighted_pressure_plate 0 keep
fill ~-4 ~-5 ~4 ~-4 ~-5 ~4 command_block 0 keep {Command:"function abc:MAZE_NEXT_C"}
setblock ~-4 ~-4 ~4 light_weighted_pressure_plate 0 keep
fill ~-3 ~-5 ~3 ~-3 ~-5 ~3 command_block 0 keep {Command:"function abc:MAZE_NEXT_D"}
setblock ~-3 ~-4 ~3 light_weighted_pressure_plate 0 keep
fill ~-2 ~-5 ~4 ~-2 ~-5 ~4 command_block 0 keep {Command:"function abc:MAZE_NEXT_E"}
setblock ~-2 ~-4 ~4 light_weighted_pressure_plate 0 keep
fill ~-1 ~-5 ~3 ~-1 ~-5 ~3 command_block 0 keep {Command:"function abc:MAZE_NEXT_F"}
setblock ~-1 ~-4 ~3 light_weighted_pressure_plate 0 keep
fill ~0 ~-5 ~4 ~0 ~-5 ~4 command_block 0 keep {Command:"function abc:MAZE_NEXT_G"}
setblock ~0 ~-4 ~4 light_weighted_pressure_plate 0 keep
fill ~1 ~-5 ~3 ~1 ~-5 ~3 command_block 0 keep {Command:"function abc:MAZE_NEXT_H"}
setblock ~1 ~-4 ~3 light_weighted_pressure_plate 0 keep
fill ~2 ~-5 ~4 ~2 ~-5 ~4 command_block 0 keep {Command:"function abc:MAZE_NEXT_I"}
setblock ~2 ~-4 ~4 light_weighted_pressure_plate 0 keep
fill ~3 ~-5 ~3 ~3 ~-5 ~3 command_block 0 keep {Command:"function abc:MAZE_NEXT_J"}
setblock ~3 ~-4 ~3 light_weighted_pressure_plate 0 keep
fill ~4 ~-5 ~4 ~4 ~-5 ~4 command_block 0 keep {Command:"function abc:MAZE_NEXT_K"}
setblock ~4 ~-4 ~4 light_weighted_pressure_plate 0 keep
fill ~5 ~-5 ~3 ~5 ~-5 ~3 command_block 0 keep {Command:"function abc:MAZE_NEXT_L"}
setblock ~5 ~-4 ~3 light_weighted_pressure_plate 0 keep
fill ~6 ~-5 ~4 ~6 ~-5 ~4 command_block 0 keep {Command:"function abc:MAZE_NEXT_M"}
setblock ~6 ~-4 ~4 light_weighted_pressure_plate 0 keep
fill ~-6 ~-1 ~4 ~-6 ~-1 ~4 command_block 0 keep {Command:"function abc:MAZE_NEXT_N"}
setblock ~-6 ~0 ~4 light_weighted_pressure_plate 0 keep
fill ~-5 ~-1 ~3 ~-5 ~-1 ~3 command_block 0 keep {Command:"function abc:MAZE_NEXT_O"}
setblock ~-5 ~0 ~3 light_weighted_pressure_plate 0 keep
fill ~-4 ~-1 ~4 ~-4 ~-1 ~4 command_block 0 keep {Command:"function abc:MAZE_NEXT_P"}
setblock ~-4 ~0 ~4 light_weighted_pressure_plate 0 keep
fill ~-3 ~-1 ~3 ~-3 ~-1 ~3 command_block 0 keep {Command:"function abc:MAZE_NEXT_Q"}
setblock ~-3 ~0 ~3 light_weighted_pressure_plate 0 keep
fill ~-2 ~-1 ~4 ~-2 ~-1 ~4 command_block 0 keep {Command:"function abc:MAZE_NEXT_R"}
setblock ~-2 ~0 ~4 light_weighted_pressure_plate 0 keep
fill ~-1 ~-1 ~3 ~-1 ~-1 ~3 command_block 0 keep {Command:"function abc:MAZE_NEXT_S"}
setblock ~-1 ~0 ~3 light_weighted_pressure_plate 0 keep
fill ~0 ~-1 ~4 ~0 ~-1 ~4 command_block 0 keep {Command:"function abc:MAZE_NEXT_T"}
setblock ~0 ~0 ~4 light_weighted_pressure_plate 0 keep
fill ~1 ~-1 ~3 ~1 ~-1 ~3 command_block 0 keep {Command:"function abc:MAZE_NEXT_U"}
setblock ~1 ~0 ~3 light_weighted_pressure_plate 0 keep
fill ~2 ~-1 ~4 ~2 ~-1 ~4 command_block 0 keep {Command:"function abc:MAZE_NEXT_V"}
setblock ~2 ~0 ~4 light_weighted_pressure_plate 0 keep
fill ~3 ~-1 ~3 ~3 ~-1 ~3 command_block 0 keep {Command:"function abc:MAZE_NEXT_W"}
setblock ~3 ~0 ~3 light_weighted_pressure_plate 0 keep
fill ~4 ~-1 ~4 ~4 ~-1 ~4 command_block 0 keep {Command:"function abc:MAZE_NEXT_X"}
setblock ~4 ~0 ~4 light_weighted_pressure_plate 0 keep
fill ~5 ~-1 ~3 ~5 ~-1 ~3 command_block 0 keep {Command:"function abc:MAZE_NEXT_Y"}
setblock ~5 ~0 ~3 light_weighted_pressure_plate 0 keep
fill ~6 ~-1 ~4 ~6 ~-1 ~4 command_block 0 keep {Command:"function abc:MAZE_NEXT_Z"}
setblock ~6 ~0 ~4 light_weighted_pressure_plate 0 keep
kill @e[type=Bat,r=8]
summon minecraft:bat ~ ~5 ~
summon minecraft:bat ~ ~5 ~
summon minecraft:bat ~ ~5 ~
summon minecraft:bat ~ ~5 ~
fill ~6 ~-8 ~9 ~6 ~-8 ~9 wooden_button 3 keep
fill ~6 ~7 ~9 ~6 ~7 ~9 stone_button 3 keep
fill ~-7 ~-8 ~9 ~-7 ~-8 ~9 stone_button 3 keep
fill ~-7 ~7 ~9 ~-7 ~7 ~9 wooden_button 3 keep
fill ~7 ~-7 ~9 ~7 ~-7 ~9 wooden_button 3 keep
fill ~7 ~6 ~9 ~7 ~6 ~9 wooden_button 3 keep
fill ~-8 ~-7 ~9 ~-8 ~-7 ~9 wooden_button 3 keep
fill ~-8 ~6 ~9 ~-8 ~6 ~9 wooden_button 3 keep
fill ~6 ~-8 ~-10 ~6 ~-8 ~-10 stone_button 4 keep
fill ~6 ~7 ~-10 ~6 ~7 ~-10 wooden_button 4 keep
fill ~-7 ~-8 ~-10 ~-7 ~-8 ~-10 wooden_button 4 keep
fill ~-7 ~7 ~-10 ~-7 ~7 ~-10 stone_button 4 keep
fill ~7 ~-7 ~-10 ~7 ~-7 ~-10 wooden_button 4 keep
fill ~7 ~6 ~-10 ~7 ~6 ~-10 wooden_button 4 keep
fill ~-8 ~-7 ~-10 ~-8 ~-7 ~-10 wooden_button 4 keep
fill ~-8 ~6 ~-10 ~-8 ~6 ~-10 wooden_button 4 keep
fill ~9 ~-8 ~6 ~9 ~-8 ~6 stone_button 1 keep
fill ~9 ~7 ~6 ~9 ~7 ~6 wooden_button 1 keep
fill ~9 ~-8 ~-7 ~9 ~-8 ~-7 wooden_button 1 keep
fill ~9 ~7 ~-7 ~9 ~7 ~-7 stone_button 1 keep
fill ~9 ~-7 ~7 ~9 ~-7 ~7 wooden_button 1 keep
fill ~9 ~6 ~7 ~9 ~6 ~7 wooden_button 1 keep
fill ~9 ~-7 ~-8 ~9 ~-7 ~-8 wooden_button 1 keep
fill ~9 ~6 ~-8 ~9 ~6 ~-8 wooden_button 1 keep
fill ~-10 ~-8 ~6 ~-10 ~-8 ~6 wooden_button 2 keep
fill ~-10 ~7 ~6 ~-10 ~7 ~6 stone_button 2 keep
fill ~-10 ~-8 ~-7 ~-10 ~-8 ~-7 stone_button 2 keep
fill ~-10 ~7 ~-7 ~-10 ~7 ~-7 wooden_button 2 keep
fill ~-10 ~-7 ~7 ~-10 ~-7 ~7 wooden_button 2 keep
fill ~-10 ~6 ~7 ~-10 ~6 ~7 wooden_button 2 keep
fill ~-10 ~-7 ~-8 ~-10 ~-7 ~-8 wooden_button 2 keep
fill ~-10 ~6 ~-8 ~-10 ~6 ~-8 wooden_button 2 keep
setblock ~6 ~7 ~7 air 0
fill ~6 ~7 ~7 ~6 ~7 ~7 command_block 0 keep {Command:"function abc:MAZE_SOUTH_NEXT_F"}
setblock ~-7 ~-8 ~7 air 0
fill ~-7 ~-8 ~7 ~-7 ~-8 ~7 command_block 0 keep {Command:"function abc:MAZE_SOUTH_ERASE"}
setblock ~6 ~-8 ~7 air 0
fill ~6 ~-8 ~7 ~6 ~-8 ~7 command_block 0 keep {Command:"function abc:MAZE_SOUTH_Y_NEG"}
setblock ~-7 ~7 ~7 air 0
fill ~-7 ~7 ~7 ~-7 ~7 ~7 command_block 0 keep {Command:"function abc:MAZE_SOUTH_Y_POS"}
setblock ~7 ~-7 ~7 air 0
fill ~7 ~-7 ~7 ~7 ~-7 ~7 command_block 0 keep {Command:"function abc:MAZE_SOUTH_X_POS"}
setblock ~-8 ~6 ~7 air 0
fill ~-8 ~6 ~7 ~-8 ~6 ~7 command_block 0 keep {Command:"function abc:MAZE_SOUTH_X_NEG"}
setblock ~-8 ~7 ~7 concrete 15
setblock ~-7 ~7 ~-8 air 0
fill ~-7 ~7 ~-8 ~-7 ~7 ~-8 command_block 0 keep {Command:"function abc:MAZE_NORTH_NEXT_F"}
setblock ~6 ~-8 ~-8 air 0
fill ~6 ~-8 ~-8 ~6 ~-8 ~-8 command_block 0 keep {Command:"function abc:MAZE_NORTH_ERASE"}
setblock ~6 ~7 ~-8 air 0
fill ~6 ~7 ~-8 ~6 ~7 ~-8 command_block 0 keep {Command:"function abc:MAZE_NORTH_Y_POS"}
setblock ~-7 ~-8 ~-8 air 0
fill ~-7 ~-8 ~-8 ~-7 ~-8 ~-8 command_block 0 keep {Command:"function abc:MAZE_NORTH_Y_NEG"}
setblock ~7 ~6 ~-8 air 0
fill ~7 ~6 ~-8 ~7 ~6 ~-8 command_block 0 keep {Command:"function abc:MAZE_NORTH_X_POS"}
setblock ~-8 ~-7 ~-8 air 0
fill ~-8 ~-7 ~-8 ~-8 ~-7 ~-8 command_block 0 keep {Command:"function abc:MAZE_NORTH_X_NEG"}
setblock ~7 ~7 ~-7 air 0
fill ~7 ~7 ~-7 ~7 ~7 ~-7 command_block 0 keep {Command:"function abc:MAZE_WEST_NEXT_F"}
setblock ~7 ~-8 ~6 air 0
fill ~7 ~-8 ~6 ~7 ~-8 ~6 command_block 0 keep {Command:"function abc:MAZE_WEST_ERASE"}
setblock ~7 ~7 ~6 air 0
fill ~7 ~7 ~6 ~7 ~7 ~6 command_block 0 keep {Command:"function abc:MAZE_WEST_Y_POS"}
setblock ~7 ~-8 ~-7 air 0
fill ~7 ~-8 ~-7 ~7 ~-8 ~-7 command_block 0 keep {Command:"function abc:MAZE_WEST_Y_NEG"}
setblock ~7 ~6 ~7 air 0
fill ~7 ~6 ~7 ~7 ~6 ~7 command_block 0 keep {Command:"function abc:MAZE_WEST_Z_POS"}
setblock ~7 ~-7 ~-8 air 0
fill ~7 ~-7 ~-8 ~7 ~-7 ~-8 command_block 0 keep {Command:"function abc:MAZE_WEST_Z_NEG"}
setblock ~-8 ~7 ~6 air 0
fill ~-8 ~7 ~6 ~-8 ~7 ~6 command_block 0 keep {Command:"function abc:MAZE_EAST_NEXT_F"}
setblock ~-8 ~-8 ~-7 air 0
fill ~-8 ~-8 ~-7 ~-8 ~-8 ~-7 command_block 0 keep {Command:"function abc:MAZE_EAST_ERASE"}
setblock ~-8 ~-8 ~6 air 0
fill ~-8 ~-8 ~6 ~-8 ~-8 ~6 command_block 0 keep {Command:"function abc:MAZE_EAST_Y_NEG"}
setblock ~-8 ~7 ~-7 air 0
fill ~-8 ~7 ~-7 ~-8 ~7 ~-7 command_block 0 keep {Command:"function abc:MAZE_EAST_Y_POS"}
setblock ~-8 ~-7 ~7 air 0
fill ~-8 ~-7 ~7 ~-8 ~-7 ~7 command_block 0 keep {Command:"function abc:MAZE_EAST_Z_POS"}
setblock ~-8 ~6 ~-8 air 0
fill ~-8 ~6 ~-8 ~-8 ~6 ~-8 command_block 0 keep {Command:"function abc:MAZE_EAST_Z_NEG"}
setblock ~0 ~-5 ~0 air 0 replace repeating_command_block 0
setblock ~0 ~-4 ~0 air 0 replace redstone_block 0
fill ~0 ~-5 ~0 ~0 ~-5 ~0 command_block 0 keep {Command:"/function abc:letter_MAZE_F"}
