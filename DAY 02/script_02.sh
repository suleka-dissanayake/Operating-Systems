read -p "Enter first string: " str1
read -p "Enter second string: " str2
if [ ${#str1} -eq ${#str2} ]; then
echo "Both have same length"
else
echo "Each have different lengths"
fi