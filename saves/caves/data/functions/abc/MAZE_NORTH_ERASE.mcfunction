setblock ~-6 ~8 ~8 air 0
fill ~-6 ~8 ~8 ~-6 ~8 ~8 repeating_command_block 0 keep {Command:"function abc:letter_ONE_REMOVE",auto:1b}
particle explode ~-6 ~8 ~8 16 16 16 0.1 5000
kill @e[type=Bat,r=8]
