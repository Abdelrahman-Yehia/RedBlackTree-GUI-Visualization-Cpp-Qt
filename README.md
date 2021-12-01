# RedBlackTree-GUI-Visualization-Cpp-Qt
This is a GUI visualization Red Black Tree data structure using c++ and Qt.
This Project was designed and implemented by:
Abdelrahman Yehia (github.com/abdelrahman-yehia)  
Mahmoud Atia	  (github.com/Mahmoud-Atia)  

# RBT Implementation
The Red Black Tree class in the file RedBlackTree.h was implemented by Mahmoud Atia

# GUI Visualization
In this project I've took a very naive approach to draw the nodes of the RBT.  
I only use lines, circles, and numbers to draw tree, by calling a recursive function starts by drawing the root at the initial coordinates, and a line point to the parent of the current node.

# Static Width issue
The approach I am taking causes an issue where sometimes two nodes are drawn on top of each other beacuse the width of the tree doesn't change dynamiclly when the number of nodes increases.  
I believe this problem can be solved by trying to calculate the width of each level depending on the total number of nodes. I haven't got a chance to code this solution yet, but it'll be fixed soon INSHALLAH.
