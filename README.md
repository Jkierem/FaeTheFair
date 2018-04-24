# Proyecto de Introducción a Computación Grafica
### Por Juan Miguel Gomez y Daniela Colmenares

- Para compilar se adjuntó archivo "compile" con la linea de compilación usada por si desea usarla.

## To Do's:
- [X] Implement Vector3D
- [X] Implement masking Functions in Juan Namespace
- [X] Implement basic FaeTheFair
- [X] Draw Cylinder given two points in space
- [X] Draw Cone given two points in space
- [X] Draw basic stage
- [X] Draw body
- [X] Get Point from Fae given Tag
- [X] Rework Folder Structure
- [X] Read Positions from input file
- [X] Fix (0,0,0) Positions in input file
- [X] Implement rotating octahedron
- [X] Adjust perspective to be able to fit entire figure
- [X] Adjust Camera to show figure correctly
- [ ] Adjust Body and Legs scale
- [X] Implement User interaction
- [X] Remove global variables from main.cpp
- [ ] Implement union with OpenCSG to use in segments
- [ ] Implement right click menu.
- [ ] Fix Cylinder function.
- [X] Add configurations
- [ ] Draw Stage (properly)
- [ ] Draw Body (properly)

## User Interaction:

   As of now the control of the program is limited to:
-  **Space Bar**: start, stop and resume the sim.
-  **R Key**: restart sim.
-  **L Key**: load a sim file using zenity.
-  **W,S Keys**: rotation on X axis.
-  **A,D Keys**: rotation on Y axis.
-  **Q,E Keys**: rotation on Z axis.
-  **Arrow keys**: panning on XY plane.
-  **- Key**: panning to positive Z plane.
-  **. Key**: panning to negative Z plane.
-  **T Key**: reset rotation to default rotation.
-  **Y Key**: reset panning to default panning.
-  **O key**: save current rotation as default rotation.
-  **P Key**: save current panning as default panning.
-  **K Key**: toggle simulation loop.
-  **F Key**: cycle frame rates. They are 15, 30 and 60 fps. The default is 30 fps.
-  **ESC Key**: exit program.
