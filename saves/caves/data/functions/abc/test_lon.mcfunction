#fill ~ ~16 ~ ~ ~16 ~ repeating_command_block 0 keep {Command:"function abc:rails_e if @e[r=40]",auto:1b}
fill ~ ~16 ~ ~ ~16 ~ repeating_command_block 0 keep {Command:"function abc:rails_l if @e[r=40]",auto:1b}

fill ~-16 ~ ~ ~-16 ~ ~ repeating_command_block 0 keep {Command:"function abc:rails_a if @e[r=40]",auto:1b}
fill ~16 ~ ~ ~16 ~ ~ repeating_command_block 0 keep {Command:"function abc:rails_c if @e[r=40]",auto:1b}


#fill ~-32 ~ ~ ~-32 ~ ~ repeating_command_block 0 keep {Command:"function abc:rails_e if @e[r=40]",auto:1b}
#fill ~32 ~ ~ ~32 ~ ~ repeating_command_block 0 keep {Command:"function abc:rails_e if @e[r=40]",auto:1b}
fill ~-32 ~ ~ ~-32 ~ ~ repeating_command_block 0 keep {Command:"function abc:rails_l if @e[r=40]",auto:1b}
fill ~32 ~ ~ ~32 ~ ~ repeating_command_block 0 keep {Command:"function abc:rails_l if @e[r=40]",auto:1b}


fill ~-64 ~ ~ ~-64 ~ ~ repeating_command_block 0 keep {Command:"function abc:test_lon if @e[r=40]",auto:1b}
fill ~64 ~ ~ ~64 ~ ~ repeating_command_block 0 keep {Command:"function abc:test_lon if @e[r=40]",auto:1b}

#fill ~ ~ ~ ~-1 ~ ~-1 concrete 1
fill ~1 ~1 ~1 ~-2 ~-1 ~-2 stained_glass 0 hollow
fill ~ ~ ~ ~-1 ~ ~-1 glowstone 1

#setblock ~ ~ ~ glowstone 0
#setblock ~ ~ ~ air 0

#fill ~ ~ ~ ~ ~ ~ repeating_command_block 0 keep {Command:"function abc:test2 if @e[r=40]",auto:1b}

#fill ~ 253 ~ ~ 253 ~ repeating_command_block 0 keep {Command:"function abc:do_roof_lon",auto:1b}
