import 'package:assgn0_1/dao/student_dao.dart';
import 'package:assgn0_1/models/student.dart';
import 'package:assgn0_1/pages/components/student_card_widget.dart';
import 'package:flutter/material.dart';

class ViewAllStudent extends StatelessWidget {
  final List<Student> studentList;
  const ViewAllStudent({Key? key, required this.studentList}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Container(
      padding: const EdgeInsets.all(16),
      child: ListView.separated(
          itemBuilder: (context, index) {
            return StudentCardWidget(
              student: studentList.elementAt(index),
            );
          },
          separatorBuilder: (context, i) {
            return const SizedBox(
              height: 16,
            );
          },
          itemCount: studentList.length),
    );
  }
}
