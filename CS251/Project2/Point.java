/*************************************************************************
 * Compilation:  javac Point.java
 *
 * Description: An immutable data type for points in the plane.
 *
 *************************************************************************/

import java.util.Comparator;

public class Point implements Comparable<Point>{
    // compare points by slope
    public final Comparator<Point> BY_SLOPE_ORDER = new Comparator<Point>() {

        public int compare(Point p1, Point p2) {

            double s1 = localSlope(p1);
            double s2 = localSlope(p2);

            if (s1 == s2)
                return 0;

            if (s1 < s2)
                return -1;

            return 1;
        }

    };

    private final int x;                              // x coordinate
    private final int y;                              // y coordinate

    // constructor
    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }


    // SLOPE OF TWO POINTS!!!
    public static double getSlope(Point p, Point q) {

    	if (p.y == q.y)
    		return 0.0;

    	return (double) ((q.y * 1.0 - p.y * 1.0) / (q.x * 1.0 - p.x * 1.0));

    }


    // SLOPE FROM THIS POINT OBJECT!!!
    public double localSlope(Point p) {

    	if (p.y == this.y)
    		return 0.0;

    	return (double) ((this.y * 1.0 - p.y * 1.0) / (this.x * 1.0 - p.x * 1.0));

    }

    public static String getStringCoords(Point p) {

    	return "(" + p.x + ", " + p.y + ")";

    }

    // are the 3 points p, q, and r collinear?
    public static boolean areCollinear(Point p, Point q, Point r) {
    
    	double slope_pq = getSlope(p, q);
    	double slope_qr = getSlope(q, r);

    	return (slope_pq == slope_qr);

    }

    // are the 4 points p, q, r, and s collinear?
    public static boolean areCollinear(Point p, Point q, Point r, Point s) {

        return (areCollinear(p, q, r) & areCollinear(q, r, s));

    }

    // is this point lexicographically smaller than that one?
    public int compareTo(Point that) {
        
        // CASE: Smaller
        if ((this.x < that.x) || (this.x == that.x && this.y < that.y))
			return -1;

		// CASE: Same point, lol
		if (this.y == that.y && this.x == that.x)
			return 0;

		// CASE: larger
        return 1;
    }

}
