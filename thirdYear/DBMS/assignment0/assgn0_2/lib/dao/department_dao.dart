import 'package:assgn0_1/models/department.dart';

class DepartmentDao {
  static Map<String, Department> departments = {
    "CSE01A": Department(name: "BCSE", deptCode: "CSE01A"),
    "CSE01B": Department(name: "MCSE", deptCode: "CSE01B"),
    "CSE02C": Department(name: "MCA", deptCode: "CSE02C"),
    "ETC022": Department(name: "ETCE", deptCode: "ETC022"),
    "IT011A": Department(name: "IT", deptCode: "IT011A"),
  };
}
