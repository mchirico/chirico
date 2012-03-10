class junk {

	public static int max(int first, int... rest) {
		int max = first;
		for (int i:rest) {
			if (i > max)
				max = i;
		}
		return max;
	}


    public static String print(Object... values) {
	StringBuilder sb = new StringBuilder( );
	sb.append(": ");
	for (Object o : values) {
	    sb.append(o)
		.append(" ");
	}
	return sb.toString( );
    }





	public static void main(String args[]) {
		Integer k = 3;
		A a = new A();
		a.set_note("This is a long note");
		String s = print(1,2,3);
		a.pr();
                System.out.println("test:" + max(2,3,4,5,6,300) + print(1,2,3));

		if (args.length == 1)
		    System.out.println("test:" + args[0]+max(1,2,3,4,5,6,7,8));
	}



}
