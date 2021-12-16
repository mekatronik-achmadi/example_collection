import 'package:flutter/material.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
        title: 'Flutter Demo', theme: ThemeData.dark(), home: HomePage());
  }
}

class HomePage extends StatefulWidget {
  @override
  _HomePageState createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  var _angkaDisplay = '0';
  double _angkaModif = 0;
  double _angkaSimpan = 0;
  int _modeOperasi = 0;

  void _tombolAngka(int _val) {
    if (_angkaModif == 0) {
      _angkaDisplay = '$_val';
    } else {
      _angkaDisplay = _angkaDisplay + '$_val';
    }
    _angkaModif = double.parse(_angkaDisplay);
  }

  void _tombolOperasi(int _op) {
    _modeOperasi = _op;
    _angkaSimpan = _angkaModif;
    _angkaDisplay = '0';
    _angkaModif = 0;
  }

  void _f0() {
    setState(() {
      _tombolAngka(0);
    });
  }

  void _f1() {
    setState(() {
      _tombolAngka(1);
    });
  }

  void _f2() {
    setState(() {
      _tombolAngka(2);
    });
  }

  void _f3() {
    setState(() {
      _tombolAngka(3);
    });
  }

  void _f4() {
    setState(() {
      _tombolAngka(4);
    });
  }

  void _f5() {
    setState(() {
      _tombolAngka(5);
    });
  }

  void _f6() {
    setState(() {
      _tombolAngka(6);
    });
  }

  void _f7() {
    setState(() {
      _tombolAngka(7);
    });
  }

  void _f8() {
    setState(() {
      _tombolAngka(8);
    });
  }

  void _f9() {
    setState(() {
      _tombolAngka(9);
    });
  }

  void _clr() {
    setState(() {
      _angkaDisplay = '0';
      _angkaModif = 0;
      _angkaSimpan = 0;
      _modeOperasi = 0;
    });
  }

  void _opPlus() {
    setState(() {
      _tombolOperasi(1);
    });
  }

  void _opMinus() {
    setState(() {
      _tombolOperasi(2);
    });
  }

  void _opTimes() {
    setState(() {
      _tombolOperasi(3);
    });
  }

  void _opDivides() {
    setState(() {
      _tombolOperasi(4);
    });
  }

  void _opResult() {
    setState(() {
      double _angkaHasil;

      if (_modeOperasi == 1) {
        _angkaHasil = _angkaSimpan + _angkaModif;
      } else if (_modeOperasi == 2) {
        _angkaHasil = _angkaSimpan - _angkaModif;
      } else if (_modeOperasi == 3) {
        _angkaHasil = _angkaSimpan * _angkaModif;
      } else if (_modeOperasi == 4) {
        _angkaHasil = _angkaSimpan / _angkaModif;
      }

      _angkaDisplay = '$_angkaHasil';
      _angkaModif = 0;
      _angkaSimpan = 0;
      _modeOperasi = 0;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('My Flutter Calculator'),
      ),
      body: Container(
          child: Column(
        mainAxisAlignment: MainAxisAlignment.spaceEvenly,
        children: <Widget>[
          Container(
            constraints: BoxConstraints.expand(
                height:
                    Theme.of(context).textTheme.headline4.fontSize * 1.1 + 50),
            alignment: Alignment.bottomRight,
            color: Colors.white,
            child: Text(
              '$_angkaDisplay',
              style: TextStyle(fontSize: 50, color: Colors.black),
              textAlign: TextAlign.right,
            ),
          ),
          Row(
            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
            children: <Widget>[
              _tombol('7', _f7),
              _tombol('8', _f8),
              _tombol('9', _f9),
              _tombol('+', _opPlus),
            ],
          ),
          Row(
            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
            children: <Widget>[
              _tombol('4', _f4),
              _tombol('5', _f5),
              _tombol('6', _f6),
              _tombol('-', _opMinus),
            ],
          ),
          Row(
            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
            children: <Widget>[
              _tombol('1', _f1),
              _tombol('2', _f2),
              _tombol('3', _f3),
              _tombol('*', _opTimes),
            ],
          ),
          Row(
            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
            children: <Widget>[
              _tombol('C', _clr),
              _tombol('0', _f0),
              _tombol('=', _opResult),
              _tombol('/', _opDivides),
            ],
          ),
          Container(
            constraints: BoxConstraints.expand(
                height:
                    Theme.of(context).textTheme.headline4.fontSize * 1.1 + 50),
            alignment: Alignment.topLeft,
            color: Colors.black,
          ),
        ],
      )),
    );
  }

  Widget _tombol(String angka, Function() f) {
    return MaterialButton(
        height: 100,
        child: Text(
          angka,
          style: TextStyle(fontWeight: FontWeight.bold, fontSize: 24),
        ),
        textColor: Colors.black,
        color: Colors.grey[100],
        onPressed: f);
  }
}
