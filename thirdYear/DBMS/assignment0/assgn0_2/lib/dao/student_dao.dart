import 'package:assgn0_1/dao/app_events.dart';
import 'package:assgn0_1/models/student.dart';

enum StudentEvents{ STUDENT_REMOVED,STUDENT_ADDED,STUDENT_UPDATED}

class StudentDao {
  static Map<int, Student> studentList = {
    312001: Student(
        roll: 312001,
        deptCode: "CSE01A",
        name: "Neeladri Pal",
        phone: "9872346570",
        address: "1A, Rajbihari road,Asansol-732432"),
    312002: Student(
        roll: 312002,
        deptCode: "ETC022",
        name: "Avik Kumar",
        phone: "7652346570",
        address: "1A, Rajbihari road,Asansol-732432"),
    312003: Student(
        roll: 312003,
        deptCode: "CSE01B",
        name: "Poulami das",
        phone: "9682346570",
        address: "1A, Rajbihari road,Asansol-732432"),
    312004: Student(
        roll: 312004,
        deptCode: "CSE01A",
        name: "Mayukh Ghosh",
        phone: "8762346570",
        address: "1A, Rajbihari road,Asansol-732432"),
    312005: Student(
        roll: 312005,
        deptCode: "ETC022",
        name: "Arup Baral",
        phone: "9782346570",
        address: "1A, Rajbihari road,Asansol-732432"),
    312006: Student(
        roll: 312006,
        deptCode: "CSE01A",
        name: "Mayukhmali Sarkar",
        phone: "6751346570",
        address: "1A, Rajbihari road,Asansol-732432"),
    312007: Student(
        roll: 312007,
        deptCode: "CSE01B",
        name: "Afsdh dksjf",
        phone: "8709346570",
        address: "1A, Rajbihari road,Asansol-732432"),
    312008: Student(
        roll: 312008,
        deptCode: "IT011A",
        name: "Saptarshi Rakhsit",
        phone: "9734873472",
        address: "1A, Rajbihari road,Asansol-732432"),
    312009: Student(
        roll: 312009,
        deptCode: "CSE02C",
        name: "Sanmit mondal",
        phone: "8762346570",
        address: "1A, Rajbihari road,Asansol-732432"),
    312010: Student(
        roll: 312010,
        deptCode: "IT011A",
        name: "Soumita paul",
        phone: "9872346570",
        address: "1A, Rajbihari road,Asansol-732432"),
    312011: Student(
        roll: 312011,
        deptCode: "CSE02C",
        name: "Abit sarkar",
        phone: "7652346570 ",
        address: "1A, Rajbihari road,Asansol-732432"),
  };

  static void add(Student st){
    //TODO: implement addition
    appEventBus.fire(StudentEvents.STUDENT_ADDED);
  }
  static void remove(Student st){
    studentList.remove(st.roll);
    appEventBus.fire(StudentEvents.STUDENT_REMOVED);
  }
  static void update(Student st){
    studentList[st.roll] = Student.from(st);
    appEventBus.fire(StudentEvents.STUDENT_UPDATED);
  }

  static bool containsRoll(int roll){
    return studentList.containsKey(roll);
  }
}
