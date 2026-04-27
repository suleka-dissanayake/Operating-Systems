digitSum() {
    local num=$1
    local result=0
    while [ $num -gt 0 ]; do
        result=$((result + num % 10))
        num=$((num / 10))
    done
    echo $result
}

reverse() {
    local num=$1
    local result=0
    while [ $num -gt 0 ]; do
        result=$((result * 10 + num % 10))
        num=$((num / 10))
    done
    echo $result
}

read -p "Enter a four-digit number: " n

echo "Sum of digits: $(digitSum $n)"
echo "Reversed number: $(reverse $n)"