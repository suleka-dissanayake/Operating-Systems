read -p "Enter first number:" a
read -p "Enter second number:" b

echo "Choose an operation:"
echo "1. Addition"
echo "2. Subtraction"
echo "3. Multiplication"
echo "4. Division"

read choice

case $choice in
    1)
        result=$((a + b))
        echo "Addition = $result"
        ;;
    
    2)
        result=$((a - b))
        echo "Subtraction = $result"
        ;;
    
    3)
        result=$((a * b))
        echo "Multiplication = $result"
        ;;
    
    4)
        if [ $b -ne 0 ]
        then
            result=$((a / b))
            echo "Division = $result"
        else
            echo "Division by zero is not possible"
        fi
        ;;
    
    *)
        echo "Invalid choice"
        ;;
esac