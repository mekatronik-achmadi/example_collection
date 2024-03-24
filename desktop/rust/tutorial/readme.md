# Rust Tutorial

## Original Tutorial

- https://www.tutorialspoint.com/rust/
- https://stevedonovan.github.io/rust-gentle-intro/
- https://google.github.io/comprehensive-rust/

## Install Rust

### ArchLinux packages

Install using command:

```sh
sudo pacman -S rust rust-src
```

### Official Rustup

Install using Rustup script:

```sh
```sh
curl --proto '=https' --tlsv1.3 -sSf https://sh.rustup.rs -o ~/rust.sh

bash ~/rust.sh -y --no-modify-path
```

Set Rustup environment

```sh
source ~/.cargo/env
```

Install source component

```
rustup component add rust-src
```

then install source component

## Setup Rust Project

Initiate project in current directory

```sh
cargo init --name learn ./
```

## Build and Run

Build using Cargo

```sh
cargo build --release
```

Run using Cargp

```sh
cargo run --release
```

or binary directly

```sh
./target/release/learn
```


