import 'dart:async';
import 'package:intl/intl.dart';
import 'package:bitsdojo_window/bitsdojo_window.dart';
import 'package:flutter/material.dart';


final buttonColors = WindowButtonColors(
    iconNormal: Color(0xFFE8D5B3),
    mouseOver: Color(0xFFF6A00C),
    mouseDown: Color(0xFF805306),
    iconMouseOver: Color(0xFFF6E6C9),
    iconMouseDown: Color(0xFFFFD500));

final closeButtonColors = WindowButtonColors(
    mouseOver: Color(0xFFD32F2F),
    mouseDown: Color(0xFFB71C1C),
    iconNormal: Color(0xFFC11A41),
    iconMouseOver: Colors.white);

class WindowButtons extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Row(
      children: [
        MinimizeWindowButton(colors: buttonColors),
        MaximizeWindowButton(colors: buttonColors),
        CloseWindowButton(colors: closeButtonColors),
      ],
    );
  }
}

class CurrentDateTimeWidget extends StatefulWidget {
  const CurrentDateTimeWidget({Key? key}) : super(key: key);

  @override
  _CurrentDateTimeWidgetState createState() => _CurrentDateTimeWidgetState();
}

class _CurrentDateTimeWidgetState extends State<CurrentDateTimeWidget> {

  late String _timeString;

  @override
  void initState() {
    _timeString='';
    super.initState();
    Timer.periodic(Duration(seconds: 1), (Timer t) => _getTime());
  }

  void _getTime() {
    final String formattedDateTime = DateFormat('yyyy-MM-dd | kk:mm:ss').format(DateTime.now()).toString();
    setState(() {
      _timeString = formattedDateTime;
      print(_timeString);
    });
  }

  @override
  Widget build(BuildContext context) {
    return Text("($_timeString)",style: Theme.of(context).textTheme.bodyText1?.copyWith(color: Theme.of(context).colorScheme.onPrimary),);
  }
}

