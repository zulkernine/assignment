package mocker.zulqarnain;

import com.google.api.client.googleapis.auth.oauth2.GoogleCredential;
import com.google.api.client.http.javanet.NetHttpTransport;
import com.google.api.client.json.gson.GsonFactory;
import com.google.api.services.oauth2.Oauth2;
import com.google.api.services.oauth2.model.Userinfo;
import java.io.IOException;
import java.security.GeneralSecurityException;
import java.util.Arrays;
import java.util.Properties;
import org.apache.kafka.clients.producer.KafkaProducer;
import org.apache.kafka.clients.producer.ProducerConfig;
import org.apache.kafka.clients.producer.ProducerRecord;
import org.apache.kafka.common.serialization.StringSerializer;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class Main {

	private static final Logger log = LoggerFactory.getLogger(Main.class);

	public static void main(String[] args) {
		log.info("Hello World");
		try {
			run();
		} catch (Exception e) {
			log.warn(e.getMessage() + "\n" + e);

			System.out.println(Arrays.toString(e.getStackTrace()));
		}
	}

	private static void run() throws GeneralSecurityException, IOException {
		final String CLIENT_ID = "469584027805-rtmuieaivahpqp757uo7ru3od11skavm.apps.googleusercontent.com";

		// (Receive idTokenString by HTTPS POST)
		String accessToken = "ya29.A0AVA9y1usH60ycQryhi4eilPyYy38rpD1IHctX05xxI83GbUlP09K3aBwo8rIbmjfkvxU5tRdoTVk3rUB_BhB_A0MJsVLgfywiQprbPtQ7CYYdfZBVNqJLFMicMW8HQZdnxqKi-QijrPb2pKeY4tkwGRb2m2XaCgYKATASATASFQE65dr8J71gF9ipx0dLTS0Bgc3OKg0163";

		GoogleCredential credential = new GoogleCredential().setAccessToken(accessToken);
//		GoogleCredentials credential = GoogleCredentials.create(new AccessToken(accessToken,null));
//		UserCredentials credential = UserCredentials.newBuilder()
//				.setAccessToken(new AccessToken(accessToken, null)).build();
		Oauth2 oauth2 = new Oauth2.Builder(new NetHttpTransport(), new GsonFactory(),
				credential).setApplicationName(
				"Oauth2").build();
		Userinfo userinfo = oauth2.userinfo().get().execute();
		log.info(userinfo.toPrettyString());
	}

	private static void run2() {
		//properties
		Properties properties = new Properties();
		properties.setProperty(ProducerConfig.BOOTSTRAP_SERVERS_CONFIG, "localhost:9092");
		properties.setProperty(ProducerConfig.KEY_SERIALIZER_CLASS_CONFIG,
				StringSerializer.class.getName());
		properties.setProperty(ProducerConfig.VALUE_SERIALIZER_CLASS_CONFIG,
				StringSerializer.class.getName());

		//create producer and close on completion
		try (KafkaProducer<String, String> producer = new KafkaProducer<>(properties)) {
			//producer record
			ProducerRecord<String, String> record = new ProducerRecord<>("first_topic",
					"metadata testing 4 :)");

			producer.send(record, (recordMetadata, e) -> {
				log.info("Topic: " + record.topic());
				log.info(record.headers().toString());
			});

			producer.flush();

		}

	}
}