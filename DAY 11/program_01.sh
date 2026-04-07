read -p "Enter number 1: " n1
read -p "Enter number 2: " n2
read -p "Select an operator ('+' or '-' or '*' or '/'): " op

case $op in 
'+') echo $(($n1+$n2));;
'-') echo $(($n1-$n2));;
'*') echo $(($n1*$n2));;
'/') echo $(($n1/$n2));;
esac