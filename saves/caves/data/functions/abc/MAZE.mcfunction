fill ~32 ~ ~ ~32 ~ ~ repeating_command_block 0 keep {Command:"function abc:maze_x_pos if @e[r=28]",auto:1b}
fill ~-32 ~ ~ ~-32 ~ ~ repeating_command_block 0 keep {Command:"function abc:maze_x_neg if @e[r=29]",auto:1b}
fill ~ ~32 ~ ~ ~32 ~ repeating_command_block 0 keep {Command:"function abc:maze_y_pos if @e[r=25]",auto:1b}
fill ~ ~-32 ~ ~ ~-32 ~ repeating_command_block 0 keep {Command:"function abc:maze_y_neg if @e[r=44]",auto:1b}
fill ~ ~ ~32 ~ ~ ~32 repeating_command_block 0 keep {Command:"function abc:maze_z_pos if @e[r=28]",auto:1b}
fill ~ ~ ~-32 ~ ~ ~-32 repeating_command_block 0 keep {Command:"function abc:maze_z_neg if @e[r=29]",auto:1b}
setblock ~ ~ ~ air 0
fill ~ ~ ~ ~ ~ ~ repeating_command_block 0 keep {Command:"function abc:letter_maze_a",auto:1b}
#tp @p ~16 ~16 ~16

#fill ~32 ~5 ~ ~32 ~5 ~ repeating_command_block 0 keep {Command:"function abc:maze_x_pos if @e[r=30]",auto:1b}
#fill ~-32 ~5 ~ ~-32 ~5 ~ repeating_command_block 0 keep {Command:"function abc:maze_x_neg if @e[r=30]",auto:1b}
#fill ~ ~37 ~ ~ ~37 ~ repeating_command_block 0 keep {Command:"function abc:maze_y_pos if @e[r=30]",auto:1b}
#fill ~ ~-27 ~ ~ ~-27 ~ repeating_command_block 0 keep {Command:"function abc:maze_y_neg if @e[r=30]",auto:1b}
#fill ~ ~5 ~32 ~ ~5 ~32 repeating_command_block 0 keep {Command:"function abc:maze_z_pos if @e[r=30]",auto:1b}
#fill ~ ~5 ~-32 ~ ~5 ~-32 repeating_command_block 0 keep {Command:"function abc:maze_z_neg if @e[r=30]",auto:1b}
#setblock ~ ~ ~ air 0
#fill ~ ~ ~ ~ ~ ~ repeating_command_block 0 keep {Command:"function abc:letter_maze_a",auto:1b}

#fill ~5 ~ ~ ~5 ~ ~ repeating_command_block 0 keep {Command:"function abc:maze_x_pos if @a[r=28]",auto:1b}
#fill ~-5 ~ ~ ~-5 ~ ~ repeating_command_block 0 keep {Command:"function abc:maze_x_neg if @a[r=28]",auto:1b}
#fill ~ ~10 ~ ~ ~10 ~ repeating_command_block 0 keep {Command:"function abc:maze_y_pos if @a[r=23]",auto:1b}
#fill ~ ~ ~ ~ ~ ~ repeating_command_block 0 keep {Command:"function abc:maze_y_neg if @a[r=33]",auto:1b}
#fill ~ ~ ~5 ~ ~ ~5 repeating_command_block 0 keep {Command:"function abc:maze_z_pos if @a[r=28]",auto:1b}
#fill ~ ~ ~-5 ~ ~ ~-5 repeating_command_block 0 keep {Command:"function abc:maze_z_neg if @a[r=28]",auto:1b}

#setblock ~ ~ ~ air 0
#fill ~ ~ ~ ~ ~ ~ repeating_command_block 0 keep {Command:"function abc:letter_maze_a",auto:1b}
