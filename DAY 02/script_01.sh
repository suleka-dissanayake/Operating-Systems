read -p "Enter first string: " string1
read -p "Enter second string: " string2
result="$string1 $string2"
echo $result
uppcse=$(echo "$string1" | tr '[:lower:]' '[:upper:]')
echo $uppcse