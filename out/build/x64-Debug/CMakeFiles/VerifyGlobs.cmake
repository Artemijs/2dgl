# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.22
cmake_policy(SET CMP0009 NEW)

# SRC at CMakeLists.txt:14 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/Other/*.cpp")
set(OLD_GLOB
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/Other/Projects/2D/TileMapMaterial.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/Other/Projects/2D/TopDownEditor.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/Other/Projects/3D/3DCollision/CollisionTest3D.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/Other/Projects/3D/MeshTest/MeshTest.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/Other/Projects/3D/RayCastingTest/RayCastTest.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/Other/Projects/CollisionTest/ColliisonTestGame.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/Other/Projects/CollisionTest/CollisionTesMain.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/Other/Projects/RenderNodeTest/RenderNodeTest.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/Other/Projects/ShaderTests/ShaterTest.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/Other/Projects/TowerDefense/TowerDefenseGame.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/Other/Projects/UI/BasePanelTest/BasePanelTest.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/out/build/x64-Debug/CMakeFiles/cmake.verify_globs")
endif()

# SRC at CMakeLists.txt:14 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/*.cpp")
set(OLD_GLOB
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Audio/SoundController.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/BackEnd/EBO.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/BackEnd/FBO.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/BackEnd/FinalRect.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/BackEnd/VAO.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/BackEnd/VBO.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/BackEnd/stb.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Game/BaseComponent.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Game/BaseNode.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Game/FBOComponent.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Game/Game.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Game/Mesh/Mesh.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Game/Mesh/MeshLoader.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Game/Mesh/Model.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Game/MouseEventComponent.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Game/RenderNode.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Graphics/Camera.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Graphics/Graphic.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Graphics/Materials/DiffuseMaterial.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Graphics/Materials/Material.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Graphics/Materials/MaterialSprite.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Graphics/Materials/MaterialUiButton.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Graphics/Materials/MaterialUiSprite.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Graphics/Materials/MaterialUiText.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Graphics/Renderer.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Graphics/ShaderClass.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Graphics/Sprite.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Graphics/Texture.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Input/Keyboard.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Input/Mouse.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Input/MouseEventHandler.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Math/AABoxBounds.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Math/Bounds.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Math/BoxBounds.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Math/CollisionDetection.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Math/CollisionHandler.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Math/Matrix4x4.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Math/PhysicsObject.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Math/PhysicsWorld.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Math/SphereBounds.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/UI/BasePanel.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/UI/Button.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/UI/Text.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/UI/UIHandler.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Util/Callback.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Util/DataStructures.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Util/MemoryManager.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Util/PseudoCode.cpp"
  "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/src/Util/Utility.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "C:/Users/artem/Documents/_programming/CMakeProjects/2dgl/out/build/x64-Debug/CMakeFiles/cmake.verify_globs")
endif()
