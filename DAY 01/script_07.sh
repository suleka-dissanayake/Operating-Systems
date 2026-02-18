echo "Enter marks for five subjects: "
read n1
read n2
read n3
read n4
read n5
total=$(($n1 + $n2 + $n3 + $n4 + $n5))
average=$(($total/5))
echo "Total: $total"
echo "Average: $average"
if [ $total -gt 400 ]
then
    echo "Very good"
elif [ $total -gt 300 ]
then
    echo "Good"
elif [ $total -gt 200 ]
then
    echo "Poor"
else
    echo "Very poor"
fi