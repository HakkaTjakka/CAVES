setblock ~ ~ ~ air 0 replace
fill ~ ~ ~ ~ ~ ~ repeating_command_block 0 replace {Command:"function exxabite:spiral_tnt",auto:1b}
setblock ~ ~-1 ~ glowstone 0 keep
setblock ~ ~-2 ~ stained_glass 0 keep
fill ~1 ~-2 ~3 ~1 ~-2 ~3 repeating_command_block 0 replace {Command:"function exxabite:spiral_large_01",auto:1b}

setblock ~6 ~-3 ~-2 tnt 0 replace
setblock ~6 ~-4 ~-2 glowstone 0 keep
setblock ~6 ~-5 ~-2 stained_glass 0 keep

setblock ~-6 ~3 ~2 tnt 0 replace
setblock ~-6 ~2 ~2 glowstone 0 keep
setblock ~-6 ~1 ~2 stained_glass 0 keep

setblock ~12 ~-6 ~-4 tnt 0 replace
setblock ~12 ~-7 ~-4 glowstone 0 keep
setblock ~12 ~-8 ~-4 stained_glass 0 keep

#setblock ~-6 ~3 ~2 tnt 0 replace
#setblock ~-6 ~4 ~2 glowstone 0 keep
#setblock ~-6 ~5 ~2 stained_glass 0 keep
