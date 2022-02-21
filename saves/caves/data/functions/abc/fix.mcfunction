
fill ~32 ~ ~ ~32 ~ ~ planks 0 replace air 0
fill ~-32 ~ ~ ~-32 ~ ~ planks 0 replace air 0
fill ~ ~ ~32 ~ ~ ~32 planks 0 replace air 0
fill ~ ~ ~-32 ~ ~ ~-32 planks 0 replace air 0
fill ~ ~32 ~ ~ ~32 ~ planks 0 replace air 0
fill ~ ~-32 ~ ~ ~-32 ~ planks 0 replace air 0

fill ~32 ~ ~ ~32 ~ ~ air 0 replace concrete 1
fill ~-32 ~ ~ ~-32 ~ ~ air 0 replace concrete 1
fill ~ ~ ~32 ~ ~ ~32 air 0 replace concrete 1
fill ~ ~ ~-32 ~ ~ ~-32 air 0 replace concrete 1
fill ~ ~32 ~ ~ ~32 ~ air 0 replace concrete 1
fill ~ ~-32 ~ ~ ~-32 ~ air 0 replace concrete 1

fill ~32 ~ ~ ~32 ~ ~ repeating_command_block 0 keep {Command:"function abc:fix2",auto:1b}
fill ~-32 ~ ~ ~-32 ~ ~ repeating_command_block 0 keep {Command:"function abc:fix2",auto:1b}
fill ~ ~ ~32 ~ ~ ~32 repeating_command_block 0 keep {Command:"function abc:fix2",auto:1b}
fill ~ ~ ~-32 ~ ~ ~-32 repeating_command_block 0 keep {Command:"function abc:fix2",auto:1b}
fill ~ ~32 ~ ~ ~32 ~ repeating_command_block 0 keep {Command:"function abc:fix2",auto:1b}
fill ~ ~-32 ~ ~ ~-32 ~ repeating_command_block 0 keep {Command:"function abc:fix2",auto:1b}

fill ~32 ~ ~ ~32 ~ ~ air 0 replace planks 0
fill ~-32 ~ ~ ~-32 ~ ~ air 0 replace planks 0
fill ~ ~ ~32 ~ ~ ~32 air 0 replace planks 0
fill ~ ~ ~-32 ~ ~ ~-32 air 0 replace planks 0
fill ~ ~32 ~ ~ ~32 ~ air 0 replace planks 0
fill ~ ~-32 ~ ~ ~-32 ~ air 0 replace planks 0

setblock ~ ~ ~ air 0
