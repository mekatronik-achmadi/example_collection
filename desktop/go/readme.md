# GoLang

## Setup in ArchLinux

```sh
go gopls delve
```

## Editor

### Vim CoC

install extension

```sh
vim -c "CocInstall coc-go"
```

add this line to: **~/.vim/coc-settings.json**

```json
"go.goplsPath"="/usr/bin/gopls"
```

### VSCode

install VSCode extension

```sh
code --force --install-extension golang.go
```

