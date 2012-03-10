package workout0;

import java.io.IOException;

import javax.servlet.http.*;


@SuppressWarnings("serial")

public class PrettyPrint  extends HttpServlet {
	public void doStuff(HttpServletRequest req, HttpServletResponse resp, 
			 String s)
			throws IOException {
//		resp.setContentType("text/plain");
		for(int i=0; i < 5; ++i)
		resp.getWriter().println(s);
	}
}