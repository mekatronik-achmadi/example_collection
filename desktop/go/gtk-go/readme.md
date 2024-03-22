# Compile

Install module and disable Go-111

```sh
go env -w GO111MODULE=off
go get github.com/gotk3/gotk3/gtk
```

Compile Go

```sh
go build main.go
```

Run binary

```sh
./main
```

