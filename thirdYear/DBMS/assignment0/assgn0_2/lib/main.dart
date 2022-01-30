import 'package:assgn0_1/common_widgets.dart';
import 'package:assgn0_1/home.dart';
import 'package:flutter/material.dart';
import 'package:bitsdojo_window/bitsdojo_window.dart';

void main() {
  runApp(RootApp());

  // Add this code below

  doWhenWindowReady(() {
    const initialSize = Size(800, 650);
    appWindow.minSize = initialSize;
    appWindow.size = initialSize;
    appWindow.alignment = Alignment.center;
    appWindow.title = "AddSubtract";
    appWindow.show();
  });
}

const borderColor = Color(0xFF805306);

class RootApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
        debugShowCheckedModeBanner: false,
        home: Scaffold(
            body: WindowBorder(
                color: borderColor,
                width: 1,
                child: Column(
                  crossAxisAlignment: CrossAxisAlignment.stretch,
                  children: [
                    WindowTitleBarBox(
                        child: Container(
                      decoration:
                          BoxDecoration(color: Theme.of(context).primaryColor),
                      child: Row(children: [
                        Expanded(
                            child: MoveWindow(
                          child: Row(
                            children: [
                              Padding(
                                padding:
                                    const EdgeInsets.symmetric(horizontal: 8.0),
                                child: Text(
                                  "Students' Data Manager",
                                  style: Theme.of(context)
                                      .textTheme
                                      .headline6
                                      ?.copyWith(
                                          color: Theme.of(context)
                                              .colorScheme
                                              .onPrimary),
                                ),
                              ),
                            ],
                          ),
                        )),
                        WindowButtons()
                      ]),
                    )),
                    const Expanded(
                        child: MaterialApp(
                      home: HomePage(),
                      debugShowCheckedModeBanner: false,
                    )),
                  ],
                )
                // Row(children: [LeftSide(), RightSide()])
                )));
  }
}
