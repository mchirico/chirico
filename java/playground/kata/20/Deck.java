public class Deck {

    public static final int DECK_SIZE = 52;
    private card[] cards = new card[DECK_SIZE];
    public void print() {
        for (int i=0; i < cards.length; ++i)
            System.out.println("i="+cards[i]);
    }

    public static void main(String[] args) {
        Deck d = new Deck();
        d.go();
    }
    public void go() {
        System.out.println("We are at go\n");
        for (int i=0; i < cards.length; ++i)
            cards[i]= new card();
        print();
    }
}
