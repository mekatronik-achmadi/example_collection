import 'package:flutter/material.dart';
import 'package:english_words/english_words.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
        title: 'My Flutter App',
        theme: ThemeData(primarySwatch: Colors.blue),
        home: MyHomeApp(title: 'My Home App'));
  }
}

class MyHomeApp extends StatefulWidget {
  MyHomeApp({Key key, this.title}) : super(key: key);
  final String title;

  @override
  _MyHomeAppState createState() => _MyHomeAppState();
}

class _MyHomeAppState extends State<MyHomeApp> {
  var _kata = WordPair.random();

  void _increCounter() {
    setState(() {
      _kata = WordPair.random();
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: Center(
          child: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        children: <Widget>[Text('Pushed Button'), Text(_kata.asPascalCase)],
      )),
      floatingActionButton: FloatingActionButton(
        onPressed: _increCounter,
        child: Icon(Icons.add),
      ),
    );
  }
}
