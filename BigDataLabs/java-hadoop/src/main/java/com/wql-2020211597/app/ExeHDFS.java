import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.URI;
import java.net.URISyntaxException;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FSDataOutputStream;
import org.apache.hadoop.fs.FileStatus;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IOUtils;
import org.apache.log4j.BasicConfigurator;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;
import org.apache.hadoop.util.ShutdownHookManager;

public class ExeHDFS {
    static String hdfsPath = "/";
    static String nodeMasterIP = "116.204.88.20";
    static String studentID = "2020211597";
    static String studentName = "吴清柳";

    private static final Logger parentLogger = LogManager.getLogger("ExeHDFS");
    private Logger logger = parentLogger;

    protected Logger getLogger() {
        return logger;
    }

    protected void setLogger(Logger logger) {
        this.logger = logger;
    }

    public static void main(String[] args) {
        BasicConfigurator.configure();
        ExeHDFS testHDFS = new ExeHDFS();
        System.setProperty("hadoop.home.dir", hdfsPath);
        System.setProperty("hadoop.root.logger", "INFO,ExeHDFS");
        System.out.println("In ExeHDFS");
        try {
            testHDFS.testView();
            testHDFS.testUpload();
            testHDFS.testCreate();
            testHDFS.testDownload();
            testHDFS.testView();
        } catch (Exception e) {
            // e.printStackTrace();
            System.err.printf(e.getMessage());
        }
    }

    // 查看 HDFS 文件系统
    public void testView() throws IOException, URISyntaxException,
            InterruptedException {
        String fsURL = "hdfs://" + nodeMasterIP + ":8020";
        System.out.println("View file:");
        Configuration conf = new Configuration();
        conf.set("dfs.client.use.datanode.hostname", "true");
        conf.set("fs.defaultFS", fsURL);
        try {
            FileSystem hdfs = FileSystem.get(new URI("hdfs://" + nodeMasterIP), conf,
                    "micuks");
            Path path = new Path(hdfsPath);
            FileStatus[] list = hdfs.listStatus(path);
            if (list.length == 0) {
                System.out.println("==============");
                System.out.println("HDFS is empty.");
                System.out.println("==============");
            } else {
                for (FileStatus f : list) {
                    System.out.println("================================");
                    System.out.printf("name: %s, folder: %s, size: %d\n", f.getPath(),
                            f.isDirectory(), f.getLen());
                    System.out.println("================================");
                }
            }
            hdfs.close();
        } catch (Exception e) {
            // e.printStackTrace();
            System.err.printf(e.getMessage());
        }

    }

    // 上传本地文件到 HDFS
    public void testUpload() throws IOException, URISyntaxException,
            InterruptedException {
        System.out.println("Upload file:");
        Configuration conf = new Configuration();
        logger.info("Current working directory[" + System.getProperty("user.dir") + "]");
        conf.set("dfs.client.use.datanode.hostname", "true");
        conf.set("fs.defaultFS", "hdfs://" + nodeMasterIP + ":8020");
        FileSystem hdfs = FileSystem.get(new URI("hdfs://" + nodeMasterIP), conf,
                "micuks");

        InputStream in = new FileInputStream("./upload.txt");
        OutputStream out = hdfs.create(new Path(hdfsPath + "upload_" + studentID +
                ".txt"));
        IOUtils.copyBytes(in, out, conf);
        System.out.println("Upload successfully!");
        hdfs.close();
    }

    // 创建 HDFS 文件
    public void testCreate() throws Exception {
        System.out.println("Write file:");
        Configuration conf = new Configuration();
        conf.set("dfs.client.use.datanode.hostname", "true");
        conf.set("fs.defaultFS", "hdfs://" + nodeMasterIP + ":8020");
        // 写入自己姓名与学号
        String buffStr = "Hello world! Myname is " + studentName + ", my student id is " + studentID + ".";
        byte[] buff = buffStr.getBytes();

        // FileSystem 为 HDFS 的 API, 通过此调用 HDFS
        FileSystem hdfs = FileSystem.get(new URI("hdfs://" + nodeMasterIP), conf,
                "micuks");

        // 文件目标路径，应填写 hdfs 文件路径
        Path dst = new Path(hdfsPath + "wql_" + studentID + ".txt");
        FSDataOutputStream outputStream = null;
        try {
            // 写入文件
            outputStream = hdfs.create(dst);
            outputStream.write(buff, 0, buff.length);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            if (outputStream != null) {
                outputStream.close();
            }
        }
        // 检查文件写入情况
        FileStatus files[] = hdfs.listStatus(dst);
        for (FileStatus file : files) {
            // 打印写入文件路径及名称
            System.out.println(file.getPath());
        }
        hdfs.close();
    }

    // 从 HDFS 下载文件到本地
    public void testDownload() throws IOException, URISyntaxException,
            InterruptedException {
        System.out.println("Download file:");
        Configuration conf = new Configuration();
        conf.set("dfs.client.use.datanode.hostname", "true");
        conf.set("fs.defaultFS", "hdfs://" + nodeMasterIP + ":8020");
        FileSystem hdfs = FileSystem.get(new URI("hdfs://" + nodeMasterIP), conf,
                "micuks");

        InputStream in = hdfs.open(new Path(hdfsPath + "wql_" + studentID + ".txt"));
        OutputStream out = new FileOutputStream("./download_" + studentID + ".txt");
        IOUtils.copyBytes(in, out, conf);
        System.out.println("Download successfully!");
        hdfs.close();
    }
}
