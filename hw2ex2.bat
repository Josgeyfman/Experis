echo "please enter a number"
read a
for((c=0;c<$a;c++)); do
	if  !(($c % 2 )) ;then
		echo "Welcome $c is even"
	fi
done