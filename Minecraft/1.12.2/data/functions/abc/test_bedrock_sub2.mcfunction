#setblock ~ ~ ~ air 0
setblock ~ ~ ~ concrete 0
setblock ~ ~9 ~ air 0
fill ~ ~9 ~ ~ ~9 ~ repeating_command_block 0 keep {Command:"function abc:rails_f",auto:1b}
fill ~ ~9 ~-16 ~ ~9 ~-16 repeating_command_block 0 keep {Command:"function abc:rails_f",auto:1b}
fill ~ ~9 ~16 ~ ~9 ~16 repeating_command_block 0 keep {Command:"function abc:rails_f",auto:1b}
fill ~ ~9 ~-32 ~ ~9 ~-32 repeating_command_block 0 keep {Command:"function abc:rails_f",auto:1b}
fill ~ ~9 ~32 ~ ~9 ~32 repeating_command_block 0 keep {Command:"function abc:rails_f",auto:1b}

