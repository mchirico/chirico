package test0;

import java.io.IOException;
import javax.servlet.http.*;

@SuppressWarnings("serial")
public class Test0Servlet extends HttpServlet {
	public void doGet(HttpServletRequest req, HttpServletResponse resp)
			throws IOException {
		resp.setContentType("text/plain");
		resp.getWriter().println("Hello, world");
		resp.getWriter().println("More data");
		Chirico0 c = new Chirico0();
		resp.getWriter().println("This is i: "+c.geti());
		c.inc();
		resp.getWriter().println("This is i: "+c.geti());
		
	}
}
