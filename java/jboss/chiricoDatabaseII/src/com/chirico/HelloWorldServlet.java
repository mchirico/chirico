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



/**
 * Simple Hello World servlet used to demonstrate many configuration options in
 * JBoss.
 */



@SuppressWarnings("serial")
public class HelloWorldServlet extends HttpServlet {

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

	/*
	  This is an example of getting input.
	 */
	String date = request.getParameter("date");
        out.print("date: "+date);
        out.print("<br>\n<br>\n");

	String doc="http://www.jboss.org/file-access/default/members/jbossas/freezone/docs/Installation_And_Getting_Started_Guide/5/html_single/index.html#Sample_JSF_EJB3_Application-JSF_Web_Pages";
	out.print("<a href=\"");
	out.print(doc);
	out.print("\">");
	out.print("Documentation");
	out.print("</a>");
        out.print("<br>\n");

	out.print("<a href=\"");
	out.print("https://192.168.1.12:8443/chirico/sayhello?date=03/21/2010%209:23");
	out.print("\">");
	out.print("https://192.168.1.12:8443/chirico/sayhello?date=03/21/2010%209:23");
	out.print("</a>");
        out.print("<br>\n");
	out.print("<a href=\"");
	out.print("https://192.168.1.12:8443/chirico/sayhello?date=03/21/2009%209:23");
	out.print("\">");
	out.print("https://192.168.1.12:8443/chirico/sayhello?date=03/21/2009%209:23");
	out.print("</a>");
        out.print("<hr>\n<br>\n<br>");








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
	    cstmt.setString(1,date);
	    cstmt.registerOutParameter(2, oracle.jdbc.driver.OracleTypes.CURSOR );
	    cstmt.execute();

	    //Cast the returned parameter, OracleTypes.CURSOR to a JDBC ResultSet
	    ResultSet rs = (ResultSet)cstmt.getObject(2);
            TestClass0 p1 = new TestClass0(rs);
	    ResultSetMetaData rsm = rs.getMetaData();
	    int columnCount = rsm.getColumnCount();
	    out.print(columnCount);
	    out.print("<br>\n");
	    while(p1.rs.next()) {
		for (int j=1;j< columnCount;j++){
		    out.print(p1.rs.getObject(j+1));
		    out.print(",");
		}
		out.println("<br>");
	    }
	    p1.rs.close();
	    if(cstmt != null)cstmt.close();
	    if(conn != null) conn.close();



        }catch (Exception e){
            out.println("Exception thrown " +e);
        }finally{

        }






    }



}
