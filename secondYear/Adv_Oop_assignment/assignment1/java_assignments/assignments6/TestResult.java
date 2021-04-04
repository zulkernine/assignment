package java_assignments.assignments6;
import java.time.LocalDateTime;

public class TestResult {
    String testName;
    String value;
    String unit;

    String recordTime;

    TestResult(String name,String val,String u){
        testName = name;
        value = val;
        unit = u;
        recordTime = LocalDateTime.now().toString();
    }

    @Override
    public String toString() {
        return (recordTime+"\t"+testName+"\t"+value+"\t"+recordTime);
    }
}
