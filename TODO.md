# cyberpunk_nes

## General

- [x] Get Hello World to work
- [x] Get the glyphs to show
- [ ] Get a sprite to render
    - [x] Add OAMADDR and OAMDATA register macros
    - [x] Add write_sprite helper
    - [x] Convert Hexany PNG tileset to CHR
    - [x] Reorganize assets into raw/build CHR directories
    - [x] Update chr.s to include CHR assets
    - [x] Add/load sprite palettes at $3F10-$3F1F
    - [ ] Clear OAM before placing sprites
    - [ ] Write one test sprite into OAM
    - [ ] Enable sprite rendering with PPUMASK
    - [ ] Verify sprite appears in Mesen/FCEUX
- [ ] Get sprite to move
- [ ] Write a control class

## Gameplay

- [ ] Write level logic
- [ ] Write a HUD
- [ ] Write a Start Menu

## Art

- [ ] Draw a scene

## Cleanup


## Tooling

- [x] Add C++ syntax highlighting
- [x] Finish Makefile
- [x] Finish progress script
- [x] Improve testing pipeline, at least make the scp go to local
- [x] Versioning feature in Makefile
