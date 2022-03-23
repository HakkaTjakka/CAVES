setblock ~ ~ ~ tnt 0 replace repeating_command_block
#setblock ~ ~ ~ xplosives:physics_bomb 0 replace repeating_command_block
fill ~-1 ~ ~ ~1 ~-1 ~ repeating_command_block 0 keep {Command:"/function exxabite:stripe_xy",auto:1b}

fill ~-2 ~-2 ~ ~2 ~2 ~ planks 0 replace air 0
fill ~ ~-2 ~-2 ~ ~2 ~2 planks 0 replace air 0
fill ~-2 ~ ~-2 ~2 ~ ~2 planks 0 replace air 0
fill ~-2 ~-2 ~ ~2 ~2 ~ air 0 replace glowstone 0
fill ~ ~-2 ~-2 ~ ~2 ~2 air 0 replace glowstone 0
fill ~-2 ~ ~-2 ~2 ~ ~2 air 0 replace glowstone 0
#fill ~-2 ~-2 ~ ~2 ~2 ~ air 0 replace lit_pumpkin 0
#fill ~ ~-2 ~-2 ~ ~2 ~2 air 0 replace lit_pumpkin 0
#fill ~-2 ~ ~-2 ~2 ~ ~2 air 0 replace lit_pumpkin 0
fill ~-2 ~-2 ~ ~2 ~2 ~ repeating_command_block 0 keep {Command:"/function exxabite:place_physics_bomb",auto:1b}
fill ~ ~-2 ~-2 ~ ~2 ~2 repeating_command_block 0 keep {Command:"/function exxabite:place_physics_bomb",auto:1b}
fill ~-2 ~ ~-2 ~2 ~ ~2 repeating_command_block 0 keep {Command:"/function exxabite:place_physics_bomb",auto:1b}
fill ~-2 ~-2 ~ ~2 ~2 ~ air 0 replace planks 0
fill ~ ~-2 ~-2 ~ ~2 ~2 air 0 replace planks 0
fill ~-2 ~ ~-2 ~2 ~ ~2 air 0 replace planks 0
