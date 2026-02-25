read -p "Enter base number: " base
read -p "Enter exponent: " expo
mod=$(($base%$expo))
ans=$(($base**$expo))
echo "Modulus is $mod and exponentation is $ans"