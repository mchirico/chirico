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
public class InsertHours extends HttpServlet {

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
	String hrs = request.getParameter("hrs");
	String etime = request.getParameter("etime");
	String payp = request.getParameter("payp");
	String notes = request.getParameter("notes");
        out.print("date: "+date);
        out.print("<br>\n");
        out.print("hrs: "+hrs);
        out.print("<br>\n");
        out.print("etime: "+etime);
        out.print("<br>\n");
        out.print("pay period: "+payp);
        out.print("<br>\n");
        out.print("notes: "+notes);
        out.print("<br>\n<br>\n");




	String link = "https://192.168.1.12:8443/chirico/insert";
	out.print("<a href=\"");
	out.print(link);
	out.print("\">");
	out.print(link);
	out.print("</a>");
        out.print("<br>\n");
	out.print("<a href=\"");
	out.print("http://192.168.1.12:8080/chirico/insert?date=03/21/2009%209:23");
	out.print("\">");
	out.print("http://192.168.1.12:8080/chirico/insert?date=03/21/2009%209:23");
	out.print("</a>");
        out.print("<hr>\n<br>\n<br>");


	MyForm mf = new MyForm();
	out.print(mf.pr());


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

            // exec W_UTL.A_DAY('03/21/2010 9:23','18:00',10,13);
	    cstmt = conn.prepareCall("{call W_UTL.A_DAY2(?,?,?,?,?,?)}");


	    //	    cstmt.setString(1,"03/21/2010 9:23");
	    cstmt.setString(1,date);
	    cstmt.setString(2,etime);
	    cstmt.setString(3,hrs);
	    cstmt.setString(4,payp);
	    cstmt.setString(5,notes);
	    cstmt.registerOutParameter(6, oracle.jdbc.driver.OracleTypes.CURSOR );
	    cstmt.execute();

	    //Cast the returned parameter, OracleTypes.CURSOR to a JDBC ResultSet
	    ResultSet rs = (ResultSet)cstmt.getObject(6);
            TestClass0 p1 = new TestClass0(rs);
	    ResultSetMetaData rsm = rs.getMetaData();
	    int columnCount = rsm.getColumnCount();
	    out.print(columnCount);
	    out.print("\n");
	    while(p1.rs.next()) {
		for (int j=0;j< columnCount;j++){
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
