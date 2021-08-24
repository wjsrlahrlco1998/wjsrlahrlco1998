import java.util.Random;

public class Main {
	
	public static void run(Producer[] producer, Consumer[] consumer) throws InterruptedException {
		Random random = new Random();
		
		Thread t = new Thread(() -> {
			try {
				producer[random.nextInt(5)].run_producer();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		});
		
		t.setName("Producer");
		t.start();
		
		consumer[random.nextInt(5)].run_consumer();
		
		return;
		
	}

	@SuppressWarnings("rawtypes")
	public static void main(String[] args) {
		
		int _of_producers = 10;
		int _of_insertion = 20;
		int max_sleep_time_for_producers = 100;
		int _of_consumers = 10;
		int _of_remove = 20;
		int max_sleep_time_for_consumers = 100;
		
		
		BoundedBuffer boundedbuffer = new BoundedBuffer();
		
		Producer[] producer = new Producer[_of_producers];
		for(int i = 0; i < _of_producers; i++)
		{
			producer[i] = new Producer(i+1, _of_insertion, max_sleep_time_for_producers, boundedbuffer);
		}
		
		Consumer[] consumer = new Consumer[_of_consumers];
		for(int i = 0; i < _of_consumers; i++)
		{
			consumer[i] = new Consumer(i+1, _of_remove, max_sleep_time_for_consumers, boundedbuffer);
		}
		
		while(true)
		{
			try {
				Thread.sleep(1000);
				run(producer, consumer);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
}
