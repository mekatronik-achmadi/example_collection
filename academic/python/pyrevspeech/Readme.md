# Python Speech Reverberation

Original Work: https://github.com/mravanelli/pySpeechRev

## Requirement

This example we use Arch-Linux/Manjaro, here some installation:
- NumPy
```sh
sudo pacman -S python-numpy
```

- SciPy
```sh
sudo pacman -S python-scipy
```

- SoundFile
AUR Package: https://aur.archlinux.org/packages/python-soundfile/

## Get Run Example

Download example:
```sh
mkdir -p data_example/clean_examples/
cd data_example/clean_examples/

wget -c -O ex1.wav https://github.com/mravanelli/pySpeechRev/blob/master/clean_examples/ex1.wav?raw=true
wget -c -O ex2.wav https://github.com/mravanelli/pySpeechRev/blob/master/clean_examples/ex2.wav?raw=true
wget -c -O ex3.wav https://github.com/mravanelli/pySpeechRev/blob/master/clean_examples/ex3.wav?raw=true
cd ../

cd IR_examples/
wget -c -O IR1.mat https://github.com/mravanelli/pySpeechRev/blob/master/IR_examples/IR1.mat?raw=true
wget -c -O IR2.mat https://github.com/mravanelli/pySpeechRev/blob/master/IR_examples/IR2.mat?raw=true
wget -c -O IR3.mat https://github.com/mravanelli/pySpeechRev/blob/master/IR_examples/IR3.mat?raw=true
cd ../

wget -c https://raw.githubusercontent.com/mravanelli/pySpeechRev/master/list.txt
cd ../
```

Run first example:
```sh
cd data_example/
mkdir -p rev_examples/

python ../pySpeechRev.py clean_examples/ rev_examples/ list.txt
```
