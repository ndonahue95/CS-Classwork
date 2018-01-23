import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.ArrayList;
import java.util.Collections;


public class Fast {

    public Fast() {


    }

    private static List<Point> dupeThatList(List<Point> pList, int index) {

        List<Point> pListNew = new ArrayList<Point>();

        for (int i = index + 1; i < pList.size(); i++) 
            pListNew.add(pList.get(i));

        return pListNew;

    }

    private static String getThatKey(Point p1, Point p2) {

        return (p1.toString() + "," + p2.toString());

    }

    private static void printThatList(List<Point> pList, Out fileOut) {

    Point _pref = new Point(420, 420);


     Collections.sort(pList);
     System.out.print(pList.size() + ":");
     fileOut.print(pList.size() + ":");

     for(int k = 0; k < pList.size() - 1; k++) {
           System.out.print(_pref.getStringCoords(pList.get(k)) + " -> ");
           fileOut.print(_pref.getStringCoords(pList.get(k)) + " -> ");
     }

     System.out.print(_pref.getStringCoords(pList.get(pList.size() - 1)) + "\n");
     fileOut.print(_pref.getStringCoords(pList.get(pList.size() - 1)) + "\n");

    }
    
    public static void main(String[] args) {

        // Creat point object for referencing.

        Point _pref = new Point(420, 420);
        
        int numPoints = StdIn.readInt();
        List<Point> points = new ArrayList<Point>();

        while (!StdIn.isEmpty()) {
        
         int _x = StdIn.readInt();
         int _y = StdIn.readInt();
                                
             Point p = new Point(_x, _y);
             points.add(p);

        }

        //Double startTime = (double)System.currentTimeMillis();

        // setup txt writer
        Out fileOut = new Out("visualPoints.txt");

        Collections.sort(points);


        Map<String, Boolean> finalMAP = new HashMap<String, Boolean>();

        for (int i = 0; i < points.size(); i++) {

            List<Point> dupedList = dupeThatList(points, i);


            Collections.sort(dupedList, points.get(i).BY_SLOPE_ORDER);

            int j = 0;
            while (j < dupedList.size()) {

                double slope = points.get(i).localSlope(dupedList.get(j));
                List<Point> possPoints = new ArrayList<Point>(); 

                possPoints.add(points.get(i));
                possPoints.add(dupedList.get(j));

                j++;

                while (j < dupedList.size() && points.get(i).localSlope(dupedList.get(j)) == slope) {

                    possPoints.add(dupedList.get(j));
                    j++;

                } 

                if (possPoints.size() >= 4) {

                    boolean toPrint = false;

                    for (int k = 0; k < possPoints.size() - 1; k++) {

                        String key = getThatKey(possPoints.get(k), possPoints.get(k+1));

                        if (!finalMAP.containsKey(key)) {

                            finalMAP.put(key, true);
                            toPrint = true;

                        }

                    }

                    if (toPrint) {

                        printThatList(possPoints, fileOut);

                    }
                }
            }
        }

        //double totalTime = ((double)System.currentTimeMillis() - startTime) / 1000.0;

        //System.out.println(totalTime);
    }
}
