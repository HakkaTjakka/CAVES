setblock ~ ~ ~ air 0
#fill ~ ~ ~ ~ ~ ~ repeating_command_block 0 keep {Command:"function abc:letter_maze_a",auto:1b}
#summon minecraft:bat ~ ~5 ~
#summon minecraft:bat ~ ~5 ~
#summon minecraft:bat ~ ~5 ~


fill ~-16 ~ ~ ~-16 ~ ~ repeating_command_block 0 keep {Command:"function abc:letter_maze_a",auto:1b}
fill ~ ~ ~ ~ ~ ~ repeating_command_block 0 keep {Command:"function abc:maze",auto:1b}
#tp @a ~16 ~ ~

#fill ~11 ~ ~ ~11 ~ ~ repeating_command_block 0 keep {Command:"function abc:letter_maze_a",auto:1b}
#fill ~27 ~ ~ ~27 ~ ~ repeating_command_block 0 keep {Command:"function abc:maze",auto:1b}

#setblock ~-32 ~ ~ air 0
#fill ~-32 ~ ~ ~-32 ~ ~ repeating_command_block 0 keep {Command:"function abc:letter_maze_a",auto:1b}

#setblock ~-5 ~ ~ air 0
#fill ~-5 ~ ~ ~-5 ~ ~ repeating_command_block 0 keep {Command:"function abc:letter_maze_a",auto:1b}


#fill ~-16 ~-5 ~ ~-16 ~-5 ~ repeating_command_block 0 keep {Command:"function abc:letter_maze_a",auto:1b}
#fill ~ ~-5 ~ ~ ~-5 ~ repeating_command_block 0 keep {Command:"function abc:maze",auto:1b}
