package com.wql_2020211597.app;

import java.util.Properties;
import org.apache.flink.api.common.eventtime.WatermarkStrategy;
import org.apache.flink.api.common.functions.FlatMapFunction;
import org.apache.flink.api.common.serialization.SimpleStringSchema;
import org.apache.flink.api.java.tuple.Tuple2;
import org.apache.flink.connector.kafka.source.KafkaSource;
import org.apache.flink.connector.kafka.source.enumerator.initializer.OffsetsInitializer;
import org.apache.flink.streaming.api.datastream.DataStream;
import org.apache.flink.streaming.api.environment.StreamExecutionEnvironment;
import org.apache.flink.util.Collector;

/**
 * Hello world!
 *
 */
public class FlinkKafka {
    static private String master_hostname = "wql-2020211597-0004";

    public static void main(String[] args) throws Exception {
        // Get Flink running environment
        StreamExecutionEnvironment env =
                StreamExecutionEnvironment.getExecutionEnvironment();

        // Configure Kafka connection properties
        Properties properties = new Properties();
        properties.setProperty("bootstrap.servers", master_hostname + ":9092");
        // properties.setProperty("zookeeper.connect", master_hostname +
        // ":2181");
        properties.setProperty("group.id", "1");

        KafkaSource<String> myKafkaSource = KafkaSource.<String>builder()
                .setBootstrapServers(master_hostname + ":9092").setGroupId("1")
                .setTopics("test")
                .setValueOnlyDeserializer(new SimpleStringSchema())
                .setStartingOffsets(OffsetsInitializer.earliest()).build();

        // Add source to environment
        DataStream<String> dataStream = env.fromSource(myKafkaSource,
                WatermarkStrategy.noWatermarks(), "KafkaSource");

        // Perform operations on DataStreamnullull,properts
        DataStream<Tuple2<String, Integer>> result =
                dataStream.flatMap(new MyFlatMapper()).keyBy(0).sum(1);

        // Print result
        result.print().setParallelism(1);

        // Execute job
        env.execute();
    }

    public static class MyFlatMapper
            implements FlatMapFunction<String, Tuple2<String, Integer>> {
        @Override
        public void flatMap(String s, Collector<Tuple2<String, Integer>> out) {
            String[] words = s.split(" ");
            for (String word : words) {
                out.collect(new Tuple2<String, Integer>(word, 1));
            }
        }
    }
}
