

public class PlayUrl {
    YahooFinance y = new YahooFinance();
    MyHttps h = new MyHttps();

    public void mfun(String s) {
        y.getPrice(s);
	h.getUrl("https://mchiricosecure.appspot.com/guestbook");

    }

    public static void main(String[] arg) {
	PlayUrl p = new PlayUrl();
	final String[] s = {"rht","msft"};
	for(int i=0; i < s.length; ++i) {
	    System.out.println(s[i]);
	    p.mfun(s[i]);
	}

    }

}