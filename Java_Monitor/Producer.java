import java.util.Random;

public class Producer {
	private int _of_insertion;
	private int max_sleep_time_for_producers;
	@SuppressWarnings("rawtypes")
	private BoundedBuffer boundedbuffer;
	private int number_of_producer;
	
	int sleep;
	int item;
	
	
	@SuppressWarnings("rawtypes")
	public Producer(int number_of_producer, int _of_insertion, int max_sleep_time_for_producers, BoundedBuffer boundedbuffer) {
		this.number_of_producer = number_of_producer;
		this._of_insertion = _of_insertion;
		this.max_sleep_time_for_producers = max_sleep_time_for_producers;
		this.boundedbuffer = boundedbuffer;
	}
	
	@SuppressWarnings("unchecked")
	public void run_producer() throws InterruptedException {
		for(int i = 0; i < this._of_insertion; i++) {
		Random random = new Random();
		
		sleep = random.nextInt(this.max_sleep_time_for_producers) + 1;
		
		System.out.println("P" + this.number_of_producer + " starts sleeping " + sleep + "ms.");
		
		Thread.sleep(sleep);
		
		item = random.nextInt(101);
		
		this.boundedbuffer.insert(item);
		
		System.out.println("P" + this.number_of_producer + " inserts item " + item + ".");
		}
	}
}
