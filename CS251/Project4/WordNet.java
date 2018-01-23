
import java.util.HashMap;


// HASHMAP for the map between Number and ID
// Hashmap(Key) = Value   -> Key = name     Value = ID 
//                          ****Utilize Bag.class

public class WordNet {

    // Digraph & SAP
    private Digraph diG;
    private SAP sapObj;

    // HashMap for each txt file
    // see top for key,value correspondence
    private HashMap<String, Bag<Integer>> map_str_int;
    private HashMap<Integer, Bag<String>> map_int_str;

    
    public WordNet(String synsets, String hypernyms) {

        // open the txt files
        In txt1 = new In(synsets);
        In txt2 = new In(hypernyms);

        
        // Init hashmaps
        map_str_int = new HashMap<String, Bag<Integer>>();
        map_int_str = new HashMap<Integer, Bag<String>>();

        int count = 0;

        // compose hashmap w/ synsets txt file
        while (txt1.hasNextLine()) {

            String [] splitLine = txt1.readLine().split(",");

            int index = Integer.parseInt(splitLine[0]);
            String [] wordsArr = splitLine[1].split(" ");

            for (String w : wordsArr) {

                // ADD TWICE, FOR REVERSE SEARCHING!!!!

                Bag<Integer> bagInt = map_str_int.get(w);

                if (bagInt == null) {       // CASE: CREATE KEY

                    bagInt = new Bag<Integer>();
                    bagInt.add(index);
                    map_str_int.put(w, bagInt);

                } else {                    // CASE: ADD To EXISTING KEY

                    bagInt.add(index);

                }

                Bag<String> bagStr = map_int_str.get(index);

                if (bagStr == null) {       // CASE: CREATE KEY

                    bagStr = new Bag<String>();
                    bagStr.add(w);
                    map_int_str.put(index, bagStr);

                } else {                    // CASE: ADD To EXISTING KEY

                    bagStr.add(w);

                }
                
            }

            count++;
        }


        // build digraph w/ hypernyms txt
        diG = new Digraph(count + 1);

        while (txt2.hasNextLine()) {

            String [] hyperSplit = txt2.readLine().split(",");

            // DO WE NEED ERROR CHECKING!?>!?!?!?!? LN LKAjshskash
            // piazza pls :(


            int hyperIndex = Integer.parseInt(hyperSplit[0]);

            for (int i = 1; i < hyperSplit.length; i++) {

                diG.addEdge(hyperIndex, Integer.parseInt(hyperSplit[i]));
            }
        }
        

        sapObj = new SAP(diG);

    }


    public boolean isNoun(String word) {

        return map_str_int.containsKey(word);

    }



    // NOTE:
    //  PIAZZA SAID ONLY NEED TO PRINT BACK 1 WORD
    //  NO NEED TO HANDLE CONCATING MULTIPLE WORDS
    private String getWordFromBag(Bag<String> bag) {

        Stack<String> stack = new Stack<String>();

        // Add all strings to stack
        for (String str : bag)
            stack.push(str);


        // print last added to astck
        // (not required to concat all in bag)

        return stack.pop();

    }

    private Integer getIntFromBag(Bag<Integer> bag) {

        Stack<Integer> stack = new Stack<Integer>();

        // Add all strings to stack
        for (int i : bag)
            stack.push(i);


        // print last added to astck
        // (not required to concat all in bag)

        return stack.pop();

    }



    public void printSap(String nounA, String nounB) {

        // 
        // LENGTH PART
        //
        int length;

        if (!isNoun(nounA) || !isNoun(nounB)) {

            length = -1;

        } else {

            Bag<Integer> bagA = map_str_int.get(nounA);
            Bag<Integer> bagB = map_str_int.get(nounB);

            int bagAInd = getIntFromBag(bagA);
            int bagBInd = getIntFromBag(bagB);
                
            if (bagA.size() > 1 || bagB.size() > 1) {

                length = sapObj.length(bagA, bagB);

            } else {

                length = sapObj.length(bagAInd, bagBInd);

            }

        }




        // 
        // ANCESTOR PART
        //
        String ancestorStr;
        int ancestor = -1;

        if (!isNoun(nounA) || !isNoun(nounB)) {

            ancestorStr = "null";

        } else {

            Bag<Integer> bagA = map_str_int.get(nounA);
            Bag<Integer> bagB = map_str_int.get(nounB);

            if (bagA.size() > 1 || bagB.size() > 1) {

                ancestor = sapObj.ancestor(bagA, bagB);
                ancestorStr = getWordFromBag(map_int_str.get(ancestor));

            } else {

                int a = getIntFromBag(bagA);
                int b = getIntFromBag(bagB);

                ancestor = sapObj.ancestor(a, b);
                ancestorStr = getWordFromBag(map_int_str.get(ancestor));
                
            }

        }


        StdOut.printf("sap = %d, ancestor = %s\n", length, ancestorStr);

    }

    public static void main(String[] args) {

        WordNet wordnet = new WordNet(args[0], args[1]);

        // Process the input file ****.input
        In in2 = new In(args[2]);

        while (!in2.isEmpty()) {

            String nounA = in2.readString();
            String nounB = in2.readString();

            wordnet.printSap(nounA, nounB);

        }
        
    }

}
