package com.chirico;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;


import java.util.*;
import javax.naming.*;
import javax.sql.DataSource;
import java.sql.*;


import java.util.Date;
import java.util.Calendar;
import java.text.SimpleDateFormat;






/**
 * Simple Hello World servlet used to demonstrate many configuration options in
 * JBoss.




exec W_UTL.A_DAY('03/21/2010 9:23','18:00',10,13);
 */



@SuppressWarnings("serial")
public class itemsDP2 extends HttpServlet {

    ArrayList<String> sList = new ArrayList<String>();



    class TestClass0 {
        String s;
	ResultSet rs;

        TestClass0(String input) {
            s=input;
        }
        TestClass0(ResultSet rs) {
	    this.rs=rs;
	}
        TestClass0() {
            this("Chirico");
        }
        String pr() {
            return s;
        }
        String prH(String s) {
	    s="<td>"+s+"</td>";
            return s;
        }

    }





    @Override
    public void service(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException {
        PrintWriter out = response.getWriter();
	response.setHeader("content-type","text/html");



        DataSource ds = null;
        Connection conn = null;
        PreparedStatement pr = null;
        InitialContext ic;
	CallableStatement cstmt = null;
        Object temp;
        try {
            ic = new InitialContext();
            ds = (DataSource)ic.lookup( "java:/OracleDS" );
            conn = ds.getConnection();
            //pr = conn.prepareStatement("select beg_time, recorded from hours order by 1");


	    cstmt = conn.prepareCall("{call W_UTL.Reportc(?,?)}");


	    //	    cstmt.setString(1,"03/21/2010 9:23");

	    String date = "03/31/2010 09:23";
	    cstmt.setString(1,date);
	    cstmt.registerOutParameter(2, oracle.jdbc.driver.OracleTypes.CURSOR );
	    cstmt.execute();

	    //Cast the returned parameter, OracleTypes.CURSOR to a JDBC ResultSet
	    ResultSet rs = (ResultSet)cstmt.getObject(2);
            TestClass0 p1 = new TestClass0(rs);
	    ResultSetMetaData rsm = rs.getMetaData();
	    int columnCount = rsm.getColumnCount();
	    out.print("<?xml version=\"1.0\" ?>");
	    out.print("<items>\n");
	    while(p1.rs.next()) {
		out.print("<item column1=\"");
		out.print(p1.rs.getObject(1));
		out.print("\" column2=\"");
		out.print(p1.rs.getObject(2));
		out.print("\" column3=\"");
		out.print(p1.rs.getObject(4));
		out.print("\" column4=\"");
		out.print(p1.rs.getObject(5));
		out.print("\" column5=\"");
		out.print(p1.rs.getObject(6));
		out.print("\" />\n");

	    }
     	    out.println("</items>\n");
	    p1.rs.close();
	    if(cstmt != null)cstmt.close();
	    if(conn != null) conn.close();



        }catch (Exception e){
            out.println("Exception thrown " +e);
        }finally{

        }



    }





}




