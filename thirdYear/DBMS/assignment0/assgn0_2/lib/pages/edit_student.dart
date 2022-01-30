import 'package:assgn0_1/dao/department_dao.dart';
import 'package:assgn0_1/dao/student_dao.dart';
import 'package:assgn0_1/models/department.dart';
import 'package:assgn0_1/models/student.dart';
import 'package:flutter/material.dart';

class EditStudentWidget extends StatefulWidget {
  final Student student;
  const EditStudentWidget({Key? key,required this.student}) : super(key: key);

  @override
  _EditStudentWidgetState createState() => _EditStudentWidgetState();
}

class _EditStudentWidgetState extends State<EditStudentWidget> {
  late Student _localStudent;
  final _formKey = GlobalKey<FormState>();

  @override
  void initState() {
    _localStudent = Student.from(widget.student);

    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Container(
        padding: const EdgeInsets.all(16),
        child: Form(
          autovalidateMode: AutovalidateMode.onUserInteraction,
          key: _formKey,
          child: Column(

            children: [
              TextFormField(
                enabled: false,
                initialValue: _localStudent.roll.toString(),
                decoration: const InputDecoration(
                  icon: Icon(Icons.edit),
                  labelText: 'Roll',
                ),
              ),
              TextFormField(
                initialValue: _localStudent.name,
                onChanged: (text){
                  setState(() {
                    _localStudent.name = text;
                  });
                },
                validator: (value) {
                  if ((value?.trim().length??0) < 3) {
                    return 'Enter a valid name';
                  }
                  return null;
                },
                decoration: const InputDecoration(
                  icon:  Icon(Icons.person),
                  hintText: 'Enter your name',
                  labelText: 'Name',
                ),
              ),
              TextFormField(
                initialValue: _localStudent.phone,
                onChanged: (text){
                  setState(() {
                    _localStudent.phone = text;
                  });
                },
                validator: (value) {
                  if ((value?.trim().length??0) != 10 ) {
                    return 'Enter a valid phone number';
                  }
                  return null;
                },
                decoration: const InputDecoration(
                  icon: Icon(Icons.phone),
                  hintText: 'Enter a phone number',
                  labelText: 'Phone',
                ),
              ),
              FormField<String>(
                builder: (FormFieldState<String> state) {
                  return InputDecorator(
                    decoration: const InputDecoration(
                      icon: Icon(Icons.book_outlined),
                        errorStyle: TextStyle(color: Colors.redAccent, fontSize: 16.0),
                        hintText: 'Please select department',),
                    isEmpty: _localStudent.deptCode == '',
                    child: DropdownButtonHideUnderline(
                      child: DropdownButton<String>(
                        value: _localStudent.deptCode,
                        isDense: true,
                        onChanged: (String? newValue) {
                          if(newValue!=null) {
                            setState(() {
                            _localStudent.deptCode = newValue;
                            state.didChange(newValue);
                          });
                          }
                        },
                        items: DepartmentDao.departments.values.map((Department d) {
                          return DropdownMenuItem<String>(
                            value: d.deptCode,
                            child: Text(d.name),
                          );
                        }).toList(),
                      ),
                    ),
                  );
                },
              ),
              TextFormField(
                initialValue: _localStudent.address,
                onChanged: (text){
                  setState(() {
                    _localStudent.address = text;
                  });
                },
                validator: (value) {
                  if ((value?.trim().length??0)<10) {
                    return 'Enter a valid address';
                  }
                  return null;
                },
                decoration: const InputDecoration(
                  icon: Icon(Icons.calendar_today),
                  hintText: 'Enter your full address',
                  labelText: 'Address',
                ),
              ),
              const Spacer(),
              Padding(
                padding: const EdgeInsets.symmetric(vertical: 16.0),
                child: Row(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: [
                    OutlinedButton(onPressed: (){
                      Navigator.pop(context);
                    }, child: const Text("Cancel")),
                    const SizedBox(width: 12,),
                    ElevatedButton(onPressed: (){
                      if(_formKey.currentState?.validate()??false){
                        StudentDao.update(_localStudent);
                        Navigator.pop(context);
                      }

                    }, child: const Text("Save")),
                  ],
                ),
              )
            ],
          ),
        ),
      ),
    );
  }
}
