class Cell<E> {
    private Cell<E> next;
    private E element;
    public Cell(E element) {
        this.element = element;
    }
    public Cell(E element, Cell<E> next) {
        this.element = element;
        this.next = next;
    }
    public E getElement() {
        return element;
    }
    public void setElement(E element) {
        this.element = element;
    }
    public Cell<E> getNext() {
        return next;
    }
    public void setNext(Cell<E> next) {
        this.next = next;
    }
}
