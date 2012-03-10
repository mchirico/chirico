import java.sql.* ;
import oracle.jdbc.*;

public class SimpleStoredProc {

    public static void main(String s[]) {
        Object temp;
	try {

            DriverManager.registerDriver(new oracle.jdbc.driver.OracleDriver(  ));
            Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@big:1521:orcl","chirico","mike");



	    CallableStatement cstmt = conn.prepareCall("{call W_UTL.Reportc(?,?)}");


	    cstmt.setString(1,"03/21/2010 9:23");
	    //	    cstmt.registerOutParameter(2, oracle.jdbc.driver.OracleTypes.CURSOR );
	    cstmt.registerOutParameter(2, OracleTypes.CURSOR );



	    cstmt.execute();

	    //Cast the returned parameter, OracleTypes.CURSOR to a JDBC ResultSet
	    ResultSet rs = (ResultSet)cstmt.getObject(2);
	    ResultSetMetaData rsm = rs.getMetaData();
	    int columnCount = rsm.getColumnCount();
	    System.out.println(columnCount);
	    while(rs.next()) {
		for (int j=0;j< columnCount;j++){
		    temp = rs.getObject(j+1);
		    System.out.print(temp);
		    System.out.print(",");
		}
		System.out.println();
	    }
	    rs.close();
	    if(cstmt != null)cstmt.close();
	    if(conn != null) conn.close();
	} catch (Exception e) {
	    System.out.println(e.toString());
	}
    }
}

