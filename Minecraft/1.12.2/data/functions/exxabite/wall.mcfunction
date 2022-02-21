fill ~-1 ~-1 ~-1 ~1 ~1 ~1 planks 0 replace air 0
fill ~-1 ~-1 ~-1 ~1 ~1 ~1 air 0 replace stone 0
#fill ~-1 ~-1 ~-1 ~1 ~1 ~1 air 0 replace stone 1
#fill ~-1 ~-1 ~-1 ~1 ~1 ~1 air 0 replace stone 3
#fill ~-1 ~-1 ~-1 ~1 ~1 ~1 air 0 replace gravel 0
#fill ~-1 ~-1 ~-1 ~1 ~1 ~1 air 0 replace stone 5

fill ~-1 ~-1 ~-1 ~1 ~1 ~1 air 0 replace stained_glass 4
fill ~-1 ~-1 ~-1 ~1 ~1 ~1 air 0 replace stained_glass 5
fill ~-1 ~-1 ~-1 ~1 ~1 ~1 air 0 replace stained_glass 14
fill ~-1 ~-1 ~-1 ~1 ~1 ~1 air 0 replace stained_glass 15
fill ~-1 ~-1 ~-1 ~1 ~1 ~1 air 0 replace lit_pumpkin 0


fill ~-1 ~-1 ~-1 ~1 ~1 ~1 repeating_command_block 0 keep {Command:"/function exxabite:wall2",auto:1b}

fill ~-1 ~-1 ~-1 ~1 ~ ~1 air 0 replace dirt 0
fill ~-1 ~-1 ~-1 ~1 ~ ~1 repeating_command_block 0 keep {Command:"/function exxabite:wall3",auto:1b}

#fill ~-1 ~-1 ~-1 ~1 ~1 ~1 air 0 replace quartz_block 0

#fill ~-1 ~-1 ~-1 ~1 ~1 ~1 air 0 replace stone 0
fill ~-1 ~-1 ~-1 ~1 ~1 ~1 air 0 replace bedrock 0
fill ~-1 ~-1 ~-1 ~1 ~1 ~1 repeating_command_block 0 keep {Command:"/function exxabite:melt_bedrockair",auto:1b}

fill ~-1 ~-1 ~-1 ~1 ~1 ~1 air 0 replace planks 0

#fill ~-1 ~-1 ~-1 ~1 ~1 ~1 air 0 replace bedrock 0

fill ~-1 ~ ~ ~-1 ~ ~ air 0 replace glowstone
fill ~ ~1 ~ ~ ~1 ~ air 0 replace glowstone
fill ~ ~ ~-1 ~ ~ ~-1 air 0 replace glowstone

#setblock ~ ~ ~ quartz_block 0 replace repeating_command_block

setblock ~ ~ ~ air 0 replace repeating_command_block
#fill ~ ~ ~ ~ ~ ~ repeating_command_block 0 keep {Command:"/function exxabite:hold1",auto:1b}

#setblock ~ ~ ~ air 0 replace repeating_command_block

#setblock ~ ~ ~ glass 0 replace repeating_command_block
#fill ~-1 ~-1 ~-1 ~1 ~1 ~1 air 0 replace quartz_block 0
fill ~-1 ~-1 ~-1 ~1 ~1 ~1 air 0 replace bedrock 0
fill ~-1 ~-1 ~-1 ~1 ~1 ~1 glass 0 replace stone 1
fill ~-1 ~-1 ~-1 ~1 ~1 ~1 gold_block 0 replace stone 3
fill ~-1 ~-1 ~-1 ~1 ~1 ~1 glass 0 replace gravel 0
fill ~-1 ~-1 ~-1 ~1 ~1 ~1 glass 0 replace stone 5
fill ~-1 ~-1 ~-1 ~1 ~1 ~1 glass 0 replace dirt 0

#fill ~-1 ~ ~ ~-1 ~ ~ air 0 replace glowstone
#fill ~ ~1 ~ ~ ~1 ~ air 0 replace glowstone
#fill ~ ~ ~-1 ~ ~ ~-1 air 0 replace glowstone
#
#setblock ~ ~ ~ air 0 replace repeating_command_block
#	