import java.util.Arrays;

public class Brute {

	public Brute() {
		
	}

    public static void myBubbSort(Point array[]) {

        int n = array.length;

	    for (int i = 0; i < n; i++) {

	        for (int j = 1; j < (n - i); j++) {

	            if (array[j-1].compareTo(array[j]) == 1) {

	                Point temp = array[j - 1];
	                array[j - 1] = array[j];
	                array[j] = temp;

	            }

	        }
	    }
    }

    public static void main(String args[]) {

    	// Creat point object for referencing.
    	Point _pref = new Point(420, 420);
        
        int numPoints = StdIn.readInt();
        Point[] pointArray = new Point[numPoints];
        int i = 0;
        
        while (!StdIn.isEmpty()) {
        
			int _x = StdIn.readInt();
			int _y = StdIn.readInt();
                                
 			pointArray[i++] = new Point(_x, _y);

        }

        //Double startTime = (double)System.currentTimeMillis();

        // seems to help?
        Arrays.sort(pointArray);

        // setup txt writer
        Out fileOut = new Out("visualPoints.txt");
        
       // nested loops man..
        for (int a = 0; a < numPoints; a++) {

        	for (int b = a + 1; b < numPoints; b++) {

        		for (int c = b + 1; c < numPoints; c++) {

        			// perhaps this check will be more effecient
        			
        			if (_pref.areCollinear(pointArray[a], pointArray[b], pointArray[c])) {

        				for (int d = c + 1; d < numPoints; d++) {

        					if (_pref.areCollinear(pointArray[a], pointArray[b], pointArray[c], pointArray[d])) {

        						Point[] toSort = new Point[4];
        						toSort[0] = pointArray[a];
        						toSort[1] = pointArray[b];
        						toSort[2] = pointArray[c];
        						toSort[3] = pointArray[d];

        						myBubbSort(toSort);


								System.out.println("4:" + _pref.getStringCoords(pointArray[a]) +
									" -> " + _pref.getStringCoords(pointArray[b]) + 
								 	" -> " + _pref.getStringCoords(pointArray[c]) + 
									" -> " + _pref.getStringCoords(pointArray[d]));

								fileOut.println("4:" + _pref.getStringCoords(pointArray[a]) +
									" -> " + _pref.getStringCoords(pointArray[b]) + 
								 	" -> " + _pref.getStringCoords(pointArray[c]) + 
									" -> " + _pref.getStringCoords(pointArray[d]));

        					}

        				}

        			}

        		}

        	}

        }

        //double totalTime = ((double)System.currentTimeMillis() - startTime) / 1000.0;

        //System.out.println(totalTime);
        
    }

}

