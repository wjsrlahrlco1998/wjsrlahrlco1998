
public class BoundedBuffer<E> {
	private static final int BUFFER_SIZE = 5;
	
	private int count, in, out;
	private E[] buffer;
	
	@SuppressWarnings("unchecked")
	public BoundedBuffer() {
		count = 0;
		in = 0;
		out = 0;
		buffer = (E[]) new Object[BUFFER_SIZE];
	}
	
	/* ���ε༭�� ȣ���ϴ� �Լ�*/
	public synchronized void insert(E item) {
		/*7.11 ����*/
		while (count == BUFFER_SIZE) {
			try {
				System.out.println("Inserting item " + (int)item + " is waiting for the full buffer.");
				wait();
			}
			catch (InterruptedException ie) {}
		}
		
		buffer[in] = item;
		
		System.out.println("Item " + (int)item + "has been inserted at index " + in);
		
		in = (in + 1) % BUFFER_SIZE;
		count++;
		
		System.out.println("Notify() has been called in the insert()");
		System.out.println("");
		notify();
	}
	/*�Һ��ڰ� ȣ���ϴ� �Լ�*/
	public synchronized E remove() {
		/*7.11 ����*/
		E item;
		while(count == 0) {
			try {
				System.out.println("Removing item is waiting for the empty buffer.");
				wait();
			}
			catch (InterruptedException ie) {}
		}
		
		item = buffer[out];
		
		System.out.println("Item " + (int)item + " has been removed from index " + out + ".");
		
		out = (out + 1) % BUFFER_SIZE;
		count--;
		
		System.out.println("Notify() has been called in the remove().");
		System.out.println("");
		notify();
		
		return item;
	}
}
