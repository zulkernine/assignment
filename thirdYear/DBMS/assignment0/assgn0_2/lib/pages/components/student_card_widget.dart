import 'package:assgn0_1/dao/student_dao.dart';
import 'package:assgn0_1/models/student.dart';
import 'package:assgn0_1/pages/components/department_info_widget.dart';
import 'package:assgn0_1/pages/edit_student.dart';
import 'package:flutter/material.dart';

class StudentCardWidget extends StatelessWidget {
  const StudentCardWidget({Key? key, required this.student}) : super(key: key);
  final Student student;

  @override
  Widget build(BuildContext context) {
    return Card(
      child: Container(
          padding: const EdgeInsets.all(12),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              Row(
                children: [
                  const Text("Name: "),
                  Text(
                    student.name,
                    style: Theme.of(context)
                        .textTheme
                        .bodyText1
                        ?.apply(fontSizeFactor: 1.2),
                  ),
                  const Spacer(),
                  Text("Roll- ${student.roll}"),
                ],
              ),
              const SizedBox(
                height: 8,
              ),
              DepartmentInfoWidget(deptCode: student.deptCode),
              const SizedBox(
                height: 8,
              ),
              RichText(
                  text: TextSpan(
                      style: Theme.of(context).textTheme.bodyText2,
                      children: [
                    const TextSpan(text: "Phone: "),
                    TextSpan(
                        text: student.phone,
                        style: Theme.of(context).textTheme.bodyText1)
                  ])),
              const SizedBox(
                height: 8,
              ),
              RichText(
                  text: TextSpan(
                      style: Theme.of(context).textTheme.bodyText2,
                      children: [
                    const TextSpan(text: "Address: "),
                    TextSpan(
                        text: student.address,
                        style: Theme.of(context).textTheme.bodyText2)
                  ])),
              const SizedBox(
                height: 24,
              ),
              Row(
                mainAxisAlignment: MainAxisAlignment.end,
                children: [
                  TextButton(
                      onPressed: () async {
                        bool shouldRemove = (await showDialog<bool>(
                                context: context,
                                builder: (_) => AlertDialog(
                                      title: Text(
                                        "Remove Student",
                                        style: Theme.of(context)
                                            .textTheme
                                            .bodyText1
                                            ?.copyWith(
                                                color: Theme.of(context)
                                                    .colorScheme
                                                    .error),
                                      ),
                                      content: Text(
                                        "Are you sure you want to remove the student: ${student.name}?",
                                        style: Theme.of(context)
                                            .textTheme
                                            .bodyText1,
                                      ),
                                      actions: [
                                        TextButton(
                                            onPressed: () {
                                              Navigator.pop(_,false);
                                            },
                                            child: const Text("No")),
                                        const SizedBox(
                                          width: 12,
                                        ),
                                        TextButton(
                                            onPressed: () {
                                              Navigator.pop(_,true);
                                            },
                                            child: const Text("Yes")),
                                      ],
                                    ))) ??
                            false;

                        if (shouldRemove) StudentDao.remove(student);
                      },
                      child: Text(
                        "Delete",
                        style: Theme.of(context).textTheme.button?.copyWith(
                            color: Theme.of(context).colorScheme.error),
                      )),
                  const SizedBox(
                    width: 12,
                  ),
                  OutlinedButton(
                      onPressed: () {
                        Navigator.push(context, MaterialPageRoute(builder: (context)=>EditStudentWidget(student: student,)));
                      },
                      child: const Text(
                        "Edit",
                      ))
                ],
              )
            ],
          )),
    );
  }
}
