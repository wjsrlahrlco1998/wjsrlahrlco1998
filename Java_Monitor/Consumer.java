import java.util.Random;

public class Consumer {
	private int _of_remove;
	private int max_sleep_time_for_consumers;
	@SuppressWarnings("rawtypes")
	private BoundedBuffer boundedbuffer;
	private int number_of_consumer;
	
	int sleep;
	int item;
	
	@SuppressWarnings("rawtypes")
	public Consumer(int number_of_consumer, int _of_remove, int max_sleep_time_for_consumers, BoundedBuffer boundedbuffer) {
		this.number_of_consumer = number_of_consumer;
		this._of_remove = _of_remove;
		this.max_sleep_time_for_consumers = max_sleep_time_for_consumers;
		this.boundedbuffer = boundedbuffer;
	}
	
	public void run_consumer() throws InterruptedException {
		for(int i = 0; i < _of_remove; i++)
		{
			Random random = new Random();
			sleep = random.nextInt(this.max_sleep_time_for_consumers) + 1;
			
			System.out.println("C" + this.number_of_consumer + " starts sleeping " + sleep + "ms.");
			
			Thread.sleep(sleep);
			
			item = (int)this.boundedbuffer.remove();
			
			System.out.println("C" + this.number_of_consumer + " removes item " + item + ".");
		}
	}
}
