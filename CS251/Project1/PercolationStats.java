
public class PercolationStats {

	public PercolationStats () {

		// todo?

	}

    public static void main(String args[]) {
        
        int gridSize = Integer.parseInt(args[0]);
        int simulations = Integer.parseInt(args[1]);
        String unionType = args[2];

        double[] pTable = new double[simulations];
        double[] tTable = new double[simulations];
        double startTime;

        for (int i = 0; i < simulations; i++) {

            if (unionType.equals("fast")) {
                
                Percolation perc = new Percolation(gridSize);
            
            int openCount = 0;

                startTime = (double)System.currentTimeMillis();
                
            while (!perc.percolates()) {

                int x = StdRandom.uniform(gridSize);
                int y = StdRandom.uniform(gridSize);

                if (!perc.isOpen(x, y))  {

                    perc.open(x, y);
                    openCount++;

                }

            }

                pTable[i] = (1.00 * openCount / (1.00 * gridSize * 1.00 * gridSize));
                
                double timeToAdd = ((double)System.currentTimeMillis() - startTime) / 1000.0;
                
                tTable[i] = timeToAdd;
                
            } else if (unionType.equals("slow")) {
                
                PercolationQuick perc = new PercolationQuick(gridSize);
                
                int openCount = 0;
                
                startTime = (double)System.currentTimeMillis();
                
                while (!perc.percolates()) {
                    
                    int x = StdRandom.uniform(gridSize);
                    int y = StdRandom.uniform(gridSize);
                    
                    if (!perc.isOpen(x, y))  {
                        
                        perc.open(x, y);
                        openCount++;
                        
                    }
                    
                }
                
                pTable[i] = (1.00 * openCount / (1.00 * gridSize * 1.00 * gridSize));
                
                double timeToAdd = ((double)System.currentTimeMillis() - startTime) / 1000.0;
                
                tTable[i] = timeToAdd;
                
            }

        }

        // PRINTING BELOW
        
        System.out.println("mean threshold=" + StdStats.mean(pTable));
        System.out.println("std dev=" + StdStats.stddev(pTable));
        
        double totalTime = 0;
        for (int i = 0; i < simulations; i++) {
            
            totalTime += tTable[i];
            
        }
        
        System.out.println("time=" + Double.toString(totalTime));
        
        System.out.println("mean time=" + StdStats.mean(tTable));
        System.out.println("stddev time=" + StdStats.stddev(tTable));

    }

}
