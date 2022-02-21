setblock ~ ~ ~ air 0 replace repeating_command_block

#fill ~-32 ~ ~ ~-32 ~ ~ repeating_command_block 0 keep {Command:"function abc:rails_w",auto:1b}
#fill ~32 ~ ~ ~32 ~ ~ repeating_command_block 0 keep {Command:"function abc:rails_w",auto:1b}
#fill ~ ~ ~-32 ~ ~ ~-32 repeating_command_block 0 keep {Command:"function abc:rails_w",auto:1b}
#fill ~ ~ ~32 ~ ~ ~32 repeating_command_block 0 keep {Command:"function abc:rails_w",auto:1b}

#fill ~-32 ~ ~ ~-32 ~ ~ repeating_command_block 0 keep {Command:"function abc:rails_x if @e[r=32]",auto:1b}
#fill ~32 ~ ~ ~32 ~ ~ repeating_command_block 0 keep {Command:"function abc:rails_x if @e[r=32]",auto:1b}
#fill ~ ~ ~-32 ~ ~ ~-32 repeating_command_block 0 keep {Command:"function abc:rails_x if @e[r=32]",auto:1b}
#fill ~ ~ ~32 ~ ~ ~32 repeating_command_block 0 keep {Command:"function abc:rails_x if @e[r=32]",auto:1b}

#fill ~-32 ~ ~ ~-32 ~ ~ repeating_command_block 0 keep {Command:"function abc:rails_v",auto:1b}
#fill ~32 ~ ~ ~32 ~ ~ repeating_command_block 0 keep {Command:"function abc:rails_t",auto:1b}
#fill ~ ~ ~-32 ~ ~ ~-32 repeating_command_block 0 keep {Command:"function abc:rails_s",auto:1b}
#fill ~ ~ ~32 ~ ~ ~32 repeating_command_block 0 keep {Command:"function abc:rails_u",auto:1b}

fill ~-32 ~ ~ ~-32 ~ ~ repeating_command_block 0 keep {Command:"function abc:rails_t if @e[r=64]",auto:1b}
fill ~32 ~ ~ ~32 ~ ~ repeating_command_block 0 keep {Command:"function abc:rails_v if @e[r=64]",auto:1b}
fill ~ ~ ~-32 ~ ~ ~-32 repeating_command_block 0 keep {Command:"function abc:rails_s if @e[r=64]",auto:1b}
fill ~ ~ ~32 ~ ~ ~32 repeating_command_block 0 keep {Command:"function abc:rails_u if @e[r=64]",auto:1b}

#fill ~-64 253 ~ ~-64 253 ~ repeating_command_block 0 keep {Command:"function abc:do_roof if @e[r=64]",auto:1b}
#fill ~64 253 ~ ~64 253 ~ repeating_command_block 0 keep {Command:"function abc:do_roof if @e[r=64]",auto:1b}
#fill ~ 253 ~-64 ~ 253 ~-64 repeating_command_block 0 keep {Command:"function abc:do_roof if @e[r=64]",auto:1b}
#fill ~ 253 ~64 ~ 253 ~64 repeating_command_block 0 keep {Command:"function abc:do_roof if @e[r=64]",auto:1b}

fill ~-64 ~-20 ~ ~-64 ~-20 ~ repeating_command_block 0 keep {Command:"function abc:test if @e[r=64]",auto:1b}
fill ~64 ~-20 ~ ~64 ~-20 ~ repeating_command_block 0 keep {Command:"function abc:test if @e[r=64]",auto:1b}
fill ~ ~-20 ~-64 ~ ~-20 ~-64 repeating_command_block 0 keep {Command:"function abc:test if @e[r=64]",auto:1b}
fill ~ ~-20 ~64 ~ ~-20 ~64 repeating_command_block 0 keep {Command:"function abc:test if @e[r=64]",auto:1b}

