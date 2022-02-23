import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

class HomePage extends StatefulWidget {
  const HomePage({Key? key}) : super(key: key);

  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  int n1 = 0, n2 = 0;
  int result = 0;

  final TextEditingController _tec1 = TextEditingController(), _tec2 = TextEditingController();

  @override
  Widget build(BuildContext context) {
    return Center(
        child: Container(
            padding: const EdgeInsets.all(16),
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.center,
              children: [
                Row(
                  children: [
                    Expanded(
                      child: TextField(
                        controller: _tec1,
                        decoration: const InputDecoration(
                          border: OutlineInputBorder(),
                          labelText: 'First number',
                        ),
                        keyboardType: TextInputType.number,
                        inputFormatters: <TextInputFormatter>[FilteringTextInputFormatter.digitsOnly],
                        onChanged: (String text) {
                          try {
                            setState(() {
                              n1 = int.parse(text);
                            });
                          } catch (e) {
                            print(e);
                          }
                        },
                      ),
                    ),
                    const SizedBox(
                      width: 8,
                    ),
                    Expanded(
                      child: TextField(
                        controller: _tec2,
                        decoration: const InputDecoration(
                          border: OutlineInputBorder(),
                          labelText: 'Second number',
                        ),
                        keyboardType: TextInputType.number,
                        inputFormatters: <TextInputFormatter>[FilteringTextInputFormatter.digitsOnly],
                        onChanged: (String text) {
                          try {
                            setState(() {
                              n2 = int.parse(text);
                            });
                          } catch (e) {
                            print(e);
                          }
                        },
                      ),
                    ),
                  ],
                ),
                const SizedBox(
                  height: 16,
                ),
                Row(
                  children: [
                    Expanded(
                        child: OutlinedButton(
                            onPressed: () {
                              setState(() {
                                result = n1 + n2;
                              });
                            },
                            child: const Text("Add"))),
                    const SizedBox(
                      width: 8,
                    ),
                    Expanded(
                        child: OutlinedButton(
                            onPressed: () {
                              setState(() {
                                result = n1 - n2;
                              });
                            },
                            child: const Text("Subtract")))
                  ],
                ),
                const SizedBox(
                  height: 16,
                ),
                TextButton(
                    onPressed: () {
                      setState(() {
                        n1 = 0;
                        n2 = 0;
                        result = 0;
                        _tec1.text = '';
                        _tec2.text = '';
                      });
                    },
                    child: const Text("Reset")),
                const SizedBox(
                  height: 40,
                ),
                Text(
                  "Result: $result",
                  style: Theme.of(context).textTheme.headline6,
                ),
              ],
            )));
  }
}
