package testL0;

import java.io.IOException;
import javax.servlet.http.*;
import java.util.Arrays;

public class stuff0 {
	String[] s0 = new String[50];
	private HttpServletRequest req;
	private HttpServletResponse resp;

	public stuff0(HttpServletRequest req, HttpServletResponse resp){
		this.req=req;
		this.resp=resp;
		Arrays.fill(s0, "*");
		
	}
	public void pt(String s) throws IOException {
		resp.getWriter().println(s);
			resp.getWriter().println(s0[0]);
	}
	
}
