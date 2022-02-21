setblock ~ ~ ~ xplosives:physics_bomb 0 replace


#
##setblock ~ ~ ~ fireworks 0 replace repeating_command_block
##setblock ~ ~-1 ~ glass 0 replace concrete
##fill ~-1 ~ ~-1 ~1 ~2 ~1 stained_glass 6 hollow
#
#fill ~-3 ~ ~-3 ~3 ~ ~3 stained_glass 14 hollow
#fill ~-3 ~1 ~-3 ~3 ~1 ~3 stained_glass 4 hollow
#fill ~-3 ~2 ~-3 ~3 ~2 ~3 stained_glass 5 keep
#
#setblock ~-2 ~2 ~-2 lit_pumpkin 0 replace
#setblock ~2 ~1 ~-2 lit_pumpkin 0 replace
#setblock ~-2 ~ ~2 lit_pumpkin 0 replace
#
#setblock ~ ~ ~ xplosives:physics_bomb 0 replace
##fill ~-1 ~ ~-1 ~1 ~ ~1 glass 0 replace concrete
##setblock ~ ~1 ~ planks 0 replace
##setblock ~ ~1 ~ air 0 replace
##setblock ~ ~1 ~ gold_block 0 replace
#summon minecraft:slime ~ ~1 ~
#summon minecraft:parrot ~5 ~15 ~5
#summon minecraft:parrot ~-5 ~15 ~5
#summon minecraft:parrot ~-5 ~15 ~-5
#summon minecraft:parrot ~5 ~15 ~-5
##fill ~-5 ~-5 ~-5 ~5 ~5 ~5 glowstone 0 replace stone 0
#
##fill ~-5 ~-5 ~-5 ~5 ~5 ~5 exxabite:physics_bomb 0 replace glowstone 0
#
playsound minecraft:ambient.cave ambient Pacman_Graphics

#fill ~-1 ~ ~ ~1 ~1 ~ planks 0 replace air 0
#fill ~-1 ~ ~ ~1 ~1 ~ air 0 replace glowstone 0
#fill ~-1 ~ ~ ~1 ~1 ~ repeating_command_block 0 keep {Command:"/function exxabite:place_physics_bomb",auto:1b}
#fill ~-1 ~ ~ ~1 ~1 ~ air 0 replace planks 0
