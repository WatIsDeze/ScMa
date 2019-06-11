# Plan for entities:
	- Use newgent for adding them. First argument is the entity type.
	- Ensure entity types are merely mentioned by TYPE name.
	- Create a few base interfaces (not fully interface classes, but we'll call them interfaces.)
		- BaseEntity
		- MovableEntity
		- ControllableEntity
		- ??
	- Use CubeScript for them to enable scripting (For example, change a mesh, or trigger another entity by TRIGGER_NAME)
	
