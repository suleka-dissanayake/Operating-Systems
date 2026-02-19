numbers=(10 5 40 7 8)
sum=0
for num in "${numbers[@]}"; do
((sum += num))
done
echo "Sum of numbers in array: $sum"
sorted=($(printf '%s\n' "${numbers[@]}" | sort -n))
for num in "${sorted[@]}"; do
echo "$num"
done