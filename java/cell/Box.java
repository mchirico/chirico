class Box<E> {
    private Box<E> next;
    private E element;
    public Box(E element) {
	this.element = element;
    }
    public Box(E element, Box<E> next) {
	this.element = element;
	this.next = next;
    }
    public E getElement() {
	return element;
    }
    public void setElement(E element) {
	this.element = element = element;
    }
    public Box<E> getNext() {
	return next;
    }
    public void setNext(Box<E> next) {
	this.next = next;
    }

}
