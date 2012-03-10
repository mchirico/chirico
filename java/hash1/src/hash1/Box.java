package hash1;

public class Box {
	private String s;
	private Double d;
	private byte b;

	public void setS(String s) {
		this.s = s;
	}

	public Box(Double d) {
		this.d = d;
		set_b((byte) 0);
	}

	public Box() {
		b=0;
		
	}

	public Double getD() {
		return d;
	}
	

	public void setD(Double d) {
		this.d = d;
	}

	public void incD(Double d) {
			  this.d+=d;
			  inc_b();
	}
	
	public String getS() {
		return s;
	}
	
	
	private void set_b(byte b){
		this.b=b;
	}
	private void inc_b() {
	    b++;
	}
	
	
}
