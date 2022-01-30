import 'package:assgn0_1/dao/student_dao.dart';
import 'package:assgn0_1/models/student.dart';
import 'package:assgn0_1/pages/view_all_student.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

class StudentSearchPageWidget extends StatefulWidget {
  const StudentSearchPageWidget({Key? key}) : super(key: key);

  @override
  _StudentSearchPageWidgetState createState() => _StudentSearchPageWidgetState();
}

class _StudentSearchPageWidgetState extends State<StudentSearchPageWidget> {
  String searchText = '';

  List<Student> _getStudentsList() {
    if (searchText.isNotEmpty) {
      return StudentDao.studentList.values
          .toList()
          .where((element) => element.roll.toString() == (searchText))
          .toList();
    } else {
      return [];
    }
  }

  Widget _getEmptyWidget() {
    return Column(
      mainAxisAlignment: MainAxisAlignment.center,
      children: [
        Text(
          searchText.isNotEmpty ? "Entered roll doesn't exist" : "Please enter exact roll to search",
          style: Theme.of(context).textTheme.bodyText1,
        )
      ],
    );
  }

  Widget _getSearchField() {
    return ListTile(
      shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(12)),
      tileColor: const Color(0xffa8faf4),
      leading: const Icon(
        Icons.search,
        size: 28,
      ),
      title: TextField(
        decoration: const InputDecoration(
          hintText: 'Roll Number',
          hintStyle: TextStyle(
            fontSize: 18,
            fontStyle: FontStyle.italic,
          ),
          border: InputBorder.none,
        ),
        keyboardType: TextInputType.number,
        inputFormatters: <TextInputFormatter>[FilteringTextInputFormatter.digitsOnly],
        onChanged: (text) {
          setState(() {
            searchText = text;
          });
        },
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    List<Student> result = _getStudentsList();

    return Container(
      child: Column(
        // mainAxisSize: MainAxisSize.min,
        children: [
          Row(
            children: [
              Expanded(
                child: Padding(
                  padding: const EdgeInsets.symmetric(horizontal: 16.0, vertical: 24),
                  child: _getSearchField(),
                ),
              )
            ],
          ),
          Expanded(
            child: result.isEmpty
                ? _getEmptyWidget()
                : ViewAllStudent(
                    studentList: result,
                  ),
          )
        ],
      ),
    );
  }
}
