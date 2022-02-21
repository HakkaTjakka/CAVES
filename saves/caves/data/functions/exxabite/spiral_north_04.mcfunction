setblock ~ ~ ~ air 0 replace
fill ~ ~ ~ ~ ~ ~ repeating_command_block 0 replace {Command:"function exxabite:spiral_tnt",auto:1b}
setblock ~ ~-1 ~ glowstone 0 keep
setblock ~ ~-2 ~ stained_glass 4 keep
fill ~1 ~-3 ~-2 ~1 ~-3 ~-2 repeating_command_block 0 replace {Command:"function exxabite:spiral_north_05",auto:1b}

setblock ~6 ~2 ~-3 tnt 0 replace
setblock ~6 ~1 ~-3 glowstone 0 keep
setblock ~6 ~ ~-3 stained_glass 4 keep

setblock ~12 ~4 ~-6 tnt 0 replace
setblock ~12 ~3 ~-6 glowstone 0 keep
setblock ~12 ~2 ~-6 stained_glass 4 keep

setblock ~-6 ~-2 ~3 tnt 0 replace
setblock ~-6 ~-3 ~3 glowstone 0 keep
setblock ~-6 ~-4 ~3 stained_glass 4 keep
