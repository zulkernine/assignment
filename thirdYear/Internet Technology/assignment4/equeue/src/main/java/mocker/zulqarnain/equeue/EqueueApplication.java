package mocker.zulqarnain.equeue;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.data.mongodb.repository.config.EnableMongoRepositories;

@SpringBootApplication(scanBasePackages = "mocker.zulqarnain.*")
@EnableMongoRepositories("mocker.zulqarnain.repository")
public class EqueueApplication {

	public static void main(String[] args) {
		SpringApplication.run(EqueueApplication.class, args);
	}

}
