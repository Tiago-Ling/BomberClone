# BomberClone
A simplified Dyna Bomber / Bomberman clone created with UE4 for a programming test.

Test should not take more than 15 hours, so i stopped working as soon as i hit that mark. Unfortunately this left the game unfinished.

Features
========

[x] Static top-down view
[x] One pre-defined map
[x] Two players play on the same machine using the keyboard, no gamepad
[x] Distinguishable characters (different materials)
[x] Procedural generated maps (kinda, just random block placement currently)
[ ] Pickups (longer blasts, more bombs, faster run speed, remote-controlled bombs)
[x] Linear bomb blasts in four main directions
[ ] Player death when standing in bomb blast
[-] Differentiation between destructible and indestructible walls (WIP)
[-] Bomb blasts are stopped by indestructible walls (WIP)
[ ] Bombs trigger other bombs
[ ] Random pickup chance when destroying walls
[-] UI, Win conditions and reset options on end screen (WIP)

Third-party stuff
=================

*  Unreal Mannequin, including skeletal mesh, animations, animation blueprint and textures
*  Unreal starter content such as particle systems (including bps, although not used), meshes, materials and sounds (not used)

Notes (mostly stuff that wasted precious time)
==============================================

*  Two players on the same keyboard wasted ~3 hours as i never had to do that before
*  Game crashing due to trying to load animation blueprint in the same way as regular assets took ~3 hours to fix

Next steps (in order of implementation)
=======================================
*  Fix overlapping of bomb trails to not propagate beyond indestructible walls
*  Finish UI w/ blueprints (Menus, Hud) and complete game cycle (win, draw, reset, etc)
*  Implement pickups
*  Character: fix facing, edit animation blueprint to include death and bomb placement (crouch).
*  Better level generation