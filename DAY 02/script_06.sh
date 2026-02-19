fruit=("Apple" "Banana" "Orange" "Grape")
echo "The first fruit is: ${fruit[0]}"
echo ""
for fruit in "${fruit[@]}"; do
echo "$fruit"
done