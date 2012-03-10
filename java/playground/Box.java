import java.util.*;
public class Box implements Comparable {
    private ArrayList<Number> aL = new ArrayList<Number>();
    private Number _sum=0;
    public Box(Number... j) {
        for (Number i: j) {
            aL.add(i);
            _sum = _sum.doubleValue() + i.doubleValue();
        }
    }
    public void add(Number... j) {
        for (Number i: j) {
            aL.add(i);
            _sum = _sum.doubleValue() + i.doubleValue();
        }
    }
    public Number sum() {
        return _sum;
    }
    public Number sum(Number... j) {
        Number sum=0;
        for (Number i: j) {
            sum = sum.doubleValue() + i.doubleValue();
        }
        return sum;
    }

    public void prsum() {
        System.out.println(sum());
    }
    public void pr() {
        System.out.print("\n(");
        String s="";
        for (Number i: aL) {
            System.out.print(s+i);
            s=",";
        }
        System.out.print(")");
    }
    public int compareTo(Object something) throws ClassCastException {
        if (!( something instanceof Box))
            throw new ClassCastException("A Box object expected.");
        Number Othersum  = ((Box) something).sum();
        return this._sum.intValue() - Othersum.intValue();
    }


}