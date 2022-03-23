fill ~ ~16 ~ ~ ~16 ~ repeating_command_block 0 keep {Command:"function abc:rails_k if @e[r=40]",auto:1b}

fill ~-16 ~ ~ ~-16 ~ ~ repeating_command_block 0 keep {Command:"function abc:rails_a if @e[r=40]",auto:1b}
fill ~16 ~ ~ ~16 ~ ~ repeating_command_block 0 keep {Command:"function abc:rails_c if @e[r=40]",auto:1b}

#fill ~ ~ ~-16 ~ ~ ~-16 repeating_command_block 0 keep {Command:"function abc:rails_b if @e[r=40]",auto:1b}
#fill ~ ~ ~16 ~ ~ ~16 repeating_command_block 0 keep {Command:"function abc:rails_d if @e[r=40]",auto:1b}

fill ~ ~16 ~-16 ~ ~16 ~-16 repeating_command_block 0 keep {Command:"function abc:rails_d if @e[r=40]",auto:1b}
fill ~ ~16 ~16 ~ ~16 ~16 repeating_command_block 0 keep {Command:"function abc:rails_b if @e[r=40]",auto:1b}

#fill ~ ~ ~16 ~ ~ ~16 repeating_command_block 0 keep {Command:"function abc:test_bedrock2",auto:1b}
#fill ~ ~ ~-16 ~ ~ ~-16 repeating_command_block 0 keep {Command:"function abc:test_bedrock2",auto:1b}

#fill ~-32 ~ ~ ~-32 ~ ~ repeating_command_block 0 keep {Command:"function abc:rails_e if @e[r=40]",auto:1b}
#fill ~32 ~ ~ ~32 ~ ~ repeating_command_block 0 keep {Command:"function abc:rails_e if @e[r=40]",auto:1b}
#fill ~ ~ ~-32 ~ ~ ~-32 repeating_command_block 0 keep {Command:"function abc:rails_f if @e[r=40]",auto:1b}
#fill ~ ~ ~32 ~ ~ ~32 repeating_command_block 0 keep {Command:"function abc:rails_f if @e[r=40]",auto:1b}

#fill ~-48 ~ ~ ~-48 ~ ~ repeating_command_block 0 keep {Command:"function abc:rails_e if @e[r=40]",auto:1b}
#fill ~48 ~ ~ ~48 ~ ~ repeating_command_block 0 keep {Command:"function abc:rails_e if @e[r=40]",auto:1b}
#fill ~ ~ ~-48 ~ ~ ~-48 repeating_command_block 0 keep {Command:"function abc:rails_f if @e[r=40]",auto:1b}
#fill ~ ~ ~48 ~ ~ ~48 repeating_command_block 0 keep {Command:"function abc:rails_f if @e[r=40]",auto:1b}


#fill ~-64 ~ ~ ~-64 ~ ~ repeating_command_block 0 keep {Command:"function abc:test_lon if @e[r=40]",auto:1b}
#fill ~64 ~ ~ ~64 ~ ~ repeating_command_block 0 keep {Command:"function abc:test_lon if @e[r=40]",auto:1b}
#fill ~ ~ ~-64 ~ ~ ~-64 repeating_command_block 0 keep {Command:"function abc:test_lat if @e[r=40]",auto:1b}
#fill ~ ~ ~64 ~ ~ ~64 repeating_command_block 0 keep {Command:"function abc:test_lat if @e[r=40]",auto:1b}

fill ~-64 ~ ~ ~-64 ~ ~ repeating_command_block 0 keep {Command:"function abc:test if @e[r=40]",auto:1b}
fill ~64 ~ ~ ~64 ~ ~ repeating_command_block 0 keep {Command:"function abc:test if @e[r=40]",auto:1b}
fill ~ ~ ~-64 ~ ~ ~-64 repeating_command_block 0 keep {Command:"function abc:test if @e[r=40]",auto:1b}
fill ~ ~ ~64 ~ ~ ~64 repeating_command_block 0 keep {Command:"function abc:test if @e[r=40]",auto:1b}


fill ~-32 ~16 ~ ~-32 ~16 ~ repeating_command_block 0 keep {Command:"function abc:test_lat if @e[r=40]",auto:1b}
fill ~32 ~16 ~ ~32 ~16 ~ repeating_command_block 0 keep {Command:"function abc:test_lat if @e[r=40]",auto:1b}
fill ~ ~16 ~-32 ~ ~16 ~-32 repeating_command_block 0 keep {Command:"function abc:test_lon if @e[r=40]",auto:1b}
fill ~ ~16 ~32 ~ ~16 ~32 repeating_command_block 0 keep {Command:"function abc:test_lon if @e[r=40]",auto:1b}


#shit
fill ~ ~32 ~ ~ ~32 ~ repeating_command_block 0 keep {Command:"function abc:test2 if @e[r=40]",auto:1b}
fill ~ ~-32 ~ ~ ~-32 ~ repeating_command_block 0 keep {Command:"function abc:test2 if @e[r=40]",auto:1b}

#fill ~ ~32 ~ ~ ~32 ~ repeating_command_block 0 keep {Command:"function abc:test2 if @e[r=40]",auto:1b}
#fill ~ ~-32 ~ ~ ~-32 ~ repeating_command_block 0 keep {Command:"function abc:test2 if @e[r=40]",auto:1b}

#setblock ~ ~ ~ air 0
#fill ~ ~ ~ ~ ~ ~ repeating_command_block 0 keep {Command:"function abc:test_bedrock2",auto:1b}

fill ~ ~-9 ~ ~ ~-9 ~ planks 0 replace air 0
fill ~ ~-9 ~ ~ ~-9 ~ air 0 replace bedrock 0
fill ~ ~-9 ~ ~ ~-9 ~ repeating_command_block 0 keep {Command:"function abc:test_bedrock_sub2",auto:1b}
fill ~ ~-9 ~ ~ ~-9 ~ air 0 replace planks 0

#function abc:test_bedrock2

function abc:fix
#fill ~80 ~-1 ~ ~80 ~-1 ~ repeating_command_block 0 keep {Command:"function abc:fix",auto:1b}
#fill ~-80 ~-1 ~ ~-80 ~-1 ~ repeating_command_block 0 keep {Command:"function abc:fix",auto:1b}
#fill ~ ~-1 ~80 ~ ~-1 ~80 repeating_command_block 0 keep {Command:"function abc:fix",auto:1b}
#fill ~ ~-1 ~-80 ~ ~-1 ~-80 repeating_command_block 0 keep {Command:"function abc:fix",auto:1b}
#fill ~ ~79 ~ ~ ~79 ~ repeating_command_block 0 keep {Command:"function abc:fix",auto:1b}
#fill ~ ~-81 ~ ~ ~-81 ~ repeating_command_block 0 keep {Command:"function abc:fix",auto:1b}

#fill ~96 ~1 ~ ~96 ~1 ~ stained_glass 10
#fill ~-96 ~1 ~ ~-96 ~1 ~ stained_glass 10
#fill ~ ~1 ~96 ~ ~1 ~96 stained_glass 10
#fill ~ ~1 ~-96 ~ ~1 ~-96 stained_glass 10
#fill ~ ~97 ~ ~ ~97 ~ stained_glass 10
#fill ~ ~-95 ~ ~ ~-95 ~ stained_glass 10

#fill ~ ~ ~ ~-1 ~ ~-1 concrete 1
fill ~1 ~1 ~1 ~-2 ~-1 ~-2 stained_glass 0 hollow
fill ~ ~ ~ ~-1 ~ ~-1 glowstone 1

#setblock ~ ~ ~ concrete 1
#setblock ~ ~ ~ glowstone 0
#setblock ~ ~ ~ air 0

#fill ~ ~ ~ ~ ~ ~ repeating_command_block 0 keep {Command:"function abc:test_lon if @e[r=40]",auto:1b}

#fill ~-48 ~ ~ ~-48 ~ ~ repeating_command_block 0 keep {Command:"function abc:rails_e if @e[r=40]",auto:1b}
#fill ~48 ~ ~ ~48 ~ ~ repeating_command_block 0 keep {Command:"function abc:rails_e if @e[r=40]",auto:1b}
#fill ~ ~ ~-48 ~ ~ ~-48 repeating_command_block 0 keep {Command:"function abc:rails_f if @e[r=40]",auto:1b}
#fill ~ ~ ~48 ~ ~ ~48 repeating_command_block 0 keep {Command:"function abc:rails_f if @e[r=40]",auto:1b}

fill ~ 253 ~ ~ 253 ~ repeating_command_block 0 keep {Command:"function abc:do_roof2",auto:1b}

