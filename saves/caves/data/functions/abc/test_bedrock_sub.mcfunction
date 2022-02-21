#setblock ~ ~ ~ air 0
setblock ~ ~ ~ concrete 0
setblock ~ ~9 ~ air 0
fill ~ ~9 ~ ~ ~9 ~ repeating_command_block 0 keep {Command:"function abc:rails_e",auto:1b}
fill ~-16 ~9 ~ ~-16 ~9 ~ repeating_command_block 0 keep {Command:"function abc:rails_e",auto:1b}
fill ~16 ~9 ~ ~16 ~9 ~ repeating_command_block 0 keep {Command:"function abc:rails_e",auto:1b}
fill ~-32 ~9 ~ ~-32 ~9 ~ repeating_command_block 0 keep {Command:"function abc:rails_e",auto:1b}
fill ~32 ~9 ~ ~32 ~9 ~ repeating_command_block 0 keep {Command:"function abc:rails_e",auto:1b}

