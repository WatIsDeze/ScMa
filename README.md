# ScMa (SchizoMania).
SchizoMania game, using Tesseract engine.

Although it is using Tesseract as a base, it does not refrain from heavily modifying parts that need a change.
Feel free to join in on this project, which is best done for now by just hacking away at one of the things found in the todo list located in CHANGES.md

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
