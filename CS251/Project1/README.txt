
NAME: 		Nicholas Donahue
ID:			0026707669
PROJECT:	#1 - Percolation


Included Files:

-<all default/given files>
-Percolation.java					-		Percolation with WeightedQuickUnionUF
-PercolationQuick.java				-		Percolation with QuickUnionFindUF
-PercolationVisualization.java		-		Percolation Visualizer
-PercolationStats.java				-		Statistical Analysis Tool for Percolation


Compilation & Execution:

  ---> I used the default compilation and execution commands provided by the instructors


javac ­classpath .:stdlib.jar WeightedQuickUnionUF.java

javac ­classpath .:stdlib.jar QuickUnionUF.java

javac ­classpath .:stdlib.jar Percolation.java

javac ­classpath .:stdlib.jar PercolationQuick.java

javac ­classpath .:stdlib.jar PercolationVisualizer.java

javac ­classpath .:stdlib.jar PercolationStats.java

javac ­classpath .:stdlib.jar VisualizeFrames.java

java ­classpath .:stdlib.jar Percolation < testCase.txt

java ­classpath .:stdlib.jar PercolationVisualizer < testCase.txt

java ­classpath .:stdlib.jar PercolationStats <gridSize> <numTrials> <fast/slow>



Errors and Special Cases:

For this project there was no explicit declartion for error handeling invalid inputs so I did not
carefully check the inputs. I did however perform out of bounds checks and created a helper function
to check the boundaries of the input coordinates via the testCase.txt files. For out of bounds 
coordinates it should simply ignore it. For more fatal errors (not providing arguments, for example)
the program is not built to handle and may not perform as desired. This program is intended to function 
under optimal conditions with no invalid inputs. 