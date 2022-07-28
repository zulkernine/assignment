package org.zulqarnain;

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
			log.warn(e.getMessage());
		}
	}

	private static void run() {
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
				log.info( "Topic: " + record.topic());
				log.info(record.headers().toString());
			});

			producer.flush();

		}

	}
}