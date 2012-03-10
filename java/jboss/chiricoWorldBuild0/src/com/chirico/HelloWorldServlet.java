package com.chirico;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;


import java.util.*;



/**
 * Simple Hello World servlet used to demonstrate many configuration options in
 * JBoss.
 */



@SuppressWarnings("serial")
public class HelloWorldServlet extends HttpServlet {

    ArrayList<String> sList = new ArrayList<String>();

    class TestClass0 {
        String s;

        TestClass0(String input) {
            s=input;
        }
        TestClass0() {
            this("Chirico");
        }
        String pr() {
            return s;
        }

    }


    TestClass0 p1 = new TestClass0("digger");


    @Override
    public void service(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException {
        PrintWriter out = response.getWriter();

        sList.add("one");
        sList.add("two");
        sList.add("three");
        sList.add("four");
        out.println("<html><body>There is more<br>");
        out.println("This is more data<br> and more <br>");
        out.println(p1.pr());
        for (int i=0; i < sList.size(); ++i)
        {
            out.println("<br>");
            out.println(sList.get(i));
        }

        out.println("</body></html>");
        out.close();
    }
}
