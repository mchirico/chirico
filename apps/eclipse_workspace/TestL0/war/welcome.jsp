<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page import="java.util.List" %>
<%@ page import="javax.jdo.PersistenceManager" %>
<%@ page import="com.google.appengine.api.users.User" %>
<%@ page import="com.google.appengine.api.users.UserService" %>
<%@ page import="com.google.appengine.api.users.UserServiceFactory" %>
<%@ page import="testL0.Database" %>
<%@ page import="testL0.PMF" %>

<html>
<head>
    <link type="text/css" rel="stylesheet" href="/stylesheets/main.css" />
  </head>



  <body>

<%
    UserService userService = UserServiceFactory.getUserService();
    User user = userService.getCurrentUser();
    if (user != null) {
%>
<p>Hello, <%= user.getNickname() %>! (You can
<a href="<%= userService.createLogoutURL(request.getRequestURI()) %>">sign out</a>.)</p>
<%
    } else {
%>
<p>Hello!
<a href="<%= userService.createLoginURL(request.getRequestURI()) %>">Sign in</a>
to include your name with greetings you post.</p>
<%
    }
%>

<%
PersistenceManager pm = PMF.get().getPersistenceManager();
String query = "select from " + Database.class.getName();
List<Database> database = (List<Database>) pm.newQuery(query).execute();
    if (database.isEmpty()) {
%>
<p>The guestbook has no messages.</p>
<%
    } else {
        for (Database g : database) {
            if (g.getRemoteAddr() == null) {
%>
<p>An anonymous person wrote:</p>
<%
            } else {
%>
<br><%= g.getStuff() %>
<p><b><%= g.getRemoteAddr() %></b> wrote:</p>
<%
            }
%>
<blockquote><%= g.getContent() %></blockquote>
<%
        }
    }
    pm.close();
%>

    <form action="/testl0" method="post">
      <div><textarea name="stuff" rows="3" cols="60"></textarea></div>
      <div><input type="submit" value="Post Greeting" /></div>
    </form>

  </body>
</html>
