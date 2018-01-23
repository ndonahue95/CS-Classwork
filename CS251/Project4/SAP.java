

import java.util.ArrayList;
import java.lang.System;
import java.io.FileInputStream;
import java.util.Scanner;
import java.io.File;

public class SAP {
    
    private Digraph diG;
    
    private int minLength;
    private int minAncestor;
    
    // constructor
    public SAP(Digraph G) {
        this.minLength = -1;
        this.minAncestor = -1;
        
        this.diG = new Digraph(G);
    }


    private void doSAPWork(BreadthFirstDirectedPaths bfv, BreadthFirstDirectedPaths bfw) {
        int min = -1;
        int ancestor = -1;

        // actively check all vertexes in Digraph to see which is shortest
        for (int i = 0; i < diG.V(); i++) {
            if (bfv.hasPathTo(i) && bfw.hasPathTo(i)) {

                int length = bfv.distTo(i) + bfw.distTo(i);

                if (length < min || min == -1) {
                    min = length;
                    ancestor = i;
                }

            }
        }
        
        if (min == -1) {				// CASE: no path found

            minLength = -1;
            minAncestor = -1;

        } else {						// CASE: path found! add it

            minLength = min;
            minAncestor = ancestor;

        }
    }

    private void findSAPHelper(int v, int w) {

        BreadthFirstDirectedPaths bfv = new BreadthFirstDirectedPaths(diG, v);
        BreadthFirstDirectedPaths bfw = new BreadthFirstDirectedPaths(diG, w);

        doSAPWork(bfv, bfw);
    }

    public int length(int v, int w) {

        findSAPHelper(v, w);

        return minLength;
    }


    public int ancestor(int v, int w) {

        findSAPHelper(v, w);

        return minAncestor;
    }







/* - = - = - = - = - = - = - = - = - = - = - = - = -

	THESE ARE HELPER FUNCTIONS FOR WORDNET!!!!
		to use with the Bag.class Iterable type

 - = - = - = - = - = - = - = - = - = - = - = - = - */

    private void findSAPHelper(Iterable<Integer> vList, Iterable<Integer> wList) {

        BreadthFirstDirectedPaths bfv = new BreadthFirstDirectedPaths(diG, vList);
        BreadthFirstDirectedPaths bfw = new BreadthFirstDirectedPaths(diG, wList);
        
        doSAPWork(bfv, bfw);
    }

    public int length(Iterable<Integer> v, Iterable<Integer> w) {

        findSAPHelper(v, w);

        return minLength;
    }

    public int ancestor(Iterable<Integer> v, Iterable<Integer> w) {
        
        findSAPHelper(v, w);

        return minAncestor;
    }

/* - = - = - = - = - = - = - = - = - = - = - = - = -

	THESE ARE HELPER FUNCTIONS FOR WORDNET!!!!

 - = - = - = - = - = - = - = - = - = - = - = - = - */








    public static void main(String[] args) {

    	// Read arg[0] to make digraph
        In in = new In(args[0]);
        Digraph G = new Digraph(in);

        // Create SAP on digraph
        SAP sap = new SAP(G);


        // Process the input file ****.input
        In in2 = new In(args[1]);

        while (!in2.isEmpty()) {

            int v = in2.readInt();
            int w = in2.readInt();

            int length   = sap.length(v, w);
            int ancestor = sap.ancestor(v, w);

            StdOut.printf("sap = %d, ancestor = %d\n", length, ancestor);

        }
        
    }

}