setblock ~ ~ ~ air 0 replace repeating_command_block

fill ~-32 ~ ~ ~-32 ~ ~ repeating_command_block 0 keep {Command:"function abc:rails_w",auto:1b}
fill ~32 ~ ~ ~32 ~ ~ repeating_command_block 0 keep {Command:"function abc:rails_w",auto:1b}
fill ~ ~ ~-32 ~ ~ ~-32 repeating_command_block 0 keep {Command:"function abc:rails_w",auto:1b}
fill ~ ~ ~32 ~ ~ ~32 repeating_command_block 0 keep {Command:"function abc:rails_w",auto:1b}

#fill ~-32 ~ ~ ~-32 ~ ~ repeating_command_block 0 keep {Command:"function abc:rails_x if @e[r=32]",auto:1b}
#fill ~32 ~ ~ ~32 ~ ~ repeating_command_block 0 keep {Command:"function abc:rails_x if @e[r=32]",auto:1b}
#fill ~ ~ ~-32 ~ ~ ~-32 repeating_command_block 0 keep {Command:"function abc:rails_x if @e[r=32]",auto:1b}
#fill ~ ~ ~32 ~ ~ ~32 repeating_command_block 0 keep {Command:"function abc:rails_x if @e[r=32]",auto:1b}

#fill ~-32 ~ ~ ~-32 ~ ~ repeating_command_block 0 keep {Command:"function abc:rails_v",auto:1b}
#fill ~32 ~ ~ ~32 ~ ~ repeating_command_block 0 keep {Command:"function abc:rails_t",auto:1b}
#
#fill ~ ~ ~-32 ~ ~ ~-32 repeating_command_block 0 keep {Command:"function abc:rails_s",auto:1b}
#fill ~ ~ ~32 ~ ~ ~32 repeating_command_block 0 keep {Command:"function abc:rails_u",auto:1b}
