
public class PercolationVisualization {

	private Out fileOut;
    
	private void writeToOut(String str) {

		System.out.println(str);
		fileOut.println(str);

	}

	private void writeToOutNoLn(String str) {

		System.out.print(str);
		fileOut.print(str);

	}

	private void writeMatrixOut(int[][] mat) {

		for (int i = mat.length - 1; i >= 0; i--) {

			for (int j = 0; j < mat.length; j++) {

				if (j == mat.length - 1) {

					writeToOutNoLn(mat[i][j] + "");

				} else {

					writeToOutNoLn(mat[i][j] + " ");

				}

			}

			writeToOut("");

		}

		writeToOut("");
	}

	public PercolationVisualization () {

		fileOut = new Out("visualMatrix.txt");

	}

    public static void main(String args[]) {
        
        boolean firstRead = true;
        Percolation perc = new Percolation(0); // avoid that error, boi
        PercolationVisualization pv = new PercolationVisualization();
        
        while (!StdIn.isEmpty()) {
        
            if (firstRead) {

            	int tempSize = StdIn.readInt();
                
                perc = new Percolation(tempSize);
                
                firstRead = false;

                pv.writeToOut(("" + tempSize + "\n"));
                
            } else {
                
                int _x = StdIn.readInt();
                int _y = StdIn.readInt();
                                
                perc.open(_x,_y);

                if (!StdIn.isEmpty()) {

                	pv.writeMatrixOut(perc.getGrid());

                }
                
            }
            
        }
        
        if (perc.percolates()) {
            
            for (int i = 0; i < perc.getGrid().length; i++) {

            	for (int j = 0; j < perc.getGrid().length; j++) {

            		if (perc.isFull(i, j) && perc.isOpen(i, j)) {

            			perc.fill(i, j);

            		}

            	}

            }

            pv.writeMatrixOut(perc.getGrid());

            
        } else {
            
            //System.out.println("No");
            
            // get top row, yo
            
            for (int k = 0; k < perc.getGrid().length; k++) {
                
                if (perc.isOpen(perc.getGrid().length - 1, k)) {
                    
                    perc.fill(perc.getGrid().length - 1, k);
                    
                }
                
            }
            
            // do the rest
            
            for (int i = 0; i < perc.getGrid().length; i++) {
     
                for (int j = 0; j < perc.getGrid().length; j++) {
                    
                    if (perc.isFull(i, j) && perc.isOpen(i, j)) {
                        
                        perc.fill(i, j);
                        
                    }
                }
                
            }
         
            pv.writeMatrixOut(perc.getGrid());

        }

        //fileOut.close();
        
    }
    

}
