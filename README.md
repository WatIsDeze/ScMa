# ScMa (SchizoMania).
SchizoMania game, using Tesseract engine.

Although it is using Tesseract as a base, it does not refrain from heavily modifying parts that need a change.
Feel free to join in on this project, which is best done for now by just hacking away at one of the things in the todo lists below.

# TODO ENGINE Alpha 0.0.1:
- Add support for footstep audio based on material/texture type.
- Add support for flickering light entities.
- Add doors. (This is done by movable to my understanding, the code is partially there, it seems that the missing link is the mapmodel command not accepting integers anymore.)
- Allow for 64 bots, maybe even more, so we can use these for AI. Otherwise, reimplement AI like in Cube 2, and work from there.

# TODO GAME Alpha 0.0.1:
- Allow for string enitity attributes to be set and edited. (Take note, this may have to be done in Engine code sadly.)
- Create a basic test map.
- Allow for the possibility of reloading a weapon.
- Add a knife melee weapon.
- Add a pellet gun single shot rifle.
- Add a pellet gun machinegun.
- Create a basic inventory for weapon switching and item management.
- Create a basic dialogue entity.

# Useful Map Editing commands:
- Must DO:
	Always turn outlines on, this allows us to see how many cubes/vertices there are being rendered. We definitely want to avoid using smaller cubes for geometry such as a platform. FPS is gained big time. (More info can be found here: https://www.youtube.com/watch?v=clWyKy5eRnQ)

- Keys:
	Hold F and scroll in order to resize a cube, this is useful when you use a larger grid size. It allows for higher FPS due to less cubes having to be rendered.

- Water
	/water
	/water2
	/air (deletes water)
	watercolour  0 0 0 (default)
	water2colour (for water2)
	waterfog=  for water transparency. default is waterfog=30

- VColor and VAlpha.
	/vcolor r g b
	/valpha v
	/texalpha v
