read -p "Enter a number: " num
if [ "$num" -ge 10 ] && [ "$num" -le 20 ]; then
echo "$num is between 10 and 20!"
else
echo "$num is not between 10 and 20!"
fi