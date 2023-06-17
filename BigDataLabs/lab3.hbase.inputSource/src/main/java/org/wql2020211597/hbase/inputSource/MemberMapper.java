package org.wql2020211597.hbase.inputSource;

import org.apache.hadoop.hbase.Cell;
import org.apache.hadoop.hbase.client.Result;
import org.apache.hadoop.hbase.io.ImmutableBytesWritable;
import org.apache.hadoop.hbase.mapreduce.TableMapper;
import org.apache.hadoop.hbase.util.Bytes;
import org.apache.hadoop.io.Writable;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.io.Text;
import java.io.IOException;

/**
 * Take Hbase table as input source Extended from class TableMapper. All classes using HBase as
 * input source is required to extend inherent class.
 */
public class MemberMapper extends TableMapper<Writable, Writable> {
    private Text k = new Text();
    private Text v = new Text();
    public static final String FIELD_COMMON_seperator = "\u0001";

    @Override
    protected void setup(Context context)
            throws IOException, InterruptedException {}

    @Override
    protected void map(ImmutableBytesWritable row, Result columns,
            Mapper<ImmutableBytesWritable, Result, Writable, Writable>.Context context)
            throws IOException, InterruptedException {
        String value = null;
        // Get row key
        String rowkey = new String(row.get());

        // All row groups in a row
        byte[] columnFamily = null;
        // All column names in one row
        byte[] columnQualifier = null;
        long ts = 0L;

        try {
            for (Cell cell : columns.listCells()) {
                // Value of cell
                value = Bytes.toStringBinary(cell.getValueArray());

                // Get all ColumnGroups of one row
                columnFamily = cell.getFamilyArray();

                // Get all column names of one row
                columnQualifier = cell.getQualifierArray();

                // Get cell timestamp
                ts = cell.getTimestamp();

                k.set(rowkey);
                v.set(Bytes.toString(columnFamily) + FIELD_COMMON_seperator
                        + Bytes.toString(columnQualifier)
                        + FIELD_COMMON_seperator + value
                        + FIELD_COMMON_seperator + ts);
                context.write(k, v);
            }
        } catch (Exception e) {
            e.printStackTrace();
            System.err.println("Error: " + e.getMessage() + ", Row: "
                    + Bytes.toString(row.get()) + ", Value " + value);
        }
    }
}
