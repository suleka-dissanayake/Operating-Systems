read -p "Enter first string: " string1
read -p "Enter second string: " string2
result="$string1 $string2"
echo $result
uppcse=$(echo "$result" | tr '[:lower:]' '[:upper:]')
echo "In uppercase: $uppcse"