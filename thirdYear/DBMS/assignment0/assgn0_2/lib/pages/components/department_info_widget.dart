import 'package:assgn0_1/dao/department_dao.dart';
import 'package:assgn0_1/models/department.dart';
import 'package:flutter/material.dart';

class DepartmentInfoWidget extends StatelessWidget {
  const DepartmentInfoWidget({Key? key, required this.deptCode}) : super(key: key);
  final String deptCode;

  @override
  Widget build(BuildContext context) {
    Department? dept = DepartmentDao.departments[deptCode];
    if (dept == null) return const SizedBox.shrink();

    return Row(
      children: [
        Text("Code: ${dept.deptCode}"),
        const SizedBox(
          width: 12,
        ),
        const Text("Dept. Name- "),
        Text(
          dept.name,
          style: Theme.of(context).textTheme.bodyText1,
        )
      ],
    );
  }
}
