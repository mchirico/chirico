
import java.sql.* ;
public class ConnOracle {
    public static void main(String[] args) {
        try {
            DriverManager.registerDriver(new oracle.jdbc.driver.OracleDriver(  ));
            Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@localhost:1521:orcl","chirico","mike");

            Statement stmt = conn.createStatement(  );

            ResultSet rset = stmt.executeQuery(
                                 "select * from junk");

            ResultSetMetaData rsMetaData = rset.getMetaData();
            while (rset.next(  )){
                String s="";
                for (int i=1; i < rsMetaData.getColumnCount(); ++i) {
                    System.out.print(s+rset.getString(i));
                    s=",";
                }
                System.out.println();
            }


            rset.close(  );
            stmt.close(  );
            conn.close(  );

        }
        catch (SQLException e) {
            System.out.println("Oops! Got a SQL error: " + e.getMessage(  ));
            System.exit(1);
        }

    }

}