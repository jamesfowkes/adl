for file in examples/*
do
	echo "Trying to build $file"
	python3 adl.py $file --sketchbook=~/sketchbook
	echo ""
done
