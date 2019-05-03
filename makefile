modules:
	cd raat/modules/unittest && make all

parameters:
	cd raat/parameters/unittest && make all

raat_code:
	cd raat/raat_code/unittest && make all

all: modules parameters raat_code

clean:
	cd raat/modules/unittest && make clean
	cd raat/parameters/unittest && make clean
	cd raat/raat_code/unittest && make clean

