import 'package:assgn0_1/dao/student_dao.dart';
import 'package:assgn0_1/models/student.dart';
import 'package:assgn0_1/pages/edit_student.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

class AddUserWidget extends StatefulWidget {
  const AddUserWidget({Key? key}) : super(key: key);

  @override
  _AddUserWidgetState createState() => _AddUserWidgetState();
}

class _AddUserWidgetState extends State<AddUserWidget> {
  int roll = 0;
  final _formKey = GlobalKey<FormState>();

  @override
  Widget build(BuildContext context) {
    return Center(
      child: Form(
        key: _formKey,
        child: Column(
          mainAxisSize: MainAxisSize.min,
          children: [
            Padding(
              padding: const EdgeInsets.all(16.0),
              child: TextFormField(
                autovalidateMode: AutovalidateMode.onUserInteraction,
                validator: (value) {
                  if(value?.isEmpty??true) return null;

                  print("value: $value");
                  int r = int.parse(value!);
                  if (r <= 0 || StudentDao.containsRoll(r)) {
                    return "Invalid roll or it already exist!";
                  }

                  return null;
                },
                decoration: const InputDecoration(
                  hintText: 'New Roll Number',
                  hintStyle: TextStyle(
                    fontSize: 18,
                    fontStyle: FontStyle.italic,
                  ),
                ),
                keyboardType: TextInputType.number,
                inputFormatters: <TextInputFormatter>[
                  FilteringTextInputFormatter.digitsOnly
                ],
                onChanged: (text) {
                  setState(() {
                    roll = int.parse(text);
                  });
                },
              ),
            ),
            const SizedBox(
              height: 16,
            ),
            ElevatedButton(
                onPressed: () {
                  if (_formKey.currentState?.validate() ?? false) {
                    Navigator.push(
                        context,
                        MaterialPageRoute(
                            builder: (context) => EditStudentWidget(
                                student: Student.temp(roll))));
                  }
                },
                child: const Text("ADD"))
          ],
        ),
      ),
    );
  }
}
