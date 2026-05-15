sum=0
echo "Enter 10 numbers:"

for (( i=1; i<=10; i++ ))
do
    read num
    if [ $((num % 5)) -eq 0 ]; then
        sum=$((sum + num))
    fi
done

echo "The sum of numbers divisible by 5 is: $sum"