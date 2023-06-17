package org.wql2020211597.hbase.inputSource;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.hbase.HBaseConfiguration;
import org.apache.hadoop.hbase.client.Scan;
import org.apache.hadoop.hbase.util.Bytes;
import org.apache.hadoop.hbase.mapreduce.TableMapReduceUtil;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;

/**
 * Take HBase as input source, read data from HBase table; Use MapReduce to
 * compute, then store result data into HDFS.
 */
public class Main {
    static final Log LOG = LogFactory.getLog(Main.class);

    // Job name
    public static final String NAME = "Member Test1";
    // Output directory
    public static final String TEMP_INDEX_PATH =
            "hdfs://wql-2020211597-0004:8020/tmp/member_user";
    // HBase table "2020211597-吴清柳" as input source
    public static String inputTable = "2020211597-吴清柳";

    public static void main(String[] args) throws Exception {
        // Step 1. Get HBase configuration
        Configuration conf = HBaseConfiguration.create();

        // Step 2. Create whole table scanner object
        Scan scan = new Scan();
        scan.setBatch(0);
        scan.setCaching(10000);
        scan.readAllVersions();
        scan.setTimeRange(System.currentTimeMillis() - 3 * 24 * 3600 * 1000L,
                System.currentTimeMillis());

        // Add scan rule, column group and column group name
        scan.addColumn(Bytes.toBytes("cf1"),
                Bytes.toBytes("a"));

        // Set HDFS storage execution behavior to false
        conf.setBoolean("mapred.map.tasks.speculative.execution", false);
        conf.setBoolean("mapred.reduce.tasks.speculative.execution", false);
        Path tmpIndexPath = new Path(TEMP_INDEX_PATH);
        FileSystem fs = FileSystem.get(conf);

        // Test if the path exists. Delete if it already exists.
        if (fs.exists(tmpIndexPath)) {
            fs.delete(tmpIndexPath, true);
        }

        // Create job object
        Job job = Job.getInstance(conf, NAME);
        job.setJarByClass(Main.class);

        /**
         * Set related information for TableMapper class. That is, initialize
         * mapper class's following configurations: ( hbase inputSource
         * corresponding table, scanner, Computation method, Output type, Output
         * value type, Job)
         */
        TableMapReduceUtil.initTableMapperJob(inputTable, scan,
                MemberMapper.class, Text.class, Text.class, job);

        job.setNumReduceTasks(0);

        // Set the result computed by Mapreduce from HBase table output format
        // to Text
        job.setOutputFormatClass(TextOutputFormat.class);

        // Set file path of job output result in HDFS
        FileOutputFormat.setOutputPath(job, tmpIndexPath);

        // Begin job
        boolean success = job.waitForCompletion(true);

        System.exit(success ? 0 : 1);

    }

}
