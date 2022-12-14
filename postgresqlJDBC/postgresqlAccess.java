import java.sql.*;
/**
 * postgresqlAccess
 */
import java.util.Properties;

import org.postgresql.util.PSQLException;

public class postgresqlAccess {

    static final String JDBC_DRIVER = "org.postgresql.Driver";
    static String url = "jdbc:postgresql://localhost:11597/postgres";
    static Properties props = new Properties();
    static Connection conn = null;
    static Statement stmt = null;
    static ResultSet rs = null;

    private static void printQueryResult() throws SQLException {
        while (rs.next()) {
            int nationkey = rs.getInt("n_nationkey");
            String name = rs.getString("n_name");
            int regionkey = rs.getInt("n_regionkey");
            String comment = rs.getString("n_comment");

            System.out.printf("%-5d %-15s %-5d %s\n", nationkey, name.trim(), regionkey, comment);
        }
    }

    public static void queryNation() throws SQLException {
        // Execute query.
        String sql;
        sql = "select n_nationkey, n_name, n_regionkey, n_comment from nation";
        rs = stmt.executeQuery(sql);
        System.out.println("Nationkey name regionkey commnet\n");

        // 展开结果集数据库
        printQueryResult();
    }

    /**
     * Insert a tuple into table Nation.
     * - n_nationkey=25, n_name='South Korea', n_regionkey=3.
     * 
     * The corresponding SQL query is
     * ```
     * insert into nation
     * values(
     * 25,
     * 'South Korea',
     * 3,
     * 'Record inserted from JDBC.'
     * )
     * ```
     * 
     * @throws SQLException
     */
    public static void insertToNation() throws SQLException {
        String sql;
        sql = "insert into nation values(25, 'South Korea', 3, 'Record inserted from JDBC.')";
        try {
            rs = stmt.executeQuery(sql);
        } catch (PSQLException e) {
            System.err.println(e.getClass().getName() + ": " + e.getMessage());
        }
        System.out.println("Insert value statement executed.");

        insertResult();
    }

    public static void insertResult() throws SQLException {
        System.out.println("Check if inserted successfully.");
        String sql = "select * from nation where n_nationkey=25";
        rs = stmt.executeQuery(sql);
        // Print query reqult.
        printQueryResult();
    }

    /**
     * Update the record inserted in last step.
     * 
     * @exception SQLException
     */
    public static void updateNation() throws SQLException {
        String sql;
        sql = "update nation set n_regionkey=2 where n_nationkey=25";
        try {
            rs = stmt.executeQuery(sql);
        } catch (Exception e) {
            System.err.println(e.getClass().getName() + ": " + e.getMessage());
        }

        // Print update result.
        System.out.println("Print updated record.");
        sql = "select * from nation where n_nationkey=25";
        try {
            rs = stmt.executeQuery(sql);
        } catch (Exception e) {
            System.err.println(e.getClass().getName() + ": " + e.getMessage());
        }
        printQueryResult();
    }

    /**
     * Delete the record inserted, and check if successfully delted via n_nationkey.
     * SQL statement:
     * delete from nation
     * where n_nationkey=25;
     * 
     * select * from nation
     * where n_nationkey=25;
     * 
     * @throws SQLException
     */
    public static void deleteRecord() throws SQLException {
        String sql;
        sql = "delete from nation where n_nationkey=25;";
        try {
            rs = stmt.executeQuery(sql);
        } catch (Exception e) {
            System.err.println(e.getClass().getName() + ": " + e.getMessage());
        }

        System.out.println("Check if the record is deleted successfully.");
        sql = "select count(*) from nation where n_nationkey=25";
        try {
            rs = stmt.executeQuery(sql);
        } catch (Exception e) {
            System.err.println(e.getClass().getName() + ": " + e.getMessage());
        }
        rs.next();
        int count = rs.getInt(1);
        System.out.println("Number of records with n_nationkey=25: " + count);
        printQueryResult();
    }

    public static void main(String[] args) throws SQLException {
        props.setProperty("user", "gaussdb");
        props.setProperty("password", "Wql@2020211597");
        props.setProperty("ssl", "false");
        try {
            Class.forName(JDBC_DRIVER);
            conn = DriverManager.getConnection(url, props);
            System.out.println("Opened database successfully.");
            System.out.println("Instantiate Statement object");
            stmt = conn.createStatement();

            // Query operation.
            // queryNation();

            // Insert operation.
            // insertToNation();

            // Update operation.
            // updateNation();

            // Delete record.
            deleteRecord();

            // Close after finished.
            rs.close();
            stmt.close();
            conn.close();
        } catch (SQLException e) {
            e.printStackTrace();
        } catch (Exception e) {
            System.err.println(e.getClass().getName() + ": " + e.getMessage());
            System.exit(0);
        } finally {
            // Close resources.
            try {
                if (stmt != null) {
                    stmt.close();
                }
            } catch (SQLException e) {
                System.err.println(e.getClass().getName() + ": " + e.getMessage());
            }
            try {
                if (conn != null) {
                    conn.close();
                }
            } catch (SQLException e) {
                System.err.println(e.getClass().getName() + ": " + e.getMessage());
            }
        }
    }
}