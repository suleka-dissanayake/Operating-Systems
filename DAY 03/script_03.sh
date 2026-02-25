read -p "Enter first string: " str1
read -p "Enter second string: " str2
if [ ${#str1} -eq ${#str2} ]; then
    echo "Both strings have same length!"
elif [ ${#str1} -gt ${#str2} ]; then
    echo "First string is longer!"
else
    echo "Second string is longer!"
fi