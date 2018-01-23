
public class Percolation {
    
    private int[][] grid;
    private WeightedQuickUnionUF wquf;
    private int datnum;
    
    private int virtualTop;
    private int virtualBot;
    
    //
    // Turn 2d coordinates into 1d space for uf
    //
    private int reverseinception(int x, int y) {
        
        return datnum * x + y;
        
    }
    
    //
    // Check out of bounds
    //
    private boolean isOutOfBounds(int x, int y) {
        
        if ( (x + 1) > datnum || (y + 1) > datnum
            || x < 0 || y < 0) {
            
            return true;
            
        }
        
        return false;
        
    }

    public int[][] getGrid() {

        return grid;

    }
    
    //
    // Constructor to create closed n x n grid
    //
    
    public Percolation(int n) {
        
        datnum = n;
        grid = new int[n][n];
        
        wquf = new WeightedQuickUnionUF(n*n + 2);

        virtualTop = n*n + 2;
        virtualBot = n*n + 1;
        
    }
    
    //
    // Opens the selected location on the grid
    //
    
    public void open(int x, int y) {
        
        if ( isOutOfBounds(x, y) ) {
            
            // do error
            
        } else {
            

            grid[x][y] = 1;

            // add to openTops if top!

            if (x == datnum - 1) {

                wquf.union(reverseinception(x, y), virtualTop - 1);

            }

             // add to openBots if top!

            if (x == 0) {

                wquf.union(reverseinception(x, y), virtualBot - 1);

            }

            
            // check surrounding nodes to connect using weighted uf
            // 4 cases: each side, NOTE the edges!!
            
            // case: check up
            if ( (y + 1) < datnum && isOpen(x, y + 1) ) {

                wquf.union(reverseinception(x, y), reverseinception(x, y+1));
                
            }
            
            

            // case: check down
            if ( (y - 1) >= 0 && isOpen(x, y - 1) ) {

                wquf.union(reverseinception(x, y), reverseinception(x, y-1));
                
            }
            
            // case: check left
            if ( (x - 1) >= 0 && isOpen(x - 1, y) ) {
                
                wquf.union(reverseinception(x, y), reverseinception(x-1, y));
                
            }
            
            // case: check right
            if ( (x + 1) < datnum && isOpen(x + 1, y) ) {
                
                wquf.union(reverseinception(x, y), reverseinception(x+1, y));
                
            }
            
        }
        
    }
    
    //
    //  Returns true when the location on the grid is open
    //
    
    public boolean isOpen(int x, int y) {
        
        if ( isOutOfBounds(x, y) ) {
            
             // do error
            
            return false;
            
        } else {
            
            return grid[x][y] == 1;
            
        }
        
    }
    
    //
    //  Returns true if the location on grid percolates to top
    //
    
    public boolean isFull(int x, int y) {
        
        if ( isOutOfBounds(x, y) ) {
            
            // do error
            
        } else {
            
            // loop through to check all top nodes of grid
            for (int i = 0; i < datnum; i++) {
                
                if ( wquf.connected(datnum * datnum - 1 - i, reverseinception(x, y)) ) {
                    
                    //System.out.println(wquf.count() + "   " + reverseinception(x,y));
                    
                    return true;
                    
                }
                
            }
            
        }
        
        return false;
        
    }

    public void fill(int x, int y) {

        grid[x][y] = 2;

    }
    
    //
    //  Returns true if the there is connection bottom to top
    //
    
    public boolean percolates() {
        
        return wquf.connected(virtualTop - 1, virtualBot - 1);
        
    }
    
    public static void main(String args[]) {
        
        boolean firstRead = true;
        Percolation perc = new Percolation(0); // avoid that error, boi
        
        while (!StdIn.isEmpty()) {
        
            if (firstRead) {
                
                perc = new Percolation(StdIn.readInt());
                
                firstRead = false;
                
            } else {
                
                int _x = StdIn.readInt();
                int _y = StdIn.readInt();
                                
                perc.open(_x,_y);
                
            }
            
        }
        
        if (perc.percolates()) {
            
            System.out.println("Yes");
            
        } else {
            
            System.out.println("No");
            
        }
        
    }
    

}
