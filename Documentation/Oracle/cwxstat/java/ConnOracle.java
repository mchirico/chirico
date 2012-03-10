
import java.sql.* ;
import oracle.jdbc.*;
import oracle.jdbc.pool.OracleDataSource;
public class ConnOracle {
    public static void main(String[] args) {
        try {
            DriverManager.registerDriver(new oracle.jdbc.driver.OracleDriver(  ));
            Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@//192.168.1.12:1521/orcl","chirico","mike");

	    /*
            Statement stmt = conn.createStatement(  );

            ResultSet rset = stmt.executeQuery(
                                 "select \"start\",\"end\",\"end\"-\"start\" from hours");


            while (rset.next(  ))
                System.out.println(rset.getString(1)+","+rset.getString(2)+","+rset.getString(3));

            rset.close(  );
            stmt.close(  );
            conn.close(  );*/

        }
        catch (SQLException e) {
            System.out.println("Oops! Got a SQL error: " + e.getMessage(  ));
            System.exit(1);
        }

    }

}