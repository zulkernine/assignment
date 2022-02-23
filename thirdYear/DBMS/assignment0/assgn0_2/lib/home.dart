import 'dart:async';

import 'package:assgn0_1/dao/app_events.dart';
import 'package:assgn0_1/dao/student_dao.dart';
import 'package:assgn0_1/pages/add_user_widget.dart';
import 'package:assgn0_1/pages/search_page_widget.dart';
import 'package:assgn0_1/pages/view_all_student.dart';
import 'package:flutter/material.dart';

class HomePage extends StatefulWidget {
  const HomePage({Key? key}) : super(key: key);

  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  late StreamSubscription subp1;
  @override
  void initState() {
    subp1 = appEventBus.on<StudentEvents>().listen((event)=>setState(() {}));
    super.initState();
  }

  @override
  void dispose() {
    subp1.cancel();
    super.dispose();
  }

  int index=0;

  selectDestination(int i) => setState(() {index=i;});

  @override
  Widget build(BuildContext context) {
    return Container(
        child: Row(
      children: [
        Drawer(
          child: ListView(
            // Important: Remove any padding from the ListView.
            padding: EdgeInsets.zero,
            children: <Widget>[
              Padding(
                padding: const EdgeInsets.all(16.0),
                child: Text(
                  'Actions',
                  style: Theme.of(context).textTheme.headline6,
                ),
              ),
              const Divider(
                height: 1,
                thickness: 1,
              ),
              ListTile(
                leading: const Icon(Icons.search),
                title: const Text('Search'),
                selected: index==0,
                onTap: () => selectDestination(0),
              ),
              ListTile(
                leading: const Icon(Icons.add),
                title: const Text('Add new'),
                selected: index==1,
                onTap: () => selectDestination(1),
              ),
              ListTile(
                leading: const Icon(Icons.ballot_outlined),
                title: const Text('View all'),
                selected: index==2,
                onTap: () => selectDestination(2),
              ),
            ],
          ),
        ),
        const VerticalDivider(
          width: 1,
          thickness: 1,
        ),
        Expanded(
          child: [
            StudentSearchPageWidget(),
            const AddUserWidget(),
            ViewAllStudent(
              studentList: StudentDao.studentList.values.toList(),
            ),
          ].elementAt(index),
        )
      ],
    ));
  }
}
