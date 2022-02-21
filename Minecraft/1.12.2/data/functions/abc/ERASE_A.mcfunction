setblock ~0 ~2 ~0 air 0
fill ~0 ~2 ~0 ~0 ~2 ~0 repeating_command_block 0 keep {Command:"function abc:letter_ONE_REMOVE",auto:1b}
particle explode ~0 ~2 ~0 16 16 16 0.1 5000
kill @e[type=Bat,r=8]
fill ~-5 ~-18 ~-5 ~-5 ~-18 ~-5 concrete 15 replace command_block
fill ~-6 ~14 ~-6 ~-6 ~14 ~-6 concrete 15 replace command_block
fill ~-3 ~-2 ~-21 ~-3 ~-2 ~-21 concrete 15 replace command_block
fill ~-4 ~-2 ~10 ~-4 ~-2 ~10 concrete 15 replace command_block
fill ~15 ~-2 ~-5 ~15 ~-2 ~-5 concrete 15 replace command_block
fill ~-18 ~-2 ~-6 ~-18 ~-2 ~-6 concrete 15 replace command_block
fill ~2 ~-18 ~-5 ~2 ~-18 ~-5 concrete 15 replace command_block
fill ~1 ~14 ~-6 ~1 ~14 ~-6 concrete 15 replace command_block
fill ~4 ~-2 ~-21 ~4 ~-2 ~-21 concrete 15 replace command_block
fill ~3 ~-2 ~10 ~3 ~-2 ~10 concrete 15 replace command_block
fill ~22 ~-2 ~-5 ~22 ~-2 ~-5 concrete 15 replace command_block
fill ~-11 ~-2 ~-6 ~-11 ~-2 ~-6 concrete 15 replace command_block
