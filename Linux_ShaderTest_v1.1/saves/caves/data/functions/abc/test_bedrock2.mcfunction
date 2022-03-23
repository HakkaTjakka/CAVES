#setblock ~ ~ ~ air 0
#setblock ~ ~ ~ glowstone 0
fill ~ ~-6 ~ ~ ~-6 ~ planks 0 replace air 0
fill ~ ~-6 ~ ~ ~-6 ~ air 0 replace bedrock 0
fill ~ ~-6 ~ ~ ~-6 ~ repeating_command_block 0 keep {Command:"function abc:test_bedrock_sub2",auto:1b}
fill ~ ~-6 ~ ~ ~-6 ~ air 0 replace planks 0
