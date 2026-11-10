# Architecture


# High level overview
There will be different tabs to show a different type of viewport.
Editor: The editor viewport, this will be a camera you control, and have objects you can click.
Game: The game viewport, this will show the current game view.
GUI: The gui viewport, this will show the gui system with different screens and menus you can edit.


# Features
- Every scene object can only have one script
- The scene object script has a built in functionality to get components under it.


Engine
    Editor
        Viewport
        SceneTree
        Content Browser
        Properties
    Subsystems
        GUISubsystem
    Core
        Scene
            SceneObject
        
        2D Renderer
        3D Renderer
        GUI system
    Tools
