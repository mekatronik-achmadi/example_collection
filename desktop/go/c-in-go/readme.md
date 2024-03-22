# Run C in Go

**note:** cgo using comment as hint

Install module and disable Go-111

```sh
go env -w GO111MODULE=off
```

Compile Go

```sh
export CGO_CPPFLAGS="-I /usr/include"
export CGO_LDFLAGS="-L /usr/lib -lm"

go build main.go
```

Run binary

```sh
./main
```

