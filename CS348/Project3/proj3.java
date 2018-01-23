import java.sql.*;
import java.io.*;

public class Project3 {
    // JDBC driver name and database URL
    static final String JDBC_DRIVER = "oracle.jdbc.OracleDriver";
    static final String DB_URL = "jdbc:oracle:thin:@claros.cs.purdue.edu:1524:strep";

    //  Database credentials
    static final String USER = "ndonahu";
    static final String PASS = "nick420420";

    // buffered writer
    FileWriter fw = new FileWriter("output.txt");
    BufferedWriter bw = new BufferedWriter(fw);

    private static int outCounter = 1;
    private static void writeOut(String ogLine, String toWrite, boolean isQuit) {
        if (!isQuit) {
            //System.out.println(outCounter++ + ": " + ogLine + "\n" + toWrite + "\n");
            bw.write(outCounter++ + ": " + ogLine + "\n" + toWrite + "\n\n")
        } else {
            //System.out.println(outCounter++ + ": " + ogLine);
            bw.write(outCounter++ + ": " + ogLine + "\n");
        }
    }

    private static boolean isRealLetter(char c) {
        return (c >= 'a' && c <= 'z') ||
               (c >= 'A' && c <= 'Z');
    }

   private static String upperA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
   private static String lowerA = "abcdefghijklmnopqrstuvwxyz";

    private static String akEncrypt(String plaintext, String key) {
        int l = plaintext.length();

        String manipulated = key + plaintext;
        String newText = manipulated;//manipulated.substring(0, manipulated.length() - key.length());

        String toReturn = "";
        int j = 0;
        int i = 0;
        while (toReturn.length() != l) {
            if (isRealLetter(plaintext.charAt(i)) && isRealLetter(newText.charAt(j))) {
                int x = lowerA.indexOf(Character.toLowerCase(plaintext.charAt(i)));
                int y = lowerA.indexOf(Character.toLowerCase(newText.charAt(j)));

                int maths = (x + y) % 26;

                if (Character.isUpperCase(plaintext.charAt(i))) {
                    toReturn += upperA.charAt(maths);
                } else {
                    toReturn += lowerA.charAt(maths);
                }

                i++;
                j++;
            } else {
                if (!isRealLetter(plaintext.charAt(i))) {
                    toReturn += plaintext.charAt(i);
                    i++;
                }
                if (!isRealLetter(newText.charAt(j))) {
                    j++;
                }
            }
        }

        return toReturn;
    }

    private static String akDecrypt(String cipherText, String key) {
        int l = cipherText.length();

        String workString = key;
        String toReturn = "";
        int j = 0;
        int i = 0;
        while (toReturn.length() != l) {
            if (isRealLetter(cipherText.charAt(i)) && isRealLetter(workString.charAt(j))) {
                int x = lowerA.indexOf(Character.toLowerCase(cipherText.charAt(i)));
                int y = lowerA.indexOf(Character.toLowerCase(workString.charAt(j)));

                int maths = (x - y) % 26;
                maths = (maths<0)? maths + 26 : maths;

                if (Character.isUpperCase(cipherText.charAt(i))) {
                    toReturn += upperA.charAt(maths);
                    workString += upperA.charAt(maths);
                } else {
                    toReturn += lowerA.charAt(maths);
                    workString += lowerA.charAt(maths);
                }

                i++;
                j++;
            } else {
                if (!isRealLetter(cipherText.charAt(i))) {
                    toReturn += cipherText.charAt(i);
                    i++;
                }
                if (!isRealLetter(workString.charAt(j))) {
                    j++;
                }
            }
        }

        return toReturn;
    }

    public static void main(String[] args) {
        Connection conn = null;
        Statement stmt = null;
        try {
            Class.forName(JDBC_DRIVER);

            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            stmt = conn.createStatement();

            // -=-=-=-=-=-=-=-
            // open txt file
            // -=-=-=-=-=-=-=-

            String line = null;

            try {
                FileReader fileReader = new FileReader(args[0]);
                BufferedReader bufferedReader = new BufferedReader(fileReader);

                int curUserId = 0;
                String sqlString = "";

                while ((line = bufferedReader.readLine()) != null) {

                    if (line.substring(0, Math.min(line.length(), 4)).toUpperCase().equals("QUIT")) {
                        writeOut(line, "", true);
                        break;
                    }

                    // -=-=-=-=-=-=-=-
                    //     HANDLING
                    // -=-=-=-=-=-=-=-

                    if (line.substring(0, Math.min(line.length(), 5)).toUpperCase().equals("LOGIN")) {
                        String[] lineArr = line.split(" ");

                        sqlString = "SELECT userid FROM users WHERE username = '" + lineArr[1] + "' AND password = '" + lineArr[2] + "'";
                        ResultSet rs = stmt.executeQuery(sqlString);
                        if (!rs.isBeforeFirst()) {
                            curUserId = 0;
                            writeOut(line, "Invalid login", false);
                        } else {
                            while (rs.next()) {
                                curUserId = rs.getInt("userid");
                                writeOut(line, "Login successful", false);
                            }
                        }
                    } else if (line.substring(0, Math.min(line.length(), 6)).toUpperCase().equals("CREATE")) {
                        String[] lineArr = line.split(" ");

                        if (lineArr[1].toUpperCase().equals("ROLE")) {
                            if (curUserId == 1) {
                                ResultSet rs = stmt.executeQuery("SELECT MAX(roleid) AS nextId FROM roles");

                                int nextId = 0;
                                while (rs.next()) {
                                    nextId = rs.getInt("nextId") + 1;
                                }

                                rs = stmt.executeQuery("INSERT INTO roles VALUES (" + nextId + ", '" + lineArr[2] + "', '" + lineArr[3] + "')");
                               
                                writeOut(line, "Role created successfully", false);
                            } else {
                                writeOut(line, "Authorization failure", false);
                            }
                        } else if (lineArr[1].toUpperCase().equals("USER")) {
                            if (curUserId == 1) {
                                ResultSet rs = stmt.executeQuery("SELECT MAX(userid) AS nextId FROM users");

                                int nextId = 0;
                                while (rs.next()) {
                                    nextId = rs.getInt("nextId") + 1;
                                }

                                rs = stmt.executeQuery("INSERT INTO users VALUES (" + nextId + ", '" + lineArr[2] + "', '" + lineArr[3] + "')");
                           
                                writeOut(line, "User created successfully", false);
                            } else {
                                writeOut(line, "Authorization failure", false);
                            }
                        }
                    } else if (line.substring(0, Math.min(line.length(), 5)).toUpperCase().equals("GRANT")) {
                        String[] lineArr = line.split(" ");

                        if (lineArr[1].toUpperCase().equals("ROLE")) {
                            if (curUserId == 1) {
                                String username = lineArr[2];
                                String rolename = lineArr[3];

                                ResultSet rs = stmt.executeQuery("SELECT userid FROM users WHERE username = '" + username + "'");
                                rs.next();
                                int uid = rs.getInt("userid");

                                rs = stmt.executeQuery("SELECT roleid FROM roles WHERE rolename = '" + rolename + "'");
                                rs.next();
                                int rid = rs.getInt("roleid");

                                rs = stmt.executeQuery("INSERT INTO UsersRoles VALUES (" + uid + ", " + rid + ")");

                                writeOut(line, "Role assigned successfully", false);
                            } else {
                                writeOut(line, "Authorization failure", false);
                            }
                        } else if (lineArr[1].toUpperCase().equals("PRIVILEGE")) {
                            if (curUserId == 1) {
                                String privName = lineArr[2];
                                String roleName = lineArr[4];
                                String tabName = lineArr[6];

                                ResultSet rs = stmt.executeQuery("SELECT roleid FROM roles WHERE rolename = '" + roleName + "'");
                                rs.next();
                                int rid = rs.getInt("roleid");

                                rs = stmt.executeQuery("SELECT privid FROM privileges WHERE privname = '" + privName + "'");
                                rs.next();
                                int pid = rs.getInt("privid");                               

                                rs = stmt.executeQuery("INSERT INTO RolesPrivileges VALUES (" + rid + ", " + pid + ", '" + tabName + "')");

                                writeOut(line, "Privilege granted successfully ", false);
                            } else {
                                writeOut(line, "Authorization failure", false);
                            }
                        }
                    } else if (line.substring(0, Math.min(line.length(), 6)).toUpperCase().equals("REVOKE")) {
                        String[] lineArr = line.split(" ");

                        if (curUserId == 1) {
                            String privName = lineArr[2];
                            String roleName = lineArr[4];
                            String tabName = lineArr[6];

                            ResultSet rs = stmt.executeQuery("SELECT roleid FROM roles WHERE rolename = '" + roleName + "'");
                            rs.next();
                            int rid = rs.getInt("roleid");

                            rs = stmt.executeQuery("SELECT privid FROM privileges WHERE privname = '" + privName + "'");
                            rs.next();
                            int pid = rs.getInt("privid");                               

                            rs = stmt.executeQuery("DELETE FROM RolesPrivileges WHERE roleid = " + rid + " AND privid = " + pid + " AND tablename = '" + tabName + "'");

                            writeOut(line, "Privilege revoked successfully ", false);
                        } else {
                            writeOut(line, "Authorization failure", false);
                        }
                    } else if (line.substring(0, Math.min(line.length(), 6)).toUpperCase().equals("INSERT")) {
                        String[] lineArr = line.split(" ");

                        String valuesRaw = line.substring(line.indexOf("VALUES(") + 7,  line.lastIndexOf(")"));
                        String[] vArr = valuesRaw.split(",(?=([^']*'[^']*')*[^']*$)");

                        String tabName = lineArr[2];
                        String afterValues = line.substring(line.lastIndexOf(")") + 2, line.length());
                        String[] lineArr2 = afterValues.split(" ");

                        ResultSet rs = stmt.executeQuery("SELECT RoleId FROM UsersRoles WHERE UserId = " + curUserId);

                        if (!rs.isBeforeFirst()) {
                            // this means no roles found
                            writeOut(line, "Authorization failure", false);
                        } else {
                            boolean allowed = false;
                            while (rs.next() && !allowed) {
                                int rid = rs.getInt("roleid");

                                Statement stmt2 = conn.createStatement();
                                ResultSet rs2 = stmt2.executeQuery("SELECT * FROM RolesPrivileges WHERE RoleId = " + rid + " AND PrivId = 1 AND tablename = '" + tabName + "'");

                                if (rs2.isBeforeFirst()) {
                                    allowed = true;
                                }
                            }
                            if (!allowed) {
                                writeOut(line, "Authorization failure", false);
                            } else {
                                int colId = Integer.parseInt(lineArr2[1]);
                                String ownerRole = lineArr2[2];

                                if (colId > 0) {
                                    sqlString = "";

                                    rs = stmt.executeQuery("SELECT EncryptionKey FROM Roles WHERE rolename = '" + ownerRole + "'");
                                    rs.next();
                                    String keyUsed = rs.getString("EncryptionKey");

                                    for (int i = 0; i < vArr.length; i++) {
                                        String toInsert = vArr[i];

                                        if (i == colId - 1) {
                                            toInsert = akEncrypt(toInsert, keyUsed);
                                        }

                                        if (sqlString.equals("")) {
                                            sqlString = toInsert;
                                        } else {
                                            sqlString = sqlString + "," + toInsert;
                                        }

                                    }

                                    rs = stmt.executeQuery("SELECT RoleId FROM Roles WHERE rolename = '" + ownerRole + "'");
                                    rs.next();
                                    int ownerRoleId = rs.getInt("roleid");

                                    rs = stmt.executeQuery("INSERT INTO " + tabName + " VALUES(" + sqlString + "," + colId + "," + ownerRoleId + ")");

                                } else {
                                    sqlString = "";

                                    for (int i = 0; i < vArr.length; i++) {
                                        if (sqlString.equals("")) {
                                            sqlString = vArr[i];
                                        } else {
                                            sqlString = sqlString + "," + vArr[i];
                                        }
                                    }
                                    rs = stmt.executeQuery("INSERT INTO " + tabName + " VALUES(" + sqlString + ",0,0)");
                                }

                                writeOut(line, "Row inserted successfully", false);
                            }
                        }
                    } else if (line.substring(0, Math.min(line.length(), 6)).toUpperCase().equals("SELECT")) {
                        String[] lineArr = line.split(" ");

                        String tabName = lineArr[3];

                        ResultSet rs = stmt.executeQuery("SELECT RoleId FROM UsersRoles WHERE UserId = " + curUserId);

                        if (!rs.isBeforeFirst()) {
                            // this means no roles found
                            writeOut(line, "Authorization failure", false);
                        } else {
                            boolean allowed = false;
                            while (rs.next() && !allowed) {
                                int rid = rs.getInt("roleid");

                                Statement stmt2 = conn.createStatement();
                                ResultSet rs2 = stmt2.executeQuery("SELECT * FROM RolesPrivileges WHERE RoleId = " + rid + " AND PrivId = 2 AND tablename = '" + tabName + "'");

                                if (rs2.isBeforeFirst()) {
                                    allowed = true;
                                }
                            }
                            if (!allowed) {
                                writeOut(line, "Authorization failure", false);
                            } else {
                                rs = stmt.executeQuery("SELECT * FROM " + tabName);

                                System.out.println(outCounter++ + ": " + line);

                                ResultSetMetaData rsmd = rs.getMetaData();
                                int cnt = rsmd.getColumnCount() - 2;

                                for (int i = 1; i <= cnt; i++) {
                                    if (i > 1) System.out.print(", ");
                                    System.out.print(rsmd.getColumnName(i));
                                }
                                System.out.print("\n");          

                                while (rs.next()) {
                                    int eCol = rs.getInt(rsmd.getColumnCount() - 1);
                                    int oRole = rs.getInt(rsmd.getColumnCount());

                                    for (int i = 1; i <= cnt; i++) {
                                        if (i > 1) System.out.print(", ");

                                        String toPrint = rs.getString(i);

                                        if (i == eCol) {
                                            // decrypt col
                                            //toPrint = eCol + " " + oRole;

                                            Statement stmt2 = conn.createStatement();
                                            ResultSet rs2 = stmt2.executeQuery("SELECT RoleId FROM UsersRoles WHERE UserId = " + curUserId);

                                            if (rs2.isBeforeFirst()) {
                                                allowed = false;
                                                while (rs2.next() && !allowed) {
                                                    int rid = rs2.getInt("roleid");

                                                    if (rid == oRole) {
                                                        allowed = true;
                                                    }
                                                }

                                                if (allowed) {
                                                    rs2 = stmt2.executeQuery("SELECT EncryptionKey FROM Roles WHERE roleid = " + oRole);
                                                    rs2.next();
                                                    toPrint = akDecrypt(toPrint, rs2.getString("EncryptionKey"));
                                                }
                                            }
                                        }

                                        System.out.print(toPrint);
                                    }
                                    System.out.print("\n");
                                }

                                System.out.println("\n");
                            }
                        }
                    }

                }

                bufferedReader.close();

            } catch (FileNotFoundException ex) {
                System.out.println("error opening file.");
            } catch (IOException ex) {
                System.out.println("error opening file");
            }





            // Clean-up environment
            //rs.close();
            stmt.close();
            conn.close();
        } catch (SQLException se) {
            //Handle errors for JDBC
            se.printStackTrace();
        } catch (Exception e) {
            //Handle errors for Class.forName
            e.printStackTrace();
        } finally {

            try {
                if (stmt != null)
                    stmt.close();
            } catch (SQLException se2) {
                // nothing we can do
            }

            try {
                if (conn != null)
                    conn.close();
            } catch (SQLException se) {
                se.printStackTrace();
            }

        }
    }
}