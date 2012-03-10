
import java.sql.* ;


public class SimpleConn {

    public static void main(String[] args) {



        try {
            DriverManager.registerDriver(new oracle.jdbc.driver.OracleDriver(  ));
            Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@localhost:15210:orcl","chirico","mike");


            Statement stmt = conn.createStatement(  );
            ResultSet rset = stmt.executeQuery(
                                 "select 'Hello OCI driver tester '||USER||'!' result from dual");

            while (rset.next(  ))
                System.out.println(rset.getString(1));
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